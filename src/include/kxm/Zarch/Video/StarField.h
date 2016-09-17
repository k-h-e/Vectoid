#ifndef KXM_ZARCH_VIDEO_STARFIELD_H_
#define KXM_ZARCH_VIDEO_STARFIELD_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Zarch/Video/Video.h>

namespace kxm {

namespace Vectoid {
    class Particles;
}

namespace Zarch {
namespace Video {

struct Data;

//! Controls the star field particles.
/*!
 *  \ingroup ZarchVideo
 */
class StarField : public virtual Core::ActionInterface {
  public:
    StarField(std::shared_ptr<Data> data, std::shared_ptr<Vectoid::Particles> particles);
    void ExecuteAction();
    
  private:
    StarField(const StarField &other);
    StarField &operator=(const StarField &other);
    
    std::shared_ptr<Data>               data_;
    std::shared_ptr<Vectoid::Particles> particles_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_VIDEO_STARFIELD_H_
