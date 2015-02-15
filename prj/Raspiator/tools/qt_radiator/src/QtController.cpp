#include "QtController.h"

#include <iostream>

#include <QTimer>

#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>

#include "Glyphs.h"
#include "Indicatower.h"
#include "TextConsole.h"
#include "QtGLDisplay.h"

using namespace std;
using namespace kxm::Vectoid;


namespace Raspiator {

QtController::QtController() {
    auto projection = make_shared<PerspectiveProjection>();
    auto camera     = make_shared<Camera>();
    auto coordSys   = make_shared<CoordSys>();
    auto tower      = make_shared<Indicatower>();
    auto glyphs     = make_shared<Glyphs>();
    auto console    = make_shared<TextConsole>(10, 4, glyphs);
    auto geode      = make_shared<Geode>(console);
    //auto geode      = make_shared<Geode>(tower);
    projection->AddChild(camera);
    camera->AddChild(coordSys);
    coordSys->AddChild(geode);

    projection->SetWindowSize(1.0f);
    projection->SetViewingDepth(4.0f);
    projection->SetEyepointDistance(1.0f);
    camera->SetPosition(Vector(0.0f, 0.5f, 2.5f));

    auto timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(ProcessTimer()));
    timer->start(0);

    projection_ = projection;
    coordSys_   = coordSys;
    angle_      = 0;
}

void QtController::SetView(std::shared_ptr<QtGLDisplay> view) {
    view_ = view;
}

shared_ptr<PerspectiveProjection> QtController::Projection() {
    return projection_;
}

void QtController::ProcessTimer() {
    ++angle_;
    if (angle_ >= 360)
        angle_ = 0;
    Transform transform(ZAxis, (float)angle_);
    coordSys_->SetTransform(transform);
    QtGLDisplay *view = view_.get();
    if (view)
        view->update();
}

}    // Namespace Raspiator.
