///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

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

Glyphs::Glyphs(const shared_ptr<class Context> &context)
        : SceneGraph::Glyphs(context) {
    for (int i = 0; i < 256; ++i) {
        textureSlots_[i] = GetContext()->AddResourceSlot(Context::ResourceType::Texture);
    }
}

Glyphs::~Glyphs() {
    for (int i = 0; i < 256; ++i) {
        GetContext()->RemoveResourceSlot(textureSlots_[i]);
    }
}

void Glyphs::BindGlyphTexture(uint8_t glyph) {
    optional<GLuint> texture = GetContext()->GetResource(textureSlots_[glyph]);
    if (!texture) {
        GenerateTextures();
        texture = GetContext()->GetResource(textureSlots_[glyph]);
        if (!texture) {
            if (defaultGlyph_) {
                texture = GetContext()->GetResource(textureSlots_[*defaultGlyph_]);
            }

            if (!texture) {
                Log::Print(Log::Level::Error, this, [&]{
                    return "failed to bind texture for glyph " + to_string(glyph);
                });
                return;
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, *texture);
}

void Glyphs::GenerateTextures() {
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

        if (!GetContext()->GetResource(textureSlots_[glyph])) {
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

                GetContext()->SetResource(textureSlots_[glyph], texture);
                defaultGlyph_ = glyph;
            }
        }
    }
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


