#ifndef RASPIATOR_CUBOID_H_
#define RASPIATOR_CUBOID_H_


#include <vector>
#include <Vectoid/OpenGL.h>
#include <Vectoid/Vector.h>
#include <Vectoid/GeometryInterface.h>


namespace Raspiator {

//! Cuboid geometry.
class Cuboid : public virtual kxm::Vectoid::GeometryInterface {
  public:
    Cuboid(float width, float height, float depth, const kxm::Vectoid::Vector &color);
    Cuboid(const Cuboid &other)            = delete;
    Cuboid &operator=(const Cuboid &other) = delete;
    Cuboid(Cuboid &&other)                 = delete;
    Cuboid &operator=(Cuboid &&other)      = delete;

    void Render(kxm::Vectoid::RenderContext *context);
    
  private:
    void Compute(float width, float height, float depth);

    kxm::Vectoid::Vector color_;
    std::vector<GLfloat> vertices_,
                         normals_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_CUBOID_H_
