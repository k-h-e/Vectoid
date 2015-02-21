#include "Visualization.h"

#include <sstream>
#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include "Glyphs.h"
#include "Indicatower.h"
#include "TextConsole.h"
#include "TextRing.h"

using namespace std;
using namespace kxm::Vectoid;


namespace Raspiator {

Visualization::Visualization() {
    auto projection = make_shared<PerspectiveProjection>();
    auto camera     = make_shared<Camera>();
    projection->AddChild(camera);

    auto glyphs     = make_shared<Glyphs>();
    auto console    = make_shared<TextConsole>(20, 10, glyphs);
    auto textRing   = make_shared<TextRing>(1.0f, .1f, .22f, glyphs);
    //auto geode      = make_shared<Geode>(textRing);

    projection->SetWindowSize(1.0f);
    projection->SetViewingDepth(10.0f);
    projection->SetEyepointDistance(1.0f);

    projection_  = projection;
    camera_      = camera;
    console_     = console;
    textRing_    = textRing;
    angle_       = 0;
    counter_     = 0;

    AddIndicatower(Vector(-1.0f, 0.0f, -1.0f));
    AddIndicatower(Vector( 1.0f, 0.0f, -1.0f));
    AddIndicatower(Vector( 1.0f, 0.0f,  1.0f));
    AddIndicatower(Vector(-1.0f, 0.0f,  1.0f));
}

void Visualization::SetViewPort(int width, int height) {
    projection_->SetViewPort((float)width, (float)height);
}

void Visualization::RenderFrame() {
    // Animate...
    ++angle_;
    if (angle_ >= 360)
        angle_ = 0;

    if (!(angle_ % 20)) {
        stringstream txt;
        txt << "Hallo Maus! (" << counter_ << ")";
        console_->WriteLine(txt.str());
        textRing_->SetText(txt.str());
        ++counter_;
    }

    // Animate camera...
    float flightRadius = 4.0f,
          flightHeight = 4.0f;
    Vector position(flightRadius, flightHeight, 0.0f);
    Transform(YAxis, angle_).ApplyTo(&position);
    Vector viewDirection(-position);
    viewDirection.Normalize();
    Vector u(-viewDirection.z, 0.0f, viewDirection.x);
    u.Normalize();
    Vector v = CrossProduct(u, viewDirection);
    v.Normalize();    // Not really necessary.
    camera_->SetTransform(Transform(u, v, -viewDirection));
    camera_->SetPosition(position);

    // Render...
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection_->Render(nullptr);
}

void Visualization::AddIndicatower(const Vector &position) {
    auto tower    = make_shared<Indicatower>(.5f, 30, .002f);
    auto geode    = make_shared<Geode>(tower);
    auto coordSys = make_shared<CoordSys>();
    coordSys->AddChild(geode);
    coordSys->SetPosition(position);
    camera_->AddChild(coordSys);

    tower->SetCounts(300, 400);
}

}
