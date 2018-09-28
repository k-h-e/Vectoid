#ifndef KXM_VECTOID_TEXTCONSOLE_H_
#define KXM_VECTOID_TEXTCONSOLE_H_

#include <memory>
#include <vector>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Vectoid {

class Glyphs;

//! Text console geometry.
/*! 
 *  \ingroup Vectoid
 */
class TextConsole : public virtual GeometryInterface {
  public:
    TextConsole(const TextConsole &other)            = delete;
    TextConsole &operator=(const TextConsole &other) = delete;
    TextConsole(TextConsole &&other)                 = delete;
    TextConsole &operator=(TextConsole &&other)      = delete;
    
    //! Writes the specified line of text to the console, wrapping it into multiple rows if necessary.
    /*!
     *  \note Encoding is ASCII for now.
     */
    void WriteLine(const char *line);
    //! Writes text at specified coordinates, without breaking into any new lines.
    /*!
     *  Does not change the \ref WriteLine() cursor.
     */
    void WriteAt(int column, int row, const char *text);
    //! Resizes the text console as specified, clearing it in the process.
    void Resize(int width, int height);
    
  protected:
    TextConsole(int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<Glyphs> &glyphs);
  
    int                     width_, height_,
                            rowCursor_;
    float                   glyphWidth_, glyphHeight_;
    std::vector<uint8_t>    buffer_;
    std::shared_ptr<Glyphs> glyphs_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_TEXTCONSOLE_H_
