#include <Vectoid/SceneGraph/OpenGL/LineSegments.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Core/LineSegmentProviderInterface.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::optional;
using std::shared_ptr;
using std::to_string;
using std::vector;
using K::Core::Log;
using Vectoid::Core::LineSegmentProviderInterface;
using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

LineSegments::LineSegments(const shared_ptr<class Context> &context,
                           const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider)
        : SceneGraph::LineSegments(context, lineSegmentProvider),
          vboSlot_(context->AddResourceSlot(Context::ResourceType::VBO)),
          numSegments_(0) {
    // Nop.
}

LineSegments::~LineSegments() {
    Context()->RemoveResourceSlot(vboSlot_);
}

void LineSegments::Render() {
    optional<GLuint> vbo = GenerateVBO();
    if (vbo) {
        glColor3f(color_.x, color_.y, color_.z);

        glBindBuffer(GL_ARRAY_BUFFER, *vbo);
        glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), nullptr);
        glEnableClientState(GL_VERTEX_ARRAY);

        glDrawArrays(GL_LINES, 0, numSegments_ * 2);

        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glColor3f(1.0f, 1.0f, 1.0f);
    }
}

optional<GLuint> LineSegments::GenerateVBO() {
    optional<GLuint> vbo = Context()->GetResource(vboSlot_);
    if (!vbo) {
        vector<GLfloat> data;
        int             numSegments = 0;

        TwoPoints segment;
        lineSegmentProvider_->PrepareToProvideLineSegments();
        while (lineSegmentProvider_->ProvideNextLineSegment(&segment)) {
            for (int i = 0; i < 2; ++i) {
                const Vector<float> &vertex = segment[i];
                data.push_back(vertex.x);
                data.push_back(vertex.y);
                data.push_back(vertex.z);
            }

            ++numSegments;
        }

        if (numSegments && !lineSegmentProvider_->LineSegmentError()) {
            GLuint name;
            glGenBuffers(1u, &name);
            glBindBuffer(GL_ARRAY_BUFFER, name);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0u);

            vbo          = name;
            Context()->SetResource(vboSlot_, name);
            numSegments_ = numSegments;
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
