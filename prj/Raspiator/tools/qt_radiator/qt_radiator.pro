TEMPLATE        = app
CONFIG         += c++11
QT             += widgets

INCLUDEPATH = ../../../../src/kxm/Core/include \
              ../../../../src/Vectoid/include \
              ../../src
DEPENDPATH  = $INCLUDEPATH

INCLUDEPATH += /Users/kai/opt/boost/include
LIBS        += /Users/kai/opt/boost/lib/libboost_system.a

HEADERS = ../../../../src/kxm/Core/include/kxm/Core/ActionInterface.h \
          ../../../../src/kxm/Core/include/kxm/Core/Buffer.h \
          ../../../../src/kxm/Core/include/kxm/Core/ConditionVariableInterface.h \
          ../../../../src/kxm/Core/include/kxm/Core/config.h \
          ../../../../src/kxm/Core/include/kxm/Core/CriticalSection.h \
          ../../../../src/kxm/Core/include/kxm/Core/Interface.h \
          ../../../../src/kxm/Core/include/kxm/Core/IntModN.h \
          ../../../../src/kxm/Core/include/kxm/Core/LockInterface.h \
          ../../../../src/kxm/Core/include/kxm/Core/logging.h \
          ../../../../src/kxm/Core/include/kxm/Core/NumberTools.h \
          ../../../../src/kxm/Core/include/kxm/Core/POSIXThreadingFactory.h \
          ../../../../src/kxm/Core/include/kxm/Core/ReusableItems.h \
          ../../../../src/kxm/Core/include/kxm/Core/terminal.h \
          ../../../../src/kxm/Core/include/kxm/Core/Thread.h \
          ../../../../src/kxm/Core/include/kxm/Core/ThreadControlInterface.h \
          ../../../../src/kxm/Core/include/kxm/Core/ThreadingFactoryInterface.h \
          ../../../../src/Vectoid/include/Vectoid/AgeColoredParticles.h \
          ../../../../src/Vectoid/include/Vectoid/Camera.h \
          ../../../../src/Vectoid/include/Vectoid/CoordSys.h \
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
          ../../src/Cuboid.h \
          ../../src/Glyphs.h \
          ../../src/Indicatower.h \
          ../../src/JenkinsAccess.h \
          ../../src/TextConsole.h \
          ../../src/TextRing.h \
          ../../src/Visualization.h \
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
          ../../src/Cuboid.cpp \
          ../../src/Glyphs.cpp \
          ../../src/Indicatower.cpp \
          ../../src/JenkinsAccess.cpp \
          ../../src/TextConsole.cpp \
          ../../src/TextRing.cpp \
          ../../src/Visualization.cpp \
          src/QtController.cpp \
          src/QtGLDisplay.cpp \
          src/main.cpp

QMAKE_MAC_SDK = macosx10.11

