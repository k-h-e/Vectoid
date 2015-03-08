#ifndef RASPIATOR_INDICATOWER_H_
#define RASPIATOR_INDICATOWER_H_


#include <vector>
#include <Vectoid/OpenGL.h>
#include <Vectoid/Vector.h>
#include <Vectoid/GeometryInterface.h>


namespace Raspiator {

//! "Tower" geometry for indicating numbers.
class Indicatower : public virtual kxm::Vectoid::GeometryInterface {
  public:
    Indicatower(float radius, int numSectors, float stretch);
    Indicatower(const Indicatower &other)            = delete;
    Indicatower &operator=(const Indicatower &other) = delete;
    Indicatower(Indicatower &&other)                 = delete;
    Indicatower &operator=(Indicatower &&other)      = delete;
    
    void SetCounts(int num, int numTotal, int progressPercent);
    void Render(kxm::Vectoid::RenderContext *context);
    
  private:
    static const kxm::Vectoid::Vector greenColor,
                                      redColor,
                                      yellowColor;

    void ComputeHull(float top, float bottom);
    void ComputeCover(float top);

    std::vector<GLfloat> hullVertices_,
                         hullNormals_,
                         coverVertices_,
                         coverNormals_;
    int                  numSectors_;
    float                radius_,
                         stretch_,
                         top_,
                         mid_;
    int                  progressPercent_;
    kxm::Vectoid::Vector coverColor_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_INDICATOWER_H_
