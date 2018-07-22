#include <kxm/Vectoid/Metal/TextConsole.h>

#include <string>
#include <cassert>
#include <kxm/Vectoid/Glyphs.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Metal {

TextConsole::TextConsole(int width, int height, float glyphWidth, float glyphHeight,
                         shared_ptr<Vectoid::Glyphs> glyphs)
        : Vectoid::TextConsole(width, height, glyphWidth, glyphHeight, glyphs) {
    // Nop.
}

void TextConsole::Render() {
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

