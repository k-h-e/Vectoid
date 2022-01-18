#include <Vectoid/SceneGraph/OpenGL/Glyphs.h>

#include <K/Core/Log.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>

using std::optional;
using std::shared_ptr;
using std::to_string;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Glyphs::Glyphs(const shared_ptr<Context> &context)
        : SceneGraph::Glyphs(context),
          texturesGenerated_(false) {
    // Nop.
}

Glyphs::~Glyphs() {
    DropTextures();
}

void Glyphs::BindGlyphTexture(uint8_t glyph) {
    GenerateTextures();
    optional<GLuint> texture = textures_[glyph];
    if (!texture && defaultGlyph_) {
        texture = textures_[*defaultGlyph_];
    }
    if (texture) {
        glBindTexture(GL_TEXTURE_2D, *texture);
    } else {
        Log::Print(Log::Level::Error, this, [&]{ return "failed to bind texture for glyph " + to_string(glyph); });
    }
}

void Glyphs::DropGraphicsResources() {
    DropTextures();
}

void Glyphs::GenerateTextures() {
    if (!texturesGenerated_) {
        uint8_t buffer[(glyphWidth + 2) * glyphHeight * 4];
        const uint8_t *srcPtr = glyphData;
        for (int i = 0; i < numGlyphs; ++i) {
            uint8_t glyph = glyphCodes[i];
            for (int y = 0; y < glyphHeight; ++y) {
                uint8_t *destPtr = buffer + (glyphHeight - y - 1)*(glyphWidth + 2)*4;
                *destPtr++ = 255;
                *destPtr++ = 255;
                *destPtr++ = 255;
                *destPtr++ = 0;
                for (int x = 0; x < glyphWidth; ++x) {
                    *destPtr++ = 255;
                    *destPtr++ = 255;
                    *destPtr++ = 255;
                    *destPtr++ = (uint8_t)255 - *srcPtr++;
                }
                *destPtr++ = 255;
                *destPtr++ = 255;
                *destPtr++ = 255;
                *destPtr++ = 0;
            }

            GLuint texture;
            glGenTextures(1, &texture);
            if (texture) {
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glyphWidth + 2, glyphHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                             buffer);

                textures_[glyph] = texture;
                defaultGlyph_    = glyph;
            }
        }

        texturesGenerated_ = true;
    }
}

void Glyphs::DropTextures() {
    for (int i = 0; i < 256; ++i) {
        if (textures_[i]) {
            static_cast<Context *>(context_.get())->ScheduleTextureForRelease(*textures_[i], this);
        }
        textures_[i].reset();
    }
    defaultGlyph_.reset();

    texturesGenerated_ = false;
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


