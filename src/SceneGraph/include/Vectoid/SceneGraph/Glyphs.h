#ifndef VECTOID_SCENEGRAPH_GLYPHS_H_
#define VECTOID_SCENEGRAPH_GLYPHS_H_

#include <stdint.h>
#include <K/Core/Interface.h>

namespace Vectoid {
namespace SceneGraph {

//! Manages textures for text glyphs.
class Glyphs : public virtual K::Core::Interface {
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

}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_GLYPHS_H_
