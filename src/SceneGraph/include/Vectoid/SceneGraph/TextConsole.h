#ifndef VECTOID_SCENEGRAPH_TEXTCONSOLE_H_
#define VECTOID_SCENEGRAPH_TEXTCONSOLE_H_

#include <memory>
#include <vector>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
namespace SceneGraph {

class Glyphs;

//! Text console geometry.
class TextConsole : public Geometry {
  public:
    enum class Color { White,
                       Grey,
                       Green,
                       Yellow,
                       Red,
                       LightBlue };

    TextConsole()                                    = delete;
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
    //! Sets the console's background color, including its alpha channel.
    void SetBackgroundColor(const Vectoid::Core::Vector<float> &color, float alpha);

  protected:
    TextConsole(const std::shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                const std::shared_ptr<Glyphs> &glyphs);
  
    int                          width_;
    int                          height_;
    int                          rowCursor_;
    float                        glyphWidth_;
    float                        glyphHeight_;
    std::vector<uint8_t>         buffer_;
    std::vector<uint8_t>         colorBuffer_;
    Vectoid::Core::Vector<float> backgroundColor_;
    float                        backgroundAlpha_;
    std::shared_ptr<Glyphs>      glyphs_;
};

}    // Namespace SceneGraph;
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_TEXTCONSOLE_H_
