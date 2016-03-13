#include <random>
#include <QApplication>
#include <Vectoid/Vector.h>
#include "Visualization.h"
#include "QtGLDisplay.h"
#include "QtController.h"

using namespace std;
using namespace kxm::Vectoid;
using namespace Raspiator;


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    auto vis        = make_shared<Visualization>(.1f, .12f);
    auto display    = make_shared<QtGLDisplay>(vis);
    auto controller = make_shared<QtController>(display, vis);

    display->resize((int)(1920.0f * .7f), (int)(1080.0f * .7f));
    display->show();
    app.exec();

    return 0;
}
