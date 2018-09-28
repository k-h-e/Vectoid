#ifndef KXM_VECTOID_VULKAN_GLYPHS_H_
#define KXM_VECTOID_VULKAN_GLYPHS_H_

#include <memory>
#include <kxm/Vectoid/Glyphs.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class RenderTarget;
class Context;

//! Manages textures for text glyphs.
/*! 
 *  \ingroup VectoidVulkan
 */
class Glyphs : public Vectoid::Glyphs {
  public:
    friend class RenderTarget;
    
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    //! Binds the texture for the specified glyph, if present.
    void BindGlyphTexture(uint8_t glyph);
    
  private:
    Glyphs(const std::shared_ptr<Context> &context);
  
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_VULKAN_GLYPHS_H_
