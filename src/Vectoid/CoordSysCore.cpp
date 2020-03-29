#include <kxm/Vectoid/CoordSysCore.h>

namespace kxm {
namespace Vectoid {

CoordSysCore::CoordSysCore()
        : transformChanged_(true) {
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

}    // Namespace Vectoid.
}    // Namespace kxm.
