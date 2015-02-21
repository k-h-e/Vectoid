#include <QApplication>

#include "Visualization.h"
#include "QtGLDisplay.h"
#include "QtController.h"

using namespace std;
using namespace Raspiator;


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    auto visualization = make_shared<Visualization>();
    auto display       = make_shared<QtGLDisplay>(visualization);
    auto controller    = make_shared<QtController>(display, visualization);

    display->show();
    app.exec();

    return 0;
}
