#ifndef RASPIATOR_TEXTCONSOLE_H_
#define RASPIATOR_TEXTCONSOLE_H_


#include <memory>
#include <vector>
#include <Vectoid/GeometryInterface.h>


namespace Raspiator {

class Glyphs;

//! Text console geometry.
class TextConsole : public virtual kxm::Vectoid::GeometryInterface {
  public:
    TextConsole(int width, int height, float glyphWidth, float glyphHeight,
                std::shared_ptr<Glyphs> glyphs);
    TextConsole(const TextConsole &other)            = delete;
    TextConsole &operator=(const TextConsole &other) = delete;
    TextConsole(TextConsole &&other)                 = delete;
    TextConsole &operator=(TextConsole &&other)      = delete;
    
    //! Writes the specified line of text to the console, wrapping it into multiple rows if
    //! necessary.
    /*!
     *  \note Encoding is ASCII for now.
     */
    void WriteLine(const std::string &line);
    //! Resizes the text console as specified, clearing it in the process.
    void Resize(int width, int height);

    void Render(kxm::Vectoid::RenderContext *context);
    
  private:
    int                     width_, height_,
                            rowCursor_;
    float                   glyphWidth_, glyphHeight_;
    std::vector<uint8_t>    buffer_;
    std::shared_ptr<Glyphs> glyphs_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_TEXTCONSOLE_H_
