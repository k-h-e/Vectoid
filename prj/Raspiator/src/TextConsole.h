#ifndef RASPIATOR_TEXTCONSOLE_H_
#define RASPIATOR_TEXTCONSOLE_H_


#include <memory>
#include <vector>
#include <Vectoid/GeometryInterface.h>


namespace Raspiator {

class Glyphs;

//! Text console geometry.
class TextConsole : public virtual kxm::Vectoid::GeometryInterface {
  public:
    TextConsole(int width, int height, std::shared_ptr<Glyphs> glyphs);
    TextConsole(const TextConsole &other)            = delete;
    TextConsole &operator=(const TextConsole &other) = delete;
    TextConsole(TextConsole &&other)                 = delete;
    TextConsole &operator=(TextConsole &&other)      = delete;
    
    void Render(kxm::Vectoid::RenderContext *context);
    
  private:
    int                     width_, height_;
    std::vector<uint8_t>    buffer_;
    std::shared_ptr<Glyphs> glyphs_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_TEXTCONSOLE_H_
