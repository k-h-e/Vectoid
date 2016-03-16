#ifndef RASPIATOR_JOBPANEL_H_
#define RASPIATOR_JOBPANEL_H_

#include <memory>
#include <string>
#include <kxm/Core/Interface.h>


namespace kxm {
namespace Vectoid {
    class SceneGraphNode;
}
}

namespace Raspiator {

class Glyphs;
class TextPanel;

//! Default job panel for the radiator.
class JobPanel : public virtual kxm::Core::Interface {
  public:
    JobPanel(int widthCharacters, float glyphWidth, float glyphHeight, float margin, float depth,
             std::shared_ptr<Glyphs> glyphs);
    JobPanel(const JobPanel &other)            = delete;
    JobPanel &operator=(const JobPanel &other) = delete;
    JobPanel(JobPanel &&other)                 = delete;
    JobPanel &operator=(JobPanel &&other)      = delete;

    //! Sets the main text to display in the job panel.
    void SetText(const std::string &text);
    //! Returns the root of the panel tree.
    std::shared_ptr<kxm::Vectoid::SceneGraphNode> Root();

  private:
    void Layout();

    std::shared_ptr<TextPanel> mainPanel_;
    std::string                text_;
    int                        widthCharacters_;
    float                      glyphWidth_, glyphHeight_,
                               margin_,
                               depth_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_JOBPANEL_H_
