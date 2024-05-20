///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/TransparentTriangles.h>

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

TransparentTriangles::TransparentTriangles(const shared_ptr<class Context> &context,
                                           const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : SceneGraph::TransparentTriangles(context, triangleProvider),
          vboSlot_(context->AddResourceSlot(Context::ResourceType::Vbo)),
          numTriangles_(0) {
    // Nop.
}

TransparentTriangles::~TransparentTriangles() {
    Context()->RemoveResourceSlot(vboSlot_);
}

void TransparentTriangles::Render() {
    optional<GLuint> vbo = GenerateVbo();
    if (vbo) {
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glColor4f(color_.x, color_.y, color_.z, alpha_);

        glBindBuffer(GL_ARRAY_BUFFER, *vbo);
        glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), nullptr);
        glEnableClientState(GL_VERTEX_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, numTriangles_ * 3);

        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
    }
}

optional<GLuint> TransparentTriangles::GenerateVbo() {
    optional<GLuint> vbo = Context()->GetResource(vboSlot_);
    if (!vbo) {
        vector<GLfloat> data;
        int             numTriangles = 0;

        ThreePoints   triangle;
        triangleProvider_->PrepareToProvideTriangles();
        while (triangleProvider_->ProvideNextTriangle(&triangle)) {
            for (int i = 0; i < 3; ++i) {
                const Vector<float> &vertex = triangle[i];
                data.push_back(vertex.x);
                data.push_back(vertex.y);
                data.push_back(vertex.z);
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
            Context()->SetResource(vboSlot_, name);
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
