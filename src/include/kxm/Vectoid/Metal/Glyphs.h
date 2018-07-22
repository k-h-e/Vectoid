#ifndef KXM_VECTOID_METAL_GLYPHS_H_
#define KXM_VECTOID_METAL_GLYPHS_H_

#include <kxm/Vectoid/Glyphs.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

//! Manages textures for text glyphs.
/*! 
 *  \ingroup VectoidMetal
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
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_METAL_GLYPHS_H_
