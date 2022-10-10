#ifndef VECTOID_SCENEGRAPH_OPENGL_COMBOBARREL_H_
#define VECTOID_SCENEGRAPH_OPENGL_COMBOBARREL_H_

#include <Vectoid/SceneGraph/ComboBarrel.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;

//! UI element comparable to a combo-box.
class ComboBarrel : public SceneGraph::ComboBarrel {
public:
    ComboBarrel()                                    = delete;
    ComboBarrel(const std::shared_ptr<Context> &context, int width, int numVisibleOtherPerSide, float glyphWidth,
                float glyphHeight, const std::shared_ptr<SceneGraph::Glyphs> &glyphs);
    ComboBarrel(const ComboBarrel &other)            = delete;
    ComboBarrel &operator=(const ComboBarrel &other) = delete;
    ComboBarrel(ComboBarrel &&other)                 = delete;
    ComboBarrel &operator=(ComboBarrel &&other)      = delete;
    ~ComboBarrel()                                   = default;
    
    void Render() override;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_COMBOBARREL_H_
