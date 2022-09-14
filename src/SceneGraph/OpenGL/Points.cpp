#include <Vectoid/SceneGraph/OpenGL/Points.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/DataSet/Points.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::optional;
using std::shared_ptr;
using std::to_string;
using std::vector;
using K::Core::Log;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Points::Points(const shared_ptr<class Context> &context, const shared_ptr<DataSet::Points> &points)
        : SceneGraph::Points(context, points),
          vboSlot_(context->AddResourceSlot(Context::ResourceType::VBO)),
          numPoints_(0) {
    // Nop.
}

Points::~Points() {
    Context()->RemoveResourceSlot(vboSlot_);
}

void Points::Render() {
    optional<GLuint> vbo = GenerateVBO();
    if (vbo) {
        glColor4f(color_.x, color_.y, color_.z, 1.0f);

        glBindBuffer(GL_ARRAY_BUFFER, *vbo);
        glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), nullptr);
        glEnableClientState(GL_VERTEX_ARRAY);

        glDrawArrays(GL_POINTS, 0, numPoints_);

        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

optional<GLuint> Points::GenerateVBO() {
    optional<GLuint> vbo = Context()->GetResource(vboSlot_);
    if (!vbo) {
        if (points_->Size()) {
            vector<GLfloat> data;

            for (int i = 0; i < points_->Size(); ++i) {
                auto &point = (*points_)[i];
                data.push_back(point.x);
                data.push_back(point.y);
                data.push_back(point.z);
            }

            GLuint name;
            glGenBuffers(1u, &name);
            glBindBuffer(GL_ARRAY_BUFFER, name);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0u);

            vbo        = name;
            Context()->SetResource(vboSlot_, name);
            numPoints_ = points_->Size();
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
