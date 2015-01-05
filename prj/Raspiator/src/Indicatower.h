#ifndef RASPIATOR_INDICATOWER_H_
#define RASPIATOR_INDICATOWER_H_


#include <Vectoid/OpenGL.h>
#include <Vectoid/GeometryInterface.h>


namespace Raspiator {

//! "Tower" geometry for indicating numbers.
class Indicatower : public virtual kxm::Vectoid::GeometryInterface {
  public:
    Indicatower();
    Indicatower(const Indicatower &other)            = delete;
    Indicatower &operator=(const Indicatower &other) = delete;
    Indicatower(Indicatower &&other)                 = delete;
    Indicatower &operator=(Indicatower &&other)      = delete;
    
    void SetHeight(float height);
    void Render(kxm::Vectoid::RenderContext *context);
    
  private:
    static const GLfloat normals[90];
    
    GLfloat vertices_[90],
            color_[4];
    
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_INDICATOWER_H_
