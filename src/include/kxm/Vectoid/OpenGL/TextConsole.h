#ifndef KXM_VECTOID_OPENGL_TEXTCONSOLE_H_
#define KXM_VECTOID_OPENGL_TEXTCONSOLE_H_

#include <kxm/Vectoid/TextConsole.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

class RenderTarget;

//! Text console geometry.
/*! 
 *  \ingroup VectoidOpenGL
 */
class TextConsole : public Vectoid::TextConsole {
  public:
    friend class RenderTarget;
    
    TextConsole(const TextConsole &other)            = delete;
    TextConsole &operator=(const TextConsole &other) = delete;
    TextConsole(TextConsole &&other)                 = delete;
    TextConsole &operator=(TextConsole &&other)      = delete;
    void Render();

  private:
    TextConsole(int width, int height, float glyphWidth, float glyphHeight,
                const std::shared_ptr<Vectoid::Glyphs> &glyphs);
    
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_OPENGL_TEXTCONSOLE_H_
