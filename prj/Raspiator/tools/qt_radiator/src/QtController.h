#ifndef RASPIATOR_QTCONTROLLER_H
#define RASPIATOR_QTCONTROLLER_H


#include <QWidget>


namespace kxm {
namespace Vectoid {
    class PerspectiveProjection;
    class CoordSys;
}
}

namespace Raspiator {

class QtGLDisplay;

class QtController : public QWidget {
    Q_OBJECT

  public:
    QtController();
    QtController(const QtController &other)            = delete;
    QtController &operator=(const QtController &other) = delete;
    QtController(QtController &&other)                 = delete;
    QtController &operator=(QtController &&other)      = delete;
    void SetView(std::shared_ptr<QtGLDisplay> view);
    std::shared_ptr<kxm::Vectoid::PerspectiveProjection> Projection();

  private slots:
    void ProcessTimer();

  private:
    std::shared_ptr<QtGLDisplay>                         view_;
    std::shared_ptr<kxm::Vectoid::PerspectiveProjection> projection_;
    std::shared_ptr<kxm::Vectoid::CoordSys>              coordSys_;
    int                                                  angle_;
};

}


#endif    // RASPIATOR_QTCONTROLLER_H

