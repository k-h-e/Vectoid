TEMPLATE        = app
CONFIG         += c++11
QT             += widgets

INCLUDEPATH = ../../../../src/kxm/Core/include \
              ../../../../src/Vectoid/include \
              ../../src
DEPENDPATH  = $INCLUDEPATH

HEADERS = ../../../../src/Vectoid/include/Vectoid/CoordSys.h \
          ../../../../src/Vectoid/include/Vectoid/CoordSysCore.h \
          ../../../../src/Vectoid/include/Vectoid/CoordSysInterface.h \
          ../../../../src/Vectoid/include/Vectoid/Geode.h \
          ../../../../src/Vectoid/include/Vectoid/GeometryInterface.h \
          ../../../../src/Vectoid/include/Vectoid/OpenGL.h \
          ../../../../src/Vectoid/include/Vectoid/Particles.h \
          ../../../../src/Vectoid/include/Vectoid/ParticlesRenderer.h \
          ../../../../src/Vectoid/include/Vectoid/PerspectiveProjection.h \
          ../../../../src/Vectoid/include/Vectoid/Range.h \
          ../../../../src/Vectoid/include/Vectoid/SceneGraphNode.h \
          ../../../../src/Vectoid/include/Vectoid/TestTriangle.h \
          ../../../../src/Vectoid/include/Vectoid/Transform.h \
          ../../../../src/Vectoid/include/Vectoid/Vector.h \
          ../../src/Glyphs.h \
          ../../src/Indicatower.h \
          ../../src/TextConsole.h \
          src/QtController.h \
          src/QtGLDisplay.h


SOURCES = ../../../../src/kxm/Core/Buffer.cpp \
          ../../../../src/kxm/Core/Interface.cpp \
          ../../../../src/kxm/Core/IntModN.cpp \
          ../../../../src/kxm/Core/logging.cpp \
          ../../../../src/kxm/Core/POSIXThreadingFactory.cpp \
          ../../../../src/kxm/Core/Thread.cpp \
          ../../../../src/Vectoid/AgeColoredParticles.cpp \
          ../../../../src/Vectoid/Camera.cpp \
          ../../../../src/Vectoid/CoordSys.cpp \
          ../../../../src/Vectoid/CoordSysCore.cpp \
          ../../../../src/Vectoid/Geode.cpp \
          ../../../../src/Vectoid/Particles.cpp \
          ../../../../src/Vectoid/ParticlesRenderer.cpp \
          ../../../../src/Vectoid/PerspectiveProjection.cpp \
          ../../../../src/Vectoid/Range.cpp \
          ../../../../src/Vectoid/SceneGraphNode.cpp \
          ../../../../src/Vectoid/TestTriangle.cpp \
          ../../src/Glyphs.cpp \
          ../../src/Indicatower.cpp \
          ../../src/TextConsole.cpp \
          src/QtController.cpp \
          src/QtGLDisplay.cpp \
          src/main.cpp


