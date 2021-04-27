#ifndef VECTOID_SCENEGRAPH_PERSPECTIVEPROJECTION_H_
#define VECTOID_SCENEGRAPH_PERSPECTIVEPROJECTION_H_

#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/GroupNode.h>

namespace Vectoid {
namespace SceneGraph {

//! Perspective screen projection, defining a frustum-shaped viewing volume.
class PerspectiveProjection : public GroupNode {
  public:
    PerspectiveProjection(const PerspectiveProjection &other) = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;

    //! Sets the size in camera space of the rectangular "window" on the near clipping plane.
    void SetWindowSize(float windowSize, bool identifyWithLargerViewPortDimension);
    //! Retrieves the property set by SetWindowSize().
    float WindowSize() const;
    //! Sets the distance in camera space between near and far clipping planes.
    void SetViewingDepth(float viewingDepth);
    //! Retrieves the property set by SetViewingDepth();
    float ViewingDepth() const;
    //! Sets the distance in camera space between central projection point and near clipping plane.
    void SetEyepointDistance(float eyepointDistance);
    //! Retrieves the property set by SetEyepointDistance().
    float EyepointDistance() const;
    //! Tells the projection about the dimensions of the viewport that it is going to be used for.
    void SetViewPort(float width, float height);
    //! Transforms a viewport point to camera coordinates.
    Core::Vector<float> TransformViewPortCoordinates(float x, float y) const;
    
  protected:
    PerspectiveProjection();
  
    void ComputeWindowDimensions(float *width, float *height) const;

    float eyepointDistance_;
    float viewingDepth_;
    bool  parametersChanged_;    // Will get cleared by Render() implementations.
    
  private:
    static const float paramMin;
    
    float windowSize_;
    bool  windowSizeIsLargerViewPortDimension_;
    float width_;
    float height_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_PERSPECTIVEPROJECTION_H_
