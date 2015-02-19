#ifndef RASPIATOR_INDICATOWER_H_
#define RASPIATOR_INDICATOWER_H_


#include <vector>
#include <Vectoid/OpenGL.h>
#include <Vectoid/GeometryInterface.h>


namespace Raspiator {

//! "Tower" geometry for indicating numbers.
class Indicatower : public virtual kxm::Vectoid::GeometryInterface {
  public:
    Indicatower(int numSectors, float stretch);
    Indicatower(const Indicatower &other)            = delete;
    Indicatower &operator=(const Indicatower &other) = delete;
    Indicatower(Indicatower &&other)                 = delete;
    Indicatower &operator=(Indicatower &&other)      = delete;
    
    void SetCounts(int num, int numTotal);
    void Render(kxm::Vectoid::RenderContext *context);
    
  private:
    void ComputeHull(float top, float bottom);
    void ComputeCover(float top);

    GLfloat              color_[4];
    std::vector<GLfloat> hullVertices_,
                         hullNormals_,
                         coverVertices_,
                         coverNormals_;
    int                  numSectors_;
    float                stretch_,
                         top_,
                         mid_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_INDICATOWER_H_
