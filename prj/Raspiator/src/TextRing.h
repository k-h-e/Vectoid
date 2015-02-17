#ifndef RASPIATOR_TEXTRING_H_
#define RASPIATOR_TEXTRING_H_


#include <memory>
#include <vector>
#include <Vectoid/GeometryInterface.h>
#include <Vectoid/OpenGL.h>


namespace Raspiator {

class Glyphs;

//! Geometry rendering a string of text in ring shape.
class TextRing : public virtual kxm::Vectoid::GeometryInterface {
  public:
    TextRing(float radius, float glyphWidth, float glyphHeight, std::shared_ptr<Glyphs> glyphs);
    TextRing(const TextRing &other)            = delete;
    TextRing &operator=(const TextRing &other) = delete;
    TextRing(TextRing &&other)                 = delete;
    TextRing &operator=(TextRing &&other)      = delete;

    //! Sets the specified text, which will be shortened if necessary to the available number of
    //! glyph slots.
    /*!
     *  \note Encoding is ASCII for now.
     */
    void SetText(const std::string &text);
    void Render(kxm::Vectoid::RenderContext *context);
    
  private:
    std::shared_ptr<Glyphs> glyphs_;
    std::vector<GLfloat>    vertexBuffer_;
    std::vector<uint8_t>    buffer_;
    int                     numSlots_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_TEXTRING_H_
