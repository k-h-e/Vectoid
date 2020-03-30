#include <Vectoid/SceneGraph/Vulkan/TextConsole.h>

#include <string>
#include <cassert>
#include <kxm/Core/logging.h>
#include <Vectoid/SceneGraph/Glyphs.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

TextConsole::TextConsole(const shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                         const shared_ptr<Vectoid::Glyphs> &glyphs)
        : Vectoid::TextConsole(width, height, glyphWidth, glyphHeight, glyphs),
          context_(context) {
    // Nop.
}

void TextConsole::Render() {
   Core::Log().Stream() << "Vulkan::TextConsole::Render()" << endl;
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

