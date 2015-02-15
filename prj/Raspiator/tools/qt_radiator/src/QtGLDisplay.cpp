#include "QtGLDisplay.h"

#include <iostream>

#include <Vectoid/PerspectiveProjection.h>

using namespace std;
using namespace kxm::Vectoid;


namespace Raspiator {

QtGLDisplay::QtGLDisplay(std::shared_ptr<PerspectiveProjection> projection)
    : projection_(projection) {
    // Nop.
}

void QtGLDisplay::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(.1f, .1f, .3f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLfloat lightPosition[] = { 2.0f, 2.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT0);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void QtGLDisplay::resizeGL(int width, int height) {
    projection_->SetViewPort((float)width, (float)height);
}

void QtGLDisplay::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection_->Render(nullptr);
}

}    // Namespace Raspiator.
