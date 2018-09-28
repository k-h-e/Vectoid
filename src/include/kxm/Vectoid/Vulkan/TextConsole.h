#ifndef KXM_VECTOID_VULKAN_TEXTCONSOLE_H_
#define KXM_VECTOID_VULKAN_TEXTCONSOLE_H_

#include <kxm/Vectoid/TextConsole.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class RenderTarget;
class Context;

//! Text console geometry.
/*! 
 *  \ingroup VectoidVulkan
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
    TextConsole(const std::shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                const std::shared_ptr<Vectoid::Glyphs> &glyphs);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_VULKAN_TEXTCONSOLE_H_
