#ifndef KXM_VECTOID_GLYPHS_H_
#define KXM_VECTOID_GLYPHS_H_

#include <kxm/Core/Interface.h>

#include <stdint.h>

namespace kxm {
namespace Vectoid {

//! Manages textures for text glyphs.
/*! 
 *  \ingroup Vectoid
 */
class Glyphs : public virtual Core::Interface {
  public:
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    //! Binds the texture for the specified glyph, if present.
    virtual void BindGlyphTexture(uint8_t glyph) = 0;
    
  protected:
    Glyphs();
  
    static const int     numGlyphs,
                         glyphWidth, glyphHeight;
    static const uint8_t glyphData[],
                         glyphCodes[];
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_GLYPHS_H_
