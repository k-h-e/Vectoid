#ifndef RASPIATOR_QTCONTROLLER_H
#define RASPIATOR_QTCONTROLLER_H


#include <QWidget>


namespace Raspiator {

class Visualization;
class QtGLDisplay;

class QtController : public QWidget {
    Q_OBJECT

  public:
    QtController(std::shared_ptr<QtGLDisplay> display,
                 std::shared_ptr<Visualization> visualization);
    QtController(const QtController &other)            = delete;
    QtController &operator=(const QtController &other) = delete;
    QtController(QtController &&other)                 = delete;
    QtController &operator=(QtController &&other)      = delete;

  private slots:
    void ProcessTimer();

  private:
    std::shared_ptr<QtGLDisplay>                         display_;
    std::shared_ptr<Visualization>                       visualization_;
};

}


#endif    // RASPIATOR_QTCONTROLLER_H

