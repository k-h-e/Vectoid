#include <iostream>
#include <GLES/gl.h>
#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>

#include "Indicatower.h"
#include "VideoCoreDisplay.h"

using namespace std;
using namespace kxm::Vectoid;
using namespace Raspiator;


int main(int argc, char **argv) {
    cout << "rpi OpenGL ES test" << endl;
    
    VideoCoreDisplay display;
    cout << "display_size=(" << display.Width() << ", " << display.Height() << ")" << endl;
    
    auto projection = make_shared<PerspectiveProjection>();
    auto camera     = make_shared<Camera>();
    auto coordSys   = make_shared<CoordSys>();
    auto tower      = make_shared<Indicatower>();
    auto geode      = make_shared<Geode>(tower);
    projection->AddChild(camera);
    camera->AddChild(coordSys);
    coordSys->AddChild(geode);
    
    projection->SetViewPort((float)display.Width(), (float)display.Height());
    projection->SetWindowSize(1.0f);
    projection->SetViewingDepth(4.0f);
    projection->SetEyepointDistance(1.0f);
    camera->SetPosition(Vector(0.0f, 0.5f, 2.5f));
    
    display.BeginFrame();
    glEnable(GL_DEPTH_TEST);
    glClearColor(.1f, .1f, .3f, 1.0f);
    GLfloat lightPosition[] = { 2.0f, 2.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT0);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    display.EndFrame();
    
    for (int i = 0; i < 2; ++i) {
        for (int angle = 0; angle < 360; angle += 1) {
            Transform transform(YAxis, (float)angle);
            coordSys->SetTransform(transform);
            
            display.BeginFrame();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            projection->Render(nullptr);
            display.EndFrame();
        }
    }
    
    return 0;
}
