#include <Vectoid/SceneGraph/GroupNode.h>

#include <cstdio>
#include <cassert>
#include <Vectoid/SceneGraph/VisitorInterface.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {
    
GroupNode::GroupNode() {
    // Nop.
}

GroupNode::~GroupNode() {
    // Nop.
}

void GroupNode::AddChild(const shared_ptr<Node> &child) {
    children_.push_back(child);
}

void GroupNode::AddAsLastChild(const shared_ptr<Node> &child) {
    lastChild_ = child;
}

void GroupNode::RemoveChild(const std::shared_ptr<Node> &child) {
    std::vector<shared_ptr<Node>> oldChildren = children_;
    children_.clear();
    for (const shared_ptr<Node> &aChild : oldChildren) {
        if (aChild != child) {
            children_.push_back(aChild);
        }
    }
    if (lastChild_ == child) {
        lastChild_.reset();
    }
}

void GroupNode::RemoveAllChildren() {
    children_.clear();
    lastChild_.reset();
}

void GroupNode::OnVisited(VisitorInterface *visitor, bool visitAll) {
    for (shared_ptr<Node> &child : children_) {
        Visit(child, visitor, visitAll);
    }
    if (lastChild_) {
        Visit(lastChild_, visitor, visitAll);
    }
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
