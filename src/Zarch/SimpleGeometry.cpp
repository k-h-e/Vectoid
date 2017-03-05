#include <kxm/Zarch/SimpleGeometry.h>

#include <kxm/Vectoid/Vector.h>

using std::vector;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

SimpleGeometry::SimpleGeometry()
        : numTriangles_(0),
          boundingBoxValid_(false) {
    // Nop.
}

void SimpleGeometry::GetBoundingBox(BoundingBox *outBoundingBox) {
    if (!boundingBoxValid_) {
        BoundingBox boundingBox;
        GLfloat *coordPtr = &vertexArray_[0];
        Vector point;
        for (int i = 0; i < numTriangles_ * 3; ++i) {
            point.x = *coordPtr++;
            point.y = *coordPtr++;
            point.z = *coordPtr++;
            boundingBox.Grow(point);
        }
        boundingBox_ = boundingBox;
        boundingBoxValid_ = true;
    }
    *outBoundingBox = boundingBox_;
}

void SimpleGeometry::Render(RenderContext *context) {
    if (numTriangles_) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
        glColorPointer(4, GL_FLOAT, 0, &colorArray_[0]);
        glDrawArrays(GL_TRIANGLES, 0, numTriangles_ * 3);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void SimpleGeometry::AddTriangle(const Vector &vertex0, const Vector &vertex1, const Vector &vertex2,
                                 const Vector &color) {
    vertexArray_.push_back(vertex0.x);
    vertexArray_.push_back(vertex0.y);
    vertexArray_.push_back(vertex0.z);
    vertexArray_.push_back(vertex1.x);
    vertexArray_.push_back(vertex1.y);
    vertexArray_.push_back(vertex1.z);
    vertexArray_.push_back(vertex2.x);
    vertexArray_.push_back(vertex2.y);
    vertexArray_.push_back(vertex2.z);
    colorArray_.push_back(color.x);
    colorArray_.push_back(color.y);
    colorArray_.push_back(color.z);
    colorArray_.push_back(1.0f);
    colorArray_.push_back(color.x);
    colorArray_.push_back(color.y);
    colorArray_.push_back(color.z);
    colorArray_.push_back(1.0f);
    colorArray_.push_back(color.x);
    colorArray_.push_back(color.y);
    colorArray_.push_back(color.z);
    colorArray_.push_back(1.0f);
    ++numTriangles_;
    boundingBoxValid_ = false;
}

void SimpleGeometry::Move(const Vector &translation) {
    for (vector<GLfloat>::iterator iter = vertexArray_.begin();
         iter != vertexArray_.end(); ) {
        (*iter) += translation.x;
        ++iter;
        (*iter) += translation.y;
        ++iter;
        (*iter) += translation.z;
        ++iter;
    }
    boundingBoxValid_ = false;
}

void SimpleGeometry::Scale(float factor) {
    for (vector<GLfloat>::iterator iter = vertexArray_.begin(); iter != vertexArray_.end(); ++iter) {
        (*iter) *= (GLfloat)factor;
    }
    boundingBoxValid_ = false;
}

}    // Namespace Zarch.
}    // Namespace kxm.
