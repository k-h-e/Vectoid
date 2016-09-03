#include <Zarch/Video/Lander.h>

#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include <Zarch/LanderGeometry.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Lander::Lander() {
    coordSys_ = shared_ptr<CoordSys>(new CoordSys());
    shared_ptr<LanderGeometry> landerGeometry(new LanderGeometry());
    coordSys_->AddChild(shared_ptr<Geode>(new Geode(landerGeometry)));
}

const shared_ptr<CoordSys> &Lander::RootNode() const {
    return coordSys_;
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
