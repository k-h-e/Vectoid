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
    // Nop.
}

void SceneGraphNode::AddChild(const shared_ptr<SceneGraphNode> &child) {
    children_.push_back(child);
}

void SceneGraphNode::AddAsLastChild(const shared_ptr<SceneGraphNode> &child) {
    lastChild_ = child;
}

void SceneGraphNode::RemoveChild(const std::shared_ptr<SceneGraphNode> &child) {
    std::vector<std::shared_ptr<SceneGraphNode>> oldChildren = children_;
    children_.clear();
    for (const std::shared_ptr<SceneGraphNode> &aChild : oldChildren) {
        if (aChild != child) {
            children_.push_back(aChild);
        }
    }
    if (lastChild_ == child) {
        lastChild_.reset();
    }
}

void SceneGraphNode::RemoveAllChildren() {
    children_.clear();
    lastChild_.reset();
}

void SceneGraphNode::Render(RenderContext *context) {
    for (auto &child : children_) {
        child->Render(context);
    }
    if (lastChild_) {
        lastChild_->Render(context);
    }
}

}    // Namespace Vectoid.
}    // Namespace kxm.
