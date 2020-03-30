#ifndef VECTOID_SCENEGRAPH_VULKAN_TEXTCONSOLE_H_
#define VECTOID_SCENEGRAPH_VULKAN_TEXTCONSOLE_H_

#include <Vectoid/SceneGraph/TextConsole.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;
class Context;

//! Text console geometry.
/*! 
 *  \ingroup VectoidVulkan
 */
class TextConsole : public Vectoid::SceneGraph::TextConsole {
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
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_TEXTCONSOLE_H_
