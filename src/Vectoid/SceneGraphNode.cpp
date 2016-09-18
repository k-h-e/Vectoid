#include <kxm/Vectoid/SceneGraphNode.h>

#include <cstdio>
#include <cassert>

using namespace std;

namespace kxm {
namespace Vectoid {
    
SceneGraphNode::SceneGraphNode() {
    // Nop.
}

SceneGraphNode::~SceneGraphNode() {
    RemoveAllChildren();
}

void SceneGraphNode::AddChild(const shared_ptr<SceneGraphNode> &child) {
    children_.push_back(child);
}

void SceneGraphNode::RemoveChild(const std::shared_ptr<SceneGraphNode> &child) {
    std::vector<std::shared_ptr<SceneGraphNode>> oldChildren = children_;
    children_.clear();
    for (const std::shared_ptr<SceneGraphNode> &aChild : oldChildren) {
        if (aChild != child) {
            children_.push_back(aChild);
        }
    }
}

void SceneGraphNode::RemoveAllChildren() {
    children_.clear();
}

void SceneGraphNode::Render(RenderContext *context) {
    for (int i = 0; i < children_.size(); i++)
        children_[i]->Render(context);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
