#include <kxm/Vectoid/SceneGraphNode.h>

#include <cstdio>
#include <cassert>

using namespace std;

namespace kxm {
namespace Vectoid {
    
SceneGraphNode::SceneGraphNode()
        : parent_(0) {
}

SceneGraphNode::~SceneGraphNode() {
    RemoveAllChildren();
}

void SceneGraphNode::AddChild(const shared_ptr<SceneGraphNode> &child) {
    assert(child->parent_ == 0);
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
