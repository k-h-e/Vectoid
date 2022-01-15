#include <Vectoid/SceneGraph/CoordSysCore.h>

using std::shared_ptr;
using Vectoid::Core::Vector;
using Vectoid::Core::Transform;

namespace Vectoid {
namespace SceneGraph {

CoordSysCore::CoordSysCore(const shared_ptr<Context> &context)
        : GroupNode(context),
          transformChanged_(true) {
    // Nop.
}

void CoordSysCore::PrependTransform(const Transform<float> &other) {
    transform_.Prepend(other);
    transformChanged_ = true;
}

void CoordSysCore::AppendTransform(const Transform<float> &other) {
    transform_.Append(other);
    transformChanged_ = true;
}

void CoordSysCore::SetTransform(const Transform<float> &other) {
    transform_ = other;
    transformChanged_ = true;
}

void CoordSysCore::GetTransform(Transform<float> *outTransform) const {
    *outTransform = transform_;
}

void CoordSysCore::SetPosition(const Vector<float> &pos) {
    transform_.SetTranslationPart(pos);
    transformChanged_ = true;
}

void CoordSysCore::GetPosition(Vector<float> *outPos) {
    transform_.GetTranslationPart(outPos);
}

Vector<float> CoordSysCore::Position() {
    return transform_.TranslationPart();
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
