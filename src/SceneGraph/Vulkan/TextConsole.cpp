///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/TextConsole.h>

#include <string>
#include <cassert>
#include <K/Core/Log.h>
#include <Vectoid/SceneGraph/Glyphs.h>

using namespace std;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

TextConsole::TextConsole(
    const shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
    const shared_ptr<Vectoid::SceneGraph::Glyphs> &glyphs)
        : Vectoid::SceneGraph::TextConsole(width, height, glyphWidth, glyphHeight, glyphs),
          context_(context) {
    // Nop.
}

void TextConsole::Render() {
    Log::Print(Log::Level::Debug, this, []{ return "Vulkan::TextConsole::Render()"; });
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

