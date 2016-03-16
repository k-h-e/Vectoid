#include "Visualization.h"

#include <cassert>
#include <sstream>
#include <kxm/Core/NumberTools.h>
#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include "Glyphs.h"
#include "JobPanel.h"

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace Raspiator {

Visualization::Visualization(float glyphWidth, float glyphHeight)
        : glyphWidth_(glyphWidth),
          glyphHeight_(glyphHeight),
          lastFrameTime_(steady_clock::now()),
          time_s_(0.0f) {
    auto projection = make_shared<PerspectiveProjection>();
    projection->SetWindowSize(1.0f);
    projection->SetViewingDepth(11.0f);
    projection->SetEyepointDistance(1.0f);
    auto camera = make_shared<Camera>();
    projection->AddChild(camera);

    projection_  = projection;
    camera_      = camera;
    glyphs_      = make_shared<Glyphs>();

    const int   widthCharacters  = 32;
    const float margin           = .5f * glyphWidth,
                panelDepth       = glyphWidth;
    jobPanel_ = make_shared<JobPanel>(widthCharacters, glyphWidth, glyphHeight, margin, panelDepth, glyphs_);

    coordSys_ = make_shared<CoordSys>();
    coordSys_->AddChild(jobPanel_->Root());
    camera->AddChild(coordSys_);

    coordSys_->SetPosition(Vector(0.0f, 0.0f, -5.0f));
}

void Visualization::SetViewPort(int width, int height) {
    projection_->SetViewPort((float)width, (float)height);
}

void Visualization::RenderFrame() {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    float frameDeltaTime_s = (float)milliSeconds / 1000.0f;

    time_s_ += frameDeltaTime_s;
    if (time_s_ > 5.0f) {
        alternateText_ = !alternateText_;
        time_s_ = 0.0f;

        jobPanel_->SetText(alternateText_ ? "This is a long text probably spanning multiple lines in the panel."
                                          : "");
    }

    // Animate...
    coordSys_->PrependTransform(Transform(YAxis, frameDeltaTime_s * 90.0f));
    coordSys_->PrependTransform(Transform(XAxis, frameDeltaTime_s * 40.0f));

    // Render...
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection_->Render(nullptr);
}

}    // Namespace Raspiator.
