#include <Zarch/Video/Lander.h>

#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include <Zarch/LanderGeometry.h>
#include <Zarch/Events/MoveEvent.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Lander::Lander(const shared_ptr<Vectoid::Camera> &camera)
        : camera_(camera) {
    coordSys_ = shared_ptr<CoordSys>(new CoordSys());
    shared_ptr<LanderGeometry> landerGeometry(new LanderGeometry());
    coordSys_->AddChild(shared_ptr<Geode>(new Geode(landerGeometry)));
}

const shared_ptr<CoordSys> &Lander::RootNode() const {
    return coordSys_;
}

void Lander::Handle(const MoveEvent &event) {
    coordSys_->SetTransform(event.transform);
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
