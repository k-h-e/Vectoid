//
//  Geode.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Vectoid/Geode.h>

using boost::shared_ptr;


namespace kxm {
namespace Vectoid {

Geode::Geode(const shared_ptr<GeometryInterface> &geometry) {
    assert(!!geometry);
    geometry_ = geometry;
}

void Geode::Render(RenderContext *context) {
    geometry_->Render(context);
    SceneGraphNode::Render(context);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
