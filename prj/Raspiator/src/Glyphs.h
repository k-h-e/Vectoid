#ifndef RASPIATOR_GLYPHS_H_
#define RASPIATOR_GLYPHS_H_


#include <Vectoid/OpenGL.h>


namespace Raspiator {

//! Manages textures for text glyphs.
class Glyphs {
  public:
    Glyphs();
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    //! Binds the texture for the specified glyph.
    void BindGlyphTexture(uint8_t glyph);
    
  private:
    void GenerateTextures();
  
    static const int     numGlyphs,
                         glyphWidth, glyphHeight;
    static const uint8_t glyphData[],
                         glyphCodes[];
                         
    GLuint  textures_[256];
    uint8_t defaultGlyph_;
    bool    glResourcesPresent_,
            haveDefaultGlyph_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_GLYPHS_H_
