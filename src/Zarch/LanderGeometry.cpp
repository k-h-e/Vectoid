#include <kxm/Zarch/LanderGeometry.h>

#include <kxm/Vectoid/Vector.h>

using std::vector;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

LanderGeometry::LanderGeometry() : numTriangles_(0) {
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector(  .5f, 0.0f,   .5f), Vector( 0.0f, 0.0f,  -1.0f),
                Vector( .8f,  .8f,  .2f));
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector(  .5f, 0.0f,   .5f), Vector( 0.0f,  .35f,  0.0f),
                Vector( .8f,  .8f,  .2f));
    
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector( 0.0f,  .5f, - .8f), Vector( 0.0f,  .35f,  0.0f),
                Vector( .8f,  .5f,  .2f));
    AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 0.0f,  .5f, - .8f), Vector( 0.0f,  .35f,  0.0f),
                Vector( .8f,  .5f,  .2f));
    
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector( 0.0f,  .5f, - .8f), Vector(-1.0f,  .1f,  -1.0f),
                Vector( .5f,  .8f,  .2f));
    AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 0.0f,  .5f, - .8f), Vector( 1.0f,  .1f,  -1.0f),
                Vector( .5f,  .8f,  .2f));
    
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector(-1.0f,  .1f, -1.0f), Vector( 0.0f, 0.0f,  -1.0f),
                Vector( .2f,  .5f,  .8f));
    AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 1.0f,  .1f, -1.0f), Vector( 0.0f, 0.0f,  -1.0f),
                Vector( .2f,  .5f,  .8f));
    
    AddTriangle(Vector(0.0f,  .5f, -.8f), Vector(-1.0f,  .1f, -1.0f), Vector( 0.0f, 0.0f,  -1.0f),
                Vector(.8f,   .2f,  .3f));
    AddTriangle(Vector(0.0f,  .5f, -.8f), Vector( 1.0f,  .1f, -1.0f), Vector( 0.0f, 0.0f,  -1.0f),
                Vector(.8f, .2f, .3f));
    
    Move(Vector(0.0f, 0.0f, .35f));
    Scale(.65f);
}

void LanderGeometry::Render(RenderContext *context) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
    glColorPointer(4, GL_FLOAT, 0, &colorArray_[0]);
    glDrawArrays(GL_TRIANGLES, 0, numTriangles_ * 3);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void LanderGeometry::AddTriangle(
        const Vectoid::Vector &vertex0, const Vectoid::Vector &vertex1,
        const Vectoid::Vector &vertex2, const Vectoid::Vector &color) {
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
}

void LanderGeometry::Move(const Vector &translation) {
    for (vector<GLfloat>::iterator iter = vertexArray_.begin();
         iter != vertexArray_.end(); ) {
        (*iter) += translation.x;
        ++iter;
        (*iter) += translation.y;
        ++iter;
        (*iter) += translation.z;
        ++iter;
    }
}

void LanderGeometry::Scale(float factor) {
    for (vector<GLfloat>::iterator iter = vertexArray_.begin();
         iter != vertexArray_.end(); ++iter)
        (*iter) *= (GLfloat)factor;
}

}    // Namespace Zarch.
}    // Namespace kxm.
