///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_TEXTCONSOLE_H_
#define VECTOID_SCENEGRAPH_TEXTCONSOLE_H_

#include <memory>
#include <vector>
#include <Vectoid/Core/BoundingBox.h>
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
                       LightBlue,
                       Custom     };

    TextConsole()                                    = delete;
    TextConsole(const TextConsole &other)            = delete;
    TextConsole &operator=(const TextConsole &other) = delete;
    TextConsole(TextConsole &&other)                 = delete;
    TextConsole &operator=(TextConsole &&other)      = delete;
    
    //! Writes the specified line of text to the console, wrapping it into multiple rows if necessary.
    /*!
     *  \note Encoding is ASCII for now.
     */
    void WriteLine(const std::string &line, Color color);
    //! Writes text at specified coordinates, without breaking into any new lines.
    /*!
     *  Does not change the \ref WriteLine() cursor.
     */
    void WriteAt(int column, int row, const char *text, Color color);
    //! Clears the specified row.
    void ClearRow(int row);
    //! Clears the entire console.
    void Clear();
    //! Resizes the text console as specified, clearing it in the process.
    void Resize(int width, int height);
    //! Tells the text console's bounding box.
    Core::BoundingBox<float> BoundingBox() const;
    //! Toggles rendering of the console background, default is on.
    void EnableBackground(bool enabled);
    //! Sets the console's background color, including its alpha channel.
    void SetBackgroundColor(const Vectoid::Core::Vector<float> &color, float alpha);
    //! Sets the console's custom text color.
    void SetCustomColor(const Vectoid::Core::Vector<float> &color);
    //! Toggles rendering of the console frame, default is off.
    void EnableFrame(bool enabled);
    //! Sets the console's frame width.
    void SetFrameWidth(float width);
    //! Sets the console's frame color.
    void SetFrameColor(const Vectoid::Core::Vector<float> &color);

  protected:
    TextConsole(const std::shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                const std::shared_ptr<Glyphs> &glyphs);
  
    int                          width_;
    int                          height_;
    float                        glyphWidth_;
    float                        glyphHeight_;
    float                        frameWidth_;
    std::shared_ptr<Glyphs>      glyphs_;
    std::vector<uint8_t>         buffer_;
    std::vector<uint8_t>         colorBuffer_;
    Vectoid::Core::Vector<float> backgroundColor_;
    float                        backgroundAlpha_;
    Vectoid::Core::Vector<float> customColor_;
    bool                         backgroundEnabled_;
    Vectoid::Core::Vector<float> frameColor_;
    bool                         frameEnabled_;
    
  private:
    void FinishLine();
  
    int     currentRow_;
    int     numLeftInCurrentRow_;
    uint8_t *writePosition_;
    uint8_t *colorWritePosition_;
    bool    linesFinished_;
};

}    // Namespace SceneGraph;
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_TEXTCONSOLE_H_
