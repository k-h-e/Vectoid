#include <kxm/Vectoid/OpenGL/Glyphs.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

Glyphs::Glyphs()
        : defaultGlyph_(0),
          glResourcesPresent_(false),
          haveDefaultGlyph_(false) {
    for (int i = 0; i < 256; ++i)
        textures_[i] = 0;
}

void Glyphs::BindGlyphTexture(uint8_t glyph) {
    if (!glResourcesPresent_) {
        GenerateTextures();
        glResourcesPresent_ = true;
    }
    GLuint texture = textures_[glyph];
    if (!texture && haveDefaultGlyph_) {
        texture = textures_[defaultGlyph_];
    }
    if (texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void Glyphs::GenerateTextures() {
    uint8_t buffer[(glyphWidth + 2) * glyphHeight * 4];
    const uint8_t *srcPtr = glyphData;
    for (int i = 0; i < numGlyphs; ++i) {
        uint8_t glyph = glyphCodes[i];
        for (int y = 0; y < glyphHeight; ++y) {
            uint8_t *destPtr = buffer + (glyphHeight - y - 1)*(glyphWidth + 2)*4;
            *destPtr++ = 255;    *destPtr++ = 255;    *destPtr++ = 255;    *destPtr++ = 0;
            for (int x = 0; x < glyphWidth; ++x) {
                *destPtr++ = 255;    *destPtr++ = 255;    *destPtr++ = 255;
                *destPtr++ = (uint8_t)255 - *srcPtr++;
            }
            *destPtr++ = 255;    *destPtr++ = 255;    *destPtr++ = 255;    *destPtr++ = 0;
        }
        
        if (textures_[glyph])
            glDeleteTextures(1, &textures_[glyph]);
        glGenTextures(1, &textures_[glyph]);
        if (textures_[glyph]) {    
            glBindTexture(GL_TEXTURE_2D, textures_[glyph]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glyphWidth + 2, glyphHeight, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, buffer);
            
            defaultGlyph_     = glyph;
            haveDefaultGlyph_ = true;
        }
    }
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.


