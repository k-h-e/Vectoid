#include "TextRing.h"

#include <vector>
#include <string>
#include <cassert>
#include <Vectoid/Transform.h>

#include "Glyphs.h"

using namespace std;
using namespace kxm::Vectoid;


namespace Raspiator {

TextRing::TextRing(float radius, float glyphWidth, float glyphHeight, shared_ptr<Glyphs> glyphs)
        : glyphs_(glyphs),
          numSlots_(0) {
    assert(radius      > 0.0f);
    assert(glyphWidth  > 0.0f);
    assert(glyphHeight > 0.0f);

    float angleStep = 10.0f;    // TODO: Calculate this.

    vector<Vector> innerPoints;
    float angle = 0.0f;
    while (angle <= 360.0f) {
        Transform rotation(ZAxis, angle);
        Vector    arm(radius, 0.0f, 0.0f);
        rotation.ApplyTo(&arm);
        innerPoints.push_back(arm);
        angle += angleStep;
    }

    Vector lastInner;
    bool   fresh = true;
    for (Vector &inner : innerPoints) {
        if (fresh) {
            lastInner = inner;
            fresh     = false;
            continue;
        }

        Vector segment = inner - lastInner,
               normal(-segment.y, segment.x, 0.0f);
        normal.Normalize();
        Vector outer     = inner     - glyphHeight*normal,
               lastOuter = lastInner - glyphHeight*normal;
        vertexBuffer_.push_back(lastOuter.x);
        vertexBuffer_.push_back(lastOuter.y);
        vertexBuffer_.push_back(0.0f);
        vertexBuffer_.push_back(outer.x);
        vertexBuffer_.push_back(outer.y);
        vertexBuffer_.push_back(0.0f);
        vertexBuffer_.push_back(inner.x);
        vertexBuffer_.push_back(inner.y);
        vertexBuffer_.push_back(0.0f);
        vertexBuffer_.push_back(lastOuter.x);
        vertexBuffer_.push_back(lastOuter.y);
        vertexBuffer_.push_back(0.0f);
        vertexBuffer_.push_back(inner.x);
        vertexBuffer_.push_back(inner.y);
        vertexBuffer_.push_back(0.0f);
        vertexBuffer_.push_back(lastInner.x);
        vertexBuffer_.push_back(lastInner.y);
        vertexBuffer_.push_back(0.0f);

        ++numSlots_;
        lastInner = inner;
    }
}

void TextRing::SetText(const std::string &text) {
    buffer_.clear();
    for (const char &c : text) {
        if ((int)buffer_.size() >= numSlots_)
            break;
        buffer_.push_back((uint8_t)c);
    }
}

void TextRing::Render(RenderContext *context) {
    GLfloat texCoords[] = { 0.0f, 0.0f,
                            1.0f, 0.0f, 
                            1.0f, 1.0f,
                            
                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f  };
    
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
   	glEnableClientState(GL_VERTEX_ARRAY);
   	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    GLfloat *ptr = &vertexBuffer_[0];
    for (uint8_t &glyph : buffer_) {
        glyphs_->BindGlyphTexture(glyph);
        glVertexPointer(3, GL_FLOAT, 0, ptr);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        ptr += 18;
    }

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

}    // Namespace Raspiator.

