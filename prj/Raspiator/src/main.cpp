#include <iostream>
#include <GLES/gl.h>
#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include <Vectoid/TestTriangle.h>

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
    auto triangle   = make_shared<TestTriangle>();
    auto geode      = make_shared<Geode>(triangle);
    projection->AddChild(camera);
    camera->AddChild(coordSys);
    coordSys->AddChild(geode);
    
    projection->SetViewPort((float)display.Width(), (float)display.Height());
    projection->SetWindowSize(1.0f);
    projection->SetViewingDepth(3.0f);
    projection->SetEyepointDistance(1.0f);
    camera->SetPosition(Vector(0.0f, 0.5f, 1.5f));
    
    display.BeginFrame();
    glEnable(GL_DEPTH_TEST);
    glClearColor(.1f, .1f, .3f, 1.0f);
    display.EndFrame();
    
    for (int i = 0; i < 2; ++i) {
        for (int angle = 0; angle < 360; angle += 5) {
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
