#ifndef VECTOID_SCENEGRAPH_GEODE_H_
#define VECTOID_SCENEGRAPH_GEODE_H_

#include <memory>
#include <Vectoid/SceneGraph/Node.h>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace SceneGraph {

//! This scene graph node represents actual geometry in the scene (geode = geometry node).
/*!
 *  A geode's geometry may be <c>nullptr</c> (empty).
 */
class Geode : public Node {
  public:
    Geode(const Geode &other) = delete;
    Geode &operator=(const Geode &other) = delete;

    //! Replaces the geode's geometry with the specified one.
    /*!
     *  A geode's geometry may be <c>nullptr</c> (empty).
     */
    void SetGeometry(const std::shared_ptr<GeometryInterface> &geometry);
    void RenderPre() override;

  protected:
    /*!
     *  A geode's geometry may be <c>nullptr</c> (empty).
     */
    Geode(const std::shared_ptr<GeometryInterface> &geometry);
    
  private:
    std::shared_ptr<GeometryInterface> geometry_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_GEODE_H_
