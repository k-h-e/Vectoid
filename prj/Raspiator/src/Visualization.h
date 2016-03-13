#ifndef RASPIATOR_VISUALIZATION_H_
#define RASPIATOR_VISUALIZATION_H_


#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <random>
#include <Vectoid/Vector.h>


namespace kxm {
namespace Vectoid {
    class PerspectiveProjection;
    class Camera;
    class CoordSys;
}
}

namespace Raspiator {

class Glyphs;

class Visualization {
  public:
    Visualization(float glyphWidth, float glyphHeight);
    Visualization(const Visualization &other)            = delete;
    Visualization &operator=(const Visualization &other) = delete;
    Visualization(Visualization &&other)                 = delete;
    Visualization &operator=(Visualization &&other)      = delete;
    void SetViewPort(int width, int height);
    void RenderFrame();

  private:
    std::shared_ptr<kxm::Vectoid::PerspectiveProjection>      projection_;
    std::shared_ptr<kxm::Vectoid::Camera>                     camera_;
    std::shared_ptr<Glyphs>                                   glyphs_;
    float                                                     glyphWidth_, glyphHeight_;
    std::shared_ptr<kxm::Vectoid::CoordSys>                   coordSys_;

    std::chrono::time_point<std::chrono::steady_clock>        lastFrameTime_;
    std::default_random_engine                                random_;
};

}    // Namespace Raspiator.

#endif    // RASPIATOR_VISUALIZATION_H_

