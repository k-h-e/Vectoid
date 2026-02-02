///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/LitColorCodedTriangles.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/ExtendedTriangleProviderInterface.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/DataSet/Points.h>
#include <Vectoid/DataSet/ThreeIds.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::make_unique;
using std::nullopt;
using std::optional;
using std::shared_ptr;
using std::to_string;
using std::unordered_set;
using std::vector;
using K::Core::Log;
using K::Core::NumberTools;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;
using Vectoid::Core::ThreePoints;
using Vectoid::DataSet::ThreeIds;
using Vectoid::DataSet::Triangles;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

LitColorCodedTriangles::LitColorCodedTriangles(const shared_ptr<class Context> &context,
                                               const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : SceneGraph::LitColorCodedTriangles{context, triangleProvider},
          vboSlot_{context->AddResourceSlot(Context::ResourceType::Vbo)},
          numTriangles_{0} {
    // Nop.
}

LitColorCodedTriangles::~LitColorCodedTriangles() {
    Context()->RemoveResourceSlot(vboSlot_);
}

void LitColorCodedTriangles::Render() {
    optional<GLuint> vbo{GenerateVbo()};
    if (vbo) {
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);

        glBindBuffer(GL_ARRAY_BUFFER, *vbo);
        glVertexPointer(3, GL_FLOAT, 10 * sizeof(GLfloat), nullptr);
        glNormalPointer(GL_FLOAT, 10 * sizeof(GLfloat), reinterpret_cast<void *>(12u));
        glColorPointer(4, GL_FLOAT, 10 * sizeof(GLfloat), reinterpret_cast<void *>(24u));
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, numTriangles_ * 3);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHTING);
    }
}

optional<GLuint> LitColorCodedTriangles::GenerateVbo() {
    optional<GLuint> vbo{Context()->GetResource(vboSlot_)};
    if (!vbo) {
        if (gouraudTriangleProvider_) {
            vbo = GenerateGouraudVbo();
        } else {
            vbo = GenerateRegularVbo();
        }
    }

    return vbo;
}

optional<GLuint> LitColorCodedTriangles::GenerateRegularVbo() {
    vector<GLfloat> data;

    ThreePoints   triangle;
    int           numTriangles{0};
    triangleProvider_->PrepareToProvideTriangles();
    while (triangleProvider_->ProvideNextTriangle(triangle)) {
        Vector<float> normal { triangle.Normal() };
        if (!normal.Valid()) {
            normal = Vector<float>{1.0f, 0.0f, 0.0f};
            Log::Print(Log::Level::Warning, this, [&]{
                return "failed to compute triangle normal, substituting default";
            });
        }

        for (int i = 0; i < 3; ++i) {
            const Vector<float> &vertex{triangle[i]};
            const Vector<float> color{GetColor(vertex)};
            data.push_back(vertex.x);
            data.push_back(vertex.y);
            data.push_back(vertex.z);
            data.push_back(normal.x);
            data.push_back(normal.y);
            data.push_back(normal.z);
            data.push_back(color.x);
            data.push_back(color.y);
            data.push_back(color.z);
            data.push_back(1.0f);
        }

        ++numTriangles;
    }

    if (numTriangles && !triangleProvider_->TriangleError()) {
        GLuint name;
        glGenBuffers(1u, &name);
        glBindBuffer(GL_ARRAY_BUFFER, name);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        Context()->SetResource(vboSlot_, name);
        numTriangles_ = numTriangles;
        Log::Print(Log::Level::Debug, this, [&]{
            return "generated VBO " + to_string(name) + " for regular shading, num_triangles="
                + to_string(numTriangles_) + ", size=" + to_string(data.size() * sizeof(GLfloat));
        });
        return name;
    } else {
        Log::Print(Log::Level::Error, this, [&]{ return "failed to generate VBO for regular shading"; });
        return nullopt;
    }
}

optional<GLuint> LitColorCodedTriangles::GenerateGouraudVbo() {
    vector<GLfloat> data;
    
    ThreePoints triangle;
    ThreePoints vertexNormals;
    int         numTriangles = 0;
    gouraudTriangleProvider_->PrepareToProvideTriangles();
    while (gouraudTriangleProvider_->ProvideNextTriangle(triangle)) {
        ++numTriangles;
        gouraudTriangleProvider_->ProvideVertexNormals(vertexNormals);
        for (int i = 0; i < 3; ++i) {
            const Vector<float> &vertex = triangle[i];
            data.push_back(vertex.x);
            data.push_back(vertex.y);
            data.push_back(vertex.z);
            const Vector<float> &normal = vertexNormals[i];
            data.push_back(normal.x);
            data.push_back(normal.y);
            data.push_back(normal.z);
            const Vector<float> color = GetColor(vertex);
            data.push_back(color.x);
            data.push_back(color.y);
            data.push_back(color.z);
            data.push_back(1.0f);
        }
    }
    
    if (gouraudTriangleProvider_->TriangleError()) {
        numTriangles_ = 0;
        
        Log::Print(Log::Level::Error, this, [&]{ return "failed to generate VBO for Gouraud shading"; });
        return nullopt;
    } else {
        GLuint name;
        glGenBuffers(1u, &name);
        glBindBuffer(GL_ARRAY_BUFFER, name);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);
        Context()->SetResource(vboSlot_, name);
        numTriangles_ = numTriangles;
        
        Log::Print(Log::Level::Debug, this, [&]{
            return "generated VBO " + to_string(name) + " for Gouraud shading, num_triangles="
                + to_string(numTriangles_) + ", size=" + to_string(data.size() * sizeof(GLfloat));
        });
        return name;
    }
}

Vector<float> LitColorCodedTriangles::GetColor(const Vector<float> &vertex) {
    auto color{colorCodingFunction_ ? colorCodingFunction_(vertex) : Vector<float>{.5f, .5f, .5f}};
    color.ClampComponents(0.0f, 1.0f);
    return color;
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
