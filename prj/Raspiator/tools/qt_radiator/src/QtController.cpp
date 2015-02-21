#include "QtController.h"

#include <QTimer>
#include "QtGLDisplay.h"

using namespace std;


namespace Raspiator {

QtController::QtController(shared_ptr<QtGLDisplay> display,
                           shared_ptr<Visualization> visualization)
        : display_(display),
          visualization_(visualization) {
    auto timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(ProcessTimer()));
    timer->start(0);
}

void QtController::ProcessTimer() {
    display_->update();
}

}    // Namespace Raspiator.
