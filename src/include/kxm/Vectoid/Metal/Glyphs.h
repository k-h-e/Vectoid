#ifndef KXM_VECTOID_METAL_GLYPHS_H_
#define KXM_VECTOID_METAL_GLYPHS_H_

#include <memory>
#include <kxm/Vectoid/Glyphs.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

class Context;

//! Manages textures for text glyphs.
/*! 
 *  \ingroup VectoidMetal
 */
class Glyphs : public Vectoid::Glyphs {
  public:
    Glyphs(const std::shared_ptr<Context> &context);
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    //! Binds the texture for the specified glyph, if present.
    void BindGlyphTexture(uint8_t glyph);
    
  private:
    std::shared_ptr<Context> context_;
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_METAL_GLYPHS_H_
