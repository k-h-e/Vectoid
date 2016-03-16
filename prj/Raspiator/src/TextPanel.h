#ifndef RASPIATOR_TEXTPANEL_H_
#define RASPIATOR_TEXTPANEL_H_

#include <memory>
#include <kxm/Core/Interface.h>


namespace kxm {
namespace Vectoid {
    class SceneGraphNode;
    class Geode;
}
}

namespace Raspiator {

class Glyphs;
class Cuboid;
class TextConsole;

//! Groups together a cuboid and a text console, forming a text panel.
class TextPanel : public virtual kxm::Core::Interface {
  public:
    TextPanel(int widthCharacters, int heightCharacters, float glyphWidth, float glyphHeight, float margin,
              float depth, std::shared_ptr<Glyphs> glyphs);
    TextPanel(const TextPanel &other)            = delete;
    TextPanel &operator=(const TextPanel &other) = delete;
    TextPanel(TextPanel &&other)                 = delete;
    TextPanel &operator=(TextPanel &&other)      = delete;

    //! Writes the specified line of text to the console, wrapping it into multiple rows if
    //! necessary.
    /*!
     *  \note Encoding is ASCII for now.
     */
    void WriteLine(const std::string &line);
    //! Resizes the text panel as specified.
    void Resize(int widthCharacters, int heightCharacters);
    //! Returns the root of the text panel tree.
    std::shared_ptr<kxm::Vectoid::SceneGraphNode> Root();

  private:
    std::shared_ptr<kxm::Vectoid::Geode> geode_;
    std::shared_ptr<Cuboid>              cuboid_;
    std::shared_ptr<TextConsole>         textConsole_;
    float                                glyphWidth_, glyphHeight_,
                                         margin_,
                                         depth_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_TEXTPANEL_H_
