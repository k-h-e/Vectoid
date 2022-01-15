#ifndef VECTOID_SCENEGRAPH_OPENGL_GLYPHS_H_
#define VECTOID_SCENEGRAPH_OPENGL_GLYPHS_H_

#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;

//! Manages textures for text glyphs.
class Glyphs : public SceneGraph::Glyphs {
  public:
    Glyphs()                               = delete;
    Glyphs(const std::shared_ptr<Context> &context);
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    void BindGlyphTexture(uint8_t glyph) override;
    
  private:
    void GenerateTextures();
                         
    GLuint  textures_[256];
    uint8_t defaultGlyph_;
    bool    glResourcesPresent_,
            haveDefaultGlyph_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_OPENGL_GLYPHS_H_
