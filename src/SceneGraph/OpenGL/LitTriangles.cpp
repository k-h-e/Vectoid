///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/LitTriangles.h>

#include <vector>

#include <K/Core/Log.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::optional;
using std::shared_ptr;
using std::to_string;
using std::vector;
using K::Core::Log;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;
using Vectoid::Core::ThreePoints;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

LitTriangles::LitTriangles(const shared_ptr<class Context> &context,
                           const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : SceneGraph::LitTriangles(context, triangleProvider),
          vboSlot_(context->AddResourceSlot(Context::ResourceType::Vbo)),
          numTriangles_(0) {
    // Nop.
}

LitTriangles::~LitTriangles() {
    GetContext()->RemoveResourceSlot(vboSlot_);
}

void LitTriangles::Render() {
    optional<GLuint> vbo = GenerateVbo();
    if (vbo) {
        if (!depthTestEnabled_) {
           glDisable(GL_DEPTH_TEST);
        }
        if (lightingEnabled_) {
            glEnable(GL_LIGHTING);
            glEnable(GL_COLOR_MATERIAL);
        }
        glColor4f(color_.x, color_.y, color_.z, 1.0f);
        
        glBindBuffer(GL_ARRAY_BUFFER, *vbo);
        glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), nullptr);
        glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), reinterpret_cast<void *>(12u));
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, numTriangles_ * 3);

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        if (lightingEnabled_) {
            glDisable(GL_COLOR_MATERIAL);
            glDisable(GL_LIGHTING);
        }
        if (!depthTestEnabled_) {
           glEnable(GL_DEPTH_TEST);
        }
    }
}

optional<GLuint> LitTriangles::GenerateVbo() {
    optional<GLuint> vbo = GetContext()->GetResource(vboSlot_);
    if (!vbo) {
        vector<GLfloat> data;
        int             numTriangles = 0;

        ThreePoints triangle;
        triangleProvider_->PrepareToProvideTriangles();
        while (triangleProvider_->ProvideNextTriangle(triangle)) {
            Vector<float> normal { triangle.Normal() };
            if (!normal.Valid()) {
                normal = Vector<float>(1.0f, 0.0f, 0.0f);
                Log::Print(Log::Level::Warning, this, [&]{
                    return "failed to compute triangle normal, substituting default";
                });
            }

            for (int i = 0; i < 3; ++i) {
                const Vector<float> &vertex = triangle[i];
                data.push_back(vertex.x);
                data.push_back(vertex.y);
                data.push_back(vertex.z);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);
            }

            ++numTriangles;
        }

        if (numTriangles && !triangleProvider_->TriangleError()) {
            GLuint name;
            glGenBuffers(1u, &name);
            glBindBuffer(GL_ARRAY_BUFFER, name);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0u);

            vbo           = name;
            GetContext()->SetResource(vboSlot_, name);
            numTriangles_ = numTriangles;
            Log::Print(Log::Level::Debug, this, [&]{
                return "generated VBO " + to_string(name) + ", size=" + to_string(data.size() * sizeof(GLfloat));
            });
        } else {
            Log::Print(Log::Level::Error, this, [&]{ return "failed to generate VBO"; });
        }
    }

    return vbo;
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
