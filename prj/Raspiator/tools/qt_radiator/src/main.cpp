#include <QApplication>

#include "QtGLDisplay.h"
#include "QtController.h"

using namespace std;
using namespace Raspiator;


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    QtController controller;
    auto glWindow = std::make_shared<QtGLDisplay>(controller.Projection());
    controller.SetView(glWindow);
    glWindow->show();
    app.exec();

    return 0;
}
