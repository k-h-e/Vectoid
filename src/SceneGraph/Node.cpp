#include <Vectoid/SceneGraph/Node.h>

#include <Vectoid/SceneGraph/Context.h>

using std::shared_ptr;
using std::string;

namespace Vectoid {
namespace SceneGraph {
    
Node::Node(const shared_ptr<Context> &context)
        : context_(context) {
    id_ = context_->RegisterNode(this);
}

Node::~Node() {
    context_->UnregisterNode(id_);
}

void Node::SetName(const string &name) {
    name_ = name;
}

string Node::Name() const {
    return name_;
}

void Node::DropGraphicsResources() {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
