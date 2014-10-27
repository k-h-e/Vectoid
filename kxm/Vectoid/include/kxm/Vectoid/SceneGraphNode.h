//
//  SceneGraphNode.h
//  kxm
//
//  Created by Kai Hergenroether on 4/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_SCENEGRAPHNODE_H_
#define KXM_VECTOID_SCENEGRAPHNODE_H_


#include <vector>
#include <memory>

#include <kxm/Core/Interface.h>


namespace kxm {
namespace Vectoid {
    
class RenderContext;

//! Base class to all scene graph nodes.
/*! 
 *  \ingroup Vectoid
 */ 
class SceneGraphNode : public virtual Core::Interface {
  public:
    SceneGraphNode();
    ~SceneGraphNode();
    //! Adds the specified node as child of the receiver node. The child node must not already be
    //! child to another parent node.
    void AddChild(const std::shared_ptr<SceneGraphNode> &child);
    //! Removes all child nodes from the scene graph node.
    /*!
     *  For each child, data structure linkage will be properly disconnected in both parent and
     *  child.
     */
    void RemoveAllChildren();
    //! Performs a render traversal of the sub scene graph rooted in the node. This is the
    //! only scene graph node operation that is allowed to interact with <c>OpenGL</c>.
    virtual void Render(RenderContext *context);
    
  private:
    SceneGraphNode(const SceneGraphNode &other);
    SceneGraphNode &operator=(const SceneGraphNode &other);
    
    SceneGraphNode                               *parent_;     // Might be 0.
    std::vector<std::shared_ptr<SceneGraphNode>> children_;
};
    
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_SCENEGRAPHNODE_H_
