#include <Vectoid/SceneGraph/Node.h>

#include <Vectoid/SceneGraph/VisitorInterface.h>

using std::string;
using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
    
Node::Node()
        : enabled_(true) {
    // Nop.
}

Node::~Node() {
    // Nop.
}

void Node::SetName(const std::string &name) {
    name_ = name;
}

string Node::Name() const {
    return name_;
}

void Node::SetEnabled(bool enabled) {
    enabled_ = enabled;
}

bool Node::Enabled() const {
    return enabled_;
}

void Node::RenderPre() {
    // Nop.
}

void Node::RenderPost() {
    // Nop.
}

void Node::OnVisited(VisitorInterface *visitor, bool visitAll) {
    (void)visitor;
    // Nop.
}

void Visit(const shared_ptr<Node> &node, VisitorInterface *visitor, bool visitAll) {
    if (visitAll || node->Enabled()) {
        visitor->Visit(node);
        node->OnVisited(visitor, visitAll);
        visitor->Leave(node);
    }
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
