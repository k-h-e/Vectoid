#ifndef KXM_ZARCH_SIMPLEGEOMETRY_H_
#define KXM_ZARCH_SIMPLEGEOMETRY_H_

#include <vector>
#include <kxm/Vectoid/HasBoundingBoxInterface.h>
#include <kxm/Vectoid/BoundingBox.h>

namespace kxm {

namespace Vectoid {
    class Vector;
}

namespace Zarch {

namespace Video {
namespace OpenGL {
    class SimpleGeometryRenderer;
}
namespace Vulkan {
    class SimpleGeometryRenderer;
}
}

//! Simple triangle-soup geometry.
/*!
 *  \ingroup Zarch
 */
class SimpleGeometry : public virtual Vectoid::HasBoundingBoxInterface {
  public:
    friend class Video::OpenGL::SimpleGeometryRenderer;
    friend class Video::Vulkan::SimpleGeometryRenderer;
  
    SimpleGeometry();
    SimpleGeometry(const SimpleGeometry &other) = delete;
    SimpleGeometry &operator=(const SimpleGeometry &other) = delete;
    void GetBoundingBox(Vectoid::BoundingBox *outBoundingBox);
    void AddTriangle(const Vectoid::Vector &vertex0, const Vectoid::Vector &vertex1, const Vectoid::Vector &vertex2,
                     const Vectoid::Vector &color);
    void Move(const Vectoid::Vector &translation);
    void Scale(float factor);
    static std::shared_ptr<SimpleGeometry> NewLanderGeometry();
    static std::shared_ptr<SimpleGeometry> NewSaucerGeometry();
    
  private:
    int                          numTriangles_;
    std::vector<float>           vertexArray_,
                                 colorArray_;
    Vectoid::BoundingBox         boundingBox_;
    bool                         boundingBoxValid_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_SIMPLEGEOMETRY_H_
