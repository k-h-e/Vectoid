#include "Visualization.h"

#include <cassert>
#include <sstream>
#include <kxm/Core/NumberTools.h>
#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include "Glyphs.h"
#include "Cuboid.h"
#include "TextConsole.h"

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace Raspiator {

Visualization::Visualization(float glyphWidth, float glyphHeight)
        : glyphWidth_(glyphWidth),
          glyphHeight_(glyphHeight),
          lastFrameTime_(steady_clock::now()) {
    auto projection = make_shared<PerspectiveProjection>();
    projection->SetWindowSize(1.0f);
    projection->SetViewingDepth(11.0f);
    projection->SetEyepointDistance(1.0f);
    auto camera = make_shared<Camera>();
    projection->AddChild(camera);

    projection_  = projection;
    camera_      = camera;
    glyphs_      = make_shared<Glyphs>();

    const int   widthCharacters  = 32,
                heightCharacters =  4;
    const float margin           = .5f * glyphWidth,
                cuboidDepth      = glyphWidth;
    auto cuboid      = make_shared<Cuboid>((float)widthCharacters*glyphWidth + 2.0f*margin,
                                           (float)heightCharacters*glyphHeight + 2.0f*margin,
                                           cuboidDepth,
                                           Vector(.8f, .2f, .2f));
    auto cuboidGeode = make_shared<Geode>(cuboid);
    auto coordSys    = make_shared<CoordSys>();
    coordSys->AddChild(cuboidGeode);

    auto textConsole  = make_shared<TextConsole>(widthCharacters, heightCharacters, glyphWidth, glyphHeight, glyphs_);
    auto textGeode    = make_shared<Geode>(textConsole);
    auto textCoordSys = make_shared<CoordSys>();
    textCoordSys->AddChild(textGeode);
    textCoordSys->SetPosition(Vector(0.0f, 0.0f, .5f*cuboidDepth + .001f));
    coordSys->AddChild(textCoordSys);

    camera->AddChild(coordSys);

    textConsole->WriteLine("msside_src_infix_parser");
    textConsole->WriteLine("Implemented infix expression parsing for StopRuleCondition inspector.");
    coordSys->SetPosition(Vector(0.0f, 0.0f, -5.0f));

    coordSys_ = coordSys;
}

void Visualization::SetViewPort(int width, int height) {
    projection_->SetViewPort((float)width, (float)height);
}

void Visualization::RenderFrame() {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    float frameDeltaTimeS = (float)milliSeconds / 1000.0f;

    // Animate...
    coordSys_->PrependTransform(Transform(YAxis, frameDeltaTimeS * 90.0f));
    coordSys_->PrependTransform(Transform(XAxis, frameDeltaTimeS * 40.0f));

    // Render...
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection_->Render(nullptr);
}

}    // Namespace Raspiator.
