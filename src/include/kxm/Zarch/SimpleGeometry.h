#ifndef KXM_ZARCH_SIMPLEGEOMETRY_H_
#define KXM_ZARCH_SIMPLEGEOMETRY_H_

#include <vector>
#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>
#include <kxm/Vectoid/HasBoundingBoxInterface.h>
#include <kxm/Vectoid/BoundingBox.h>

namespace kxm {

namespace Vectoid {
    class Vector;
    class RenderContext;
}

namespace Zarch {

//! Base class to simple geometries.
/*!
 *  \ingroup Zarch
 */
class SimpleGeometry : public virtual Vectoid::GeometryInterface, public virtual Vectoid::HasBoundingBoxInterface {
  public:
    SimpleGeometry();
    void Render(Vectoid::RenderContext *context);
    void GetBoundingBox(Vectoid::BoundingBox *outBoundingBox);
    
  protected:
    void AddTriangle(const Vectoid::Vector &vertex0, const Vectoid::Vector &vertex1, const Vectoid::Vector &vertex2,
                     const Vectoid::Vector &color);
    void Move(const Vectoid::Vector &translation);
    void Scale(float factor);
    
  private:
    SimpleGeometry(const SimpleGeometry &other);
    SimpleGeometry &operator=(const SimpleGeometry &other);
    
    int                          numTriangles_;
    std::vector<GLfloat>         vertexArray_,
                                 colorArray_;
    Vectoid::BoundingBox         boundingBox_;
    bool                         boundingBoxValid_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_SIMPLEGEOMETRY_H_
