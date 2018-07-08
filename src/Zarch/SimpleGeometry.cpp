#include <kxm/Zarch/SimpleGeometry.h>

#include <kxm/Vectoid/Vector.h>

using std::vector;
using std::shared_ptr;
using std::make_shared;
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
        float *coordPtr = &vertexArray_[0];
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
    for (vector<float>::iterator iter = vertexArray_.begin();
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
    for (vector<float>::iterator iter = vertexArray_.begin(); iter != vertexArray_.end(); ++iter) {
        (*iter) *= (float)factor;
    }
    boundingBoxValid_ = false;
}

shared_ptr<SimpleGeometry> SimpleGeometry::NewLanderGeometry() {
    shared_ptr<SimpleGeometry> geometry = make_shared<SimpleGeometry>();

    geometry->AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( -.5f, 0.0f,   .5f), Vector( 0.0f, 0.0f,  -1.0f),
                          Vector( .8f,  .8f,  .2f));
    geometry->AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector(  .5f, 0.0f,   .5f), Vector( 0.0f,  .35f,  0.0f),
                          Vector( .8f,  .8f,  .2f));
    
    geometry->AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector( 0.0f,  .35f,  0.0f), Vector( 0.0f,  .5f, - .8f),
                          Vector( .8f,  .5f,  .2f));
    geometry->AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 0.0f,  .5f, - .8f), Vector( 0.0f,  .35f,  0.0f),
                          Vector( .8f,  .5f,  .2f));
    
    geometry->AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector( 0.0f,  .5f, - .8f), Vector(-1.0f,  .1f,  -1.0f),
                          Vector( .5f,  .8f,  .2f));
    geometry->AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 1.0f,  .1f, -1.0f), Vector( 0.0f,  .5f, - .8f),
                          Vector( .5f,  .8f,  .2f));
    
    geometry->AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector(-1.0f,  .1f, -1.0f), Vector( 0.0f, 0.0f,  -1.0f),
                          Vector( .2f,  .5f,  .8f));
    geometry->AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 0.0f, 0.0f,  -1.0f), Vector( 1.0f,  .1f, -1.0f),
                          Vector( .2f,  .5f,  .8f));
    
    geometry->AddTriangle(Vector(0.0f,  .5f, -.8f), Vector( 0.0f, 0.0f,  -1.0f), Vector(-1.0f,  .1f, -1.0f),
                          Vector(.8f,   .2f,  .3f));
    geometry->AddTriangle(Vector(0.0f,  .5f, -.8f), Vector( 1.0f,  .1f, -1.0f), Vector( 0.0f, 0.0f,  -1.0f),
                          Vector(.8f, .2f, .3f));
    
    geometry->Move(Vector(0.0f, 0.0f, .35f));
    geometry->Scale(.65f);
    return geometry;
}

shared_ptr<SimpleGeometry> SimpleGeometry::NewSaucerGeometry() {
    shared_ptr<SimpleGeometry> geometry = make_shared<SimpleGeometry>();
    
    const float radius = 1.0f;
    float lastX, lastZ;
    for (int i = 0; i <= 8; ++i) {
        float angle = -22.5f + (float)(i*45);
        float x = radius * (float)cos(angle * 3.141592654f / 180.0f),
              z = radius * (float)sin(angle * 3.141592654f / 180.0f);
        if (i) {
            geometry->AddTriangle(Vector(0.0f,  .3f, 0.0f), Vector(x, 0.0f, z), Vector(lastX, 0.0f, lastZ),
                                  i % 2 ? Vector( .2f,  .2f,  .8f) : Vector( .2f,  .8f,  .8f));
            geometry->AddTriangle(Vector(0.0f, -.3f, 0.0f), Vector(lastX, 0.0f, lastZ), Vector(x, 0.0f, z),
                                  i % 2 ? Vector( .2f,  .8f,  .8f) : Vector( .2f,  .2f,  .8f));
        }
        lastX = x;
        lastZ = z;
    }
    geometry->Scale(.7f);
    
    return geometry;
}

}    // Namespace Zarch.
}    // Namespace kxm.
