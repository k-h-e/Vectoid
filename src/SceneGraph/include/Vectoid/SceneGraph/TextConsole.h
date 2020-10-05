#ifndef VECTOID_SCENEGRAPH_TEXTCONSOLE_H_
#define VECTOID_SCENEGRAPH_TEXTCONSOLE_H_

#include <memory>
#include <vector>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace SceneGraph {

class Glyphs;

//! Text console geometry.
class TextConsole : public virtual GeometryInterface {
  public:
    enum class Color { White,
                       Grey,
                       Green,
                       Yellow,
                       Red     };

    TextConsole(const TextConsole &other)            = delete;
    TextConsole &operator=(const TextConsole &other) = delete;
    TextConsole(TextConsole &&other)                 = delete;
    TextConsole &operator=(TextConsole &&other)      = delete;
    
    //! Writes the specified line of text to the console, wrapping it into multiple rows if necessary.
    /*!
     *  \note Encoding is ASCII for now.
     */
    void WriteLine(const char *line, Color color);
    //! Writes text at specified coordinates, without breaking into any new lines.
    /*!
     *  Does not change the \ref WriteLine() cursor.
     */
    void WriteAt(int column, int row, const char *text, Color color);
    //! Clears the specified row.
    void ClearRow(int row);
    //! Resizes the text console as specified, clearing it in the process.
    void Resize(int width, int height);
    
  protected:
    TextConsole(int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<Glyphs> &glyphs);
  
    int                     width_;
    int                     height_;
    int                     rowCursor_;
    float                   glyphWidth_, glyphHeight_;
    std::vector<uint8_t>    buffer_;
    std::vector<uint8_t>    colorBuffer_;
    std::shared_ptr<Glyphs> glyphs_;
};

}    // Namespace SceneGraph;
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_TEXTCONSOLE_H_
