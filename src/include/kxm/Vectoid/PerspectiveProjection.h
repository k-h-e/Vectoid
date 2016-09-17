//
//  PerspectiveProjection.h
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_PERSPECTIVEPROJECTION_H_
#define KXM_VECTOID_PERSPECTIVEPROJECTION_H_


#include <kxm/Vectoid/SceneGraphNode.h>
#include <kxm/Vectoid/Vector.h>


namespace kxm {
namespace Vectoid {

//! Perspective screen projection, defining a frustum-shaped viewing volume.
/*! 
 *  \ingroup Vectoid
 */ 
class PerspectiveProjection : public SceneGraphNode {
  public:
    PerspectiveProjection();
    //! Sets the length in camera space of that dimension of the rectangular "window" on the near clipping plane that correspoinds to the larger dimension of the viewport.
    void SetWindowSize(float windowSize);
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
    Vector TransformViewPortCoordinates(float x, float y) const;
    void Render(RenderContext *context);
    
  private:
    static const float paramMin;
    PerspectiveProjection(const PerspectiveProjection &other);
    PerspectiveProjection &operator=(const PerspectiveProjection &other);
    void ComputeWindowDimensions(float *width, float *height) const;
    
    float windowSize_, eyepointDistance_, viewingDepth_,
          width_, height_;
    bool  parametersChanged_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KVM_VECTOID_PERSPECTIVEPROJECTION_H_
