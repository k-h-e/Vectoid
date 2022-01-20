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
          vboSlot_(context->AddResourceSlot(Context::ResourceType::VBO)),
          numTriangles_(0) {
    // Nop.
}

LitTriangles::~LitTriangles() {
    Context()->RemoveResourceSlot(vboSlot_);
}

void LitTriangles::Render() {
    optional<GLuint> vbo = GenerateVBO();
    if (vbo) {
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(color_.x, color_.y, color_.z);

        glBindBuffer(GL_ARRAY_BUFFER, *vbo);
        glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), nullptr);
        glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), reinterpret_cast<void *>(12u));
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, numTriangles_ * 3);

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glColor3f(1.0f, 1.0f, 1.0f);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHTING);
    }
}

optional<GLuint> LitTriangles::GenerateVBO() {
    optional<GLuint> vbo = Context()->GetResource(vboSlot_);
    if (!vbo) {
        vector<GLfloat> data;
        int             numTriangles = 0;

        ThreePoints   triangle;
        Vector<float> normal;
        triangleProvider_->PrepareToProvideTriangles();
        while (triangleProvider_->ProvideNextTriangle(&triangle)) {
            triangle.ComputeNormal(&normal);
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
