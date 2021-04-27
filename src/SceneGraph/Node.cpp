#include <Vectoid/SceneGraph/Node.h>

#include <Vectoid/SceneGraph/VisitorInterface.h>

namespace Vectoid {
namespace SceneGraph {
    
Node::Node() {
    // Nop.
}

Node::~Node() {
    // Nop.
}

void Node::Visit(VisitorInterface *visitor) {
    visitor->Visit(this);
    visitor->Leave(this);
}

void Node::RenderPre() {
    // Nop.
}

void Node::RenderPost() {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
