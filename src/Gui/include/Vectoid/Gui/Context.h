#ifndef VECTOID_GUI_CONTEXT_H_
#define VECTOID_GUI_CONTEXT_H_

#include <memory>

namespace Vectoid {
    namespace Gui {
        class RedrawRequestHandlerInterface;
    }
    namespace SceneGraph {
        class Glyphs;
        class RenderTargetInterface;
    }
}

namespace Vectoid {
namespace Gui {

//! Holds context information for GUI elements.
class Context {
  public:
    float Spacing() const { return .025f; }
    Size GlyphSize() const { return Size{.025f, .025f}; }
    void SetLayoutRequired(bool required) { layoutRequired_ = required; }
    bool LayoutRequired() const { return layoutRequired_; }
    
    const std::shared_ptr<SceneGraph::RenderTargetInterface> renderTarget;
    const std::shared_ptr<SceneGraph::Glyphs>                glyphs;
    const std::shared_ptr<RedrawRequestHandlerInterface>     redrawRequestHandler;
    
    Context(const std::shared_ptr<SceneGraph::RenderTargetInterface> &renderTarget,
            const std::shared_ptr<SceneGraph::Glyphs> &glyphs,
            const std::shared_ptr<RedrawRequestHandlerInterface> &redrawRequestHandler)
        : renderTarget(renderTarget),
          glyphs(glyphs),
          redrawRequestHandler(redrawRequestHandler),
          layoutRequired_{false} {}
    
  private:
    bool layoutRequired_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_CONTEXT_H_
