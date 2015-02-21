#ifndef RASPIATOR_VISUALIZATION_H_
#define RASPIATOR_VISUALIZATION_H_


#include <memory>


namespace kxm {
namespace Vectoid {
    class PerspectiveProjection;
    class Camera;
    class Vector;
}
}

namespace Raspiator {

class TextConsole;
class TextRing;

class Visualization {
  public:
    Visualization();
    Visualization(const Visualization &other)            = delete;
    Visualization &operator=(const Visualization &other) = delete;
    Visualization(Visualization &&other)                 = delete;
    Visualization &operator=(Visualization &&other)      = delete;
    void SetViewPort(int width, int height);
    void RenderFrame();

  private:
    void AddIndicatower(const kxm::Vectoid::Vector &position);

    std::shared_ptr<kxm::Vectoid::PerspectiveProjection> projection_;
    std::shared_ptr<kxm::Vectoid::Camera>                camera_;
    std::shared_ptr<TextConsole>                         console_;
    std::shared_ptr<TextRing>                            textRing_;
    int                                                  angle_,
                                                         counter_;
};

}    // Namespace Raspiator.

#endif    // RASPIATOR_VISUALIZATION_H_

