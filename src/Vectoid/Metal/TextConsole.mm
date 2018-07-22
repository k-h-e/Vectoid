#include <kxm/Vectoid/Metal/TextConsole.h>

#include <string>
#include <cassert>
#include <kxm/Vectoid/Glyphs.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Metal {

TextConsole::TextConsole(const shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                         const shared_ptr<Vectoid::Glyphs> &glyphs)
        : Vectoid::TextConsole(width, height, glyphWidth, glyphHeight, glyphs),
          context_(context) {
    // Nop.
}

void TextConsole::Render() {
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

