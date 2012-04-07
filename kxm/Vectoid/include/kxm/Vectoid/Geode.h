//
//  Geode.h
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_GEODE_H_
#define KXM_VECTOID_GEODE_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Vectoid/SceneGraphNode.h>
#include <kxm/Vectoid/GeometryInterface.h>


namespace kxm {
namespace Vectoid {

//! This scene graph node represents actual geometry in the scene (geode = geometry node).
/*! 
 *  \ingroup Vectoid
 */ 
class Geode : public SceneGraphNode {
  public:
    Geode(const boost::shared_ptr<GeometryInterface> &geometry);
    void Render(RenderContext *context);
    
  private:
    Geode(const Geode &other);
    Geode &operator=(const Geode &other);
    
    boost::shared_ptr<GeometryInterface> geometry_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_GEODE_H_
