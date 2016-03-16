#include "JobPanel.h"

#include <cassert>
#include <kxm/Core/NumberTools.h>
#include "TextPanel.h"

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace Raspiator {

JobPanel::JobPanel(int widthCharacters, float glyphWidth, float glyphHeight, float margin, float depth,
                   shared_ptr<Glyphs> glyphs)
        : widthCharacters_(widthCharacters),
          glyphWidth_(glyphWidth),
          glyphHeight_(glyphHeight),
          margin_(margin),
          depth_(depth) {
    assert(widthCharacters_ > 0);
    mainPanel_ = make_shared<TextPanel>(widthCharacters_, 2, glyphWidth_, glyphHeight_, margin_, depth_, glyphs);
    SetText("Job Panel");
}

void JobPanel::SetText(const string &text) {
    text_ = text;
    Layout();
}

shared_ptr<SceneGraphNode> JobPanel::Root() {
    return mainPanel_->Root();
}

void JobPanel::Layout() {
    int numRows = text_.length() / widthCharacters_;
    if (text_.length() % widthCharacters_) {
        ++numRows;
    }
    NumberTools::ClampMin(&numRows, 1);
    mainPanel_->Resize(widthCharacters_, numRows);
    mainPanel_->WriteLine(text_);
}

}    // Namespace Raspiator.
