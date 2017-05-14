#ifndef KXM_VECTOID_GLYPHS_H_
#define KXM_VECTOID_GLYPHS_H_


#include <kxm/Vectoid/OpenGL.h>

namespace kxm {
namespace Vectoid {

//! Manages textures for text glyphs.
/*! 
 *  \ingroup Vectoid
 */
class Glyphs {
  public:
    Glyphs();
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    //! Binds the texture for the specified glyph, if present.
    void BindGlyphTexture(uint8_t glyph);
    
  private:
    static const int     numGlyphs,
                         glyphWidth, glyphHeight;
    static const uint8_t glyphData[],
                         glyphCodes[];
  
    void GenerateTextures();
                         
    GLuint  textures_[256];
    uint8_t defaultGlyph_;
    bool    glResourcesPresent_,
            haveDefaultGlyph_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_GLYPHS_H_
