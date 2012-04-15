//
//  GeometryInterface.h
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KXM_VECTOID_GEOMETRYINTERFACE_H_
#define KXM_VECTOID_GEOMETRYINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Vectoid {

class RenderContext;

//! Interface to entities representing actual geometry.
/*! 
 *  \ingroup Vectoid
 */ 
class GeometryInterface : public virtual Core::Interface {
  public:
    //! Renders the geometry.
    virtual void Render(RenderContext *context) = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_GEOMETRYINTERFACE_H_
