#ifndef RASPIATOR_QTGLDISPLAY_H
#define RASPIATOR_QTGLDISPLAY_H


#include <QOpenGLWidget>


namespace Raspiator {

class Visualization;

class QtGLDisplay : public QOpenGLWidget {
    Q_OBJECT

  public:
    QtGLDisplay(std::shared_ptr<Visualization> visualization);
    QtGLDisplay(const QtGLDisplay &other)            = delete;
    QtGLDisplay &operator=(const QtGLDisplay &other) = delete;
    QtGLDisplay(QtGLDisplay &&other)                 = delete;
    QtGLDisplay &operator=(QtGLDisplay &&other)      = delete;

  protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

  private:
    std::shared_ptr<Visualization> visualization_;
};

}    // Namespace Raspiator.


#endif    // RASPIATOR_QTGLDISPLAY_H
