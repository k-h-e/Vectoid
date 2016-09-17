#ifndef KXM_ZARCH_LANDERGEOMETRY_H_
#define KXM_ZARCH_LANDERGEOMETRY_H_

#include <vector>
#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {

namespace Vectoid {
    class Vector;
    class RenderContext;
}

namespace Zarch {

//! Initial, simple geometry for the lander (the vehicle controlled by the player).
/*!
 *  \ingroup Zarch
 */
class LanderGeometry : public virtual Vectoid::GeometryInterface {
  public:
    LanderGeometry();
    
    void Render(Vectoid::RenderContext *context);
    
  private:
    LanderGeometry(const LanderGeometry &other);
    LanderGeometry &operator=(const LanderGeometry &other);
    
    void AddTriangle(const Vectoid::Vector &vertex0, const Vectoid::Vector &vertex1,
                     const Vectoid::Vector &vertex2, const Vectoid::Vector &color);
    void Move(const Vectoid::Vector &translation);
    void Scale(float factor);
    
    int                          numTriangles_;
    std::vector<GLfloat>         vertexArray_,
                                 colorArray_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_LANDERGEOMETRY_H_
