#ifndef VECTOID_SCENEGRAPH_OPENGL_GLYPHS_H_
#define VECTOID_SCENEGRAPH_OPENGL_GLYPHS_H_

#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Manages textures for text glyphs.
class Glyphs : public Vectoid::SceneGraph::Glyphs {
  public:
    friend class RenderTarget;
    
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    //! Binds the texture for the specified glyph, if present.
    void BindGlyphTexture(uint8_t glyph);
    
  private:
    Glyphs();
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
