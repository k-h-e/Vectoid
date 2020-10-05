#ifndef VECTOID_SCENEGRAPH_OPENGL_TEXTCONSOLE_H_
#define VECTOID_SCENEGRAPH_OPENGL_TEXTCONSOLE_H_

#include <Vectoid/SceneGraph/TextConsole.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Text console geometry.
class TextConsole : public Vectoid::SceneGraph::TextConsole {
  public:
    friend class RenderTarget;
    
    TextConsole(const TextConsole &other)            = delete;
    TextConsole &operator=(const TextConsole &other) = delete;
    TextConsole(TextConsole &&other)                 = delete;
    TextConsole &operator=(TextConsole &&other)      = delete;
    void Render();

  private:
    TextConsole(int width, int height, float glyphWidth, float glyphHeight,
                const std::shared_ptr<SceneGraph::Glyphs> &glyphs);
    void SetColor(uint8_t colorIndex);

    uint8_t currentColorIndex_;
    
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_OPENGL_TEXTCONSOLE_H_
