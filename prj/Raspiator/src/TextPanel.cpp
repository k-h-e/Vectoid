#include "TextPanel.h"

#include <cassert>
#include <Vectoid/Vector.h>
#include <Vectoid/Geode.h>
#include <Vectoid/CoordSys.h>
#include "Cuboid.h"
#include "TextConsole.h"

using namespace std;
using namespace kxm::Vectoid;


namespace Raspiator {

TextPanel::TextPanel(int widthCharacters, int heightCharacters, float glyphWidth, float glyphHeight,
                     float margin, float depth, shared_ptr<Glyphs> glyphs)
        : glyphWidth_(glyphWidth),
          glyphHeight_(glyphHeight),
          margin_(margin),
          depth_(depth) {
    cuboid_           = make_shared<Cuboid>((float)widthCharacters*glyphWidth + 2.0f*margin,
                                           (float)heightCharacters*glyphHeight + 2.0f*margin,
                                           depth, Vector(.8f, .2f, .2f));
    geode_            = make_shared<Geode>(cuboid_);
    textConsole_      = make_shared<TextConsole>(widthCharacters, heightCharacters, glyphWidth, glyphHeight, glyphs);
    auto textGeode    = make_shared<Geode>(textConsole_);
    auto textCoordSys = make_shared<CoordSys>();
    textCoordSys->AddChild(textGeode);
    textCoordSys->SetPosition(Vector(0.0f, 0.0f, .5f*depth + .001f));
    geode_->AddChild(textCoordSys);
}

void TextPanel::WriteLine(const std::string &line) {
    textConsole_->WriteLine(line);
}

void TextPanel::Resize(int widthCharacters, int heightCharacters) {
    assert(widthCharacters  > 0);
    assert(heightCharacters > 0);
    cuboid_->Resize((float)widthCharacters*glyphWidth_ + 2.0f*margin_,
                    (float)heightCharacters*glyphHeight_ + 2.0f*margin_,
                    depth_);
    textConsole_->Resize(widthCharacters, heightCharacters);
}

shared_ptr<SceneGraphNode> TextPanel::Root() {
    return geode_;
}

}    // Namespace Raspiator.
