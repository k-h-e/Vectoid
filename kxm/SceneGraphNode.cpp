//
//  SceneGraphNode.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Vectoid/SceneGraphNode.h>

#include <cstdio>

using boost::shared_ptr;


namespace kxm {
namespace Vectoid {
    
SceneGraphNode::SceneGraphNode()
        : parent_(0) {
}

void SceneGraphNode::AddChild(const shared_ptr<SceneGraphNode> &child) {
    children_.push_back(child);
    child->parent_ = this;
}

void SceneGraphNode::RemoveAllChildren() {
    for (int i = 0; i < children_.size(); i++)
        children_[i]->parent_ = 0;
    children_.clear();
}

void SceneGraphNode::Render(RenderContext *context) {
    for (int i = 0; i < children_.size(); i++)
        children_[i]->Render(context);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
