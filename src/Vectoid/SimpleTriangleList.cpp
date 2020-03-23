#include <kxm/Vectoid/SimpleTriangleList.h>

namespace kxm {
namespace Vectoid {

SimpleTriangleList::SimpleTriangleList()
        : cursor_(-1),
          normalsValid_(false) {
    // Nop.
}

void SimpleTriangleList::Add(const ThreePoints &triangle) {
    triangles_.push_back(triangle);
    normalsValid_ = false;
}

void SimpleTriangleList::PrepareToProvideTriangles() {
    cursor_ = -1;
}

bool SimpleTriangleList::ProvideNextTriangle(ThreePoints *outTriangle) {
    ++cursor_;
    if (cursor_ < static_cast<int>(triangles_.size())) {
        *outTriangle = triangles_[cursor_];
        return true;
    }
    else {
        return false;
    }
}

void SimpleTriangleList::ProvideNormal(Vector *outNormal) {
    if (cursor_ < static_cast<int>(triangles_.size())) {
        EnsureNormalsValid();
        *outNormal = normals_[cursor_];
    }
    else {
        *outNormal = Vector(0.0f, 1.0f, 0.0f);
    }
}

bool SimpleTriangleList::TriangleError() {
    return false;
}

void SimpleTriangleList::EnsureNormalsValid() {
    if (!normalsValid_) {
        normals_.clear();
        Vector normal;
        for (ThreePoints &triangle : triangles_) {
            triangle.ComputeNormal(&normal);
            if (!normal.Valid()) {
                normal = Vector(0.0f, 1.0f, 0.0f);
            }
            normals_.push_back(normal);
        }
        normalsValid_ = true;
    }
}

}    // Namespace Vectoid.
}    // Namespace kxm.