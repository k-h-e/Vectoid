#ifndef KXM_VECTOID_OPENGL_GLYPHS_H_
#define KXM_VECTOID_OPENGL_GLYPHS_H_

#include <kxm/Vectoid/Glyphs.h>
#include <kxm/Vectoid/OpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! Manages textures for text glyphs.
/*! 
 *  \ingroup VectoidOpenGL
 */
class Glyphs : public Vectoid::Glyphs {
  public:
    Glyphs();
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    //! Binds the texture for the specified glyph, if present.
    void BindGlyphTexture(uint8_t glyph);
    
  private:
    void GenerateTextures();
                         
    GLuint  textures_[256];
    uint8_t defaultGlyph_;
    bool    glResourcesPresent_,
            haveDefaultGlyph_;
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_OPENGL_GLYPHS_H_
