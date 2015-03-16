#include <iostream>
#include <GLES/gl.h>
#include <Vectoid/Vector.h>
#include "VideoCoreDisplay.h"
#include "Visualization.h"

using namespace std;
using namespace kxm::Vectoid;
using namespace Raspiator;


int main(int argc, char **argv) {
    puts("Buh!");
    cout << "rpi OpenGL ES test" << endl;
    exit(0);
    
    Visualization vis("jenkins.org", 1.0f, .4f, .0015f, .08f, .11f, -2.0f,
                      Vector(-1.0f, 0.0f, 0.0f));
    vis.NewGroup("Pre-Production Build (PPB)", 0.0f, 0.0f);
    vis.NewSubGroup("Builds", 0.0f);
    vis.NewJob("ppb_build",         "MPC Trunk",                "a", 120.0f);
    vis.NewJob("ppb_build_sim",     "MPC Simulation Trunk",     "b", 120.0f);
    vis.NewJob("ppb_build_kw",      "MPC Klocwork Trunk",       "c", 120.0f);
    vis.NewJob("ppb_build_cov",     "MPC Coverage Trunk",       "d", 120.0f);
    vis.NewJob("ppb_build_cov_int", "MPC Coverage Integration", "e", 120.0f);
    vis.NewSubGroup("Module Tests", 0.0f);
    vis.NewJob("ppb_mod_smoke",     "Tests Trunk Smoke",        "f", 120.0f);
    vis.NewJob("ppb_mod_normal",    "Tests Trunk Normal",       "g", 120.0f);
    vis.NewJob("ppb_mod_intensive", "Tests Trunk Intensive",    "h", 120.0f);
    vis.NewSubGroup("System Tests", 0.0f);
    vis.NewJob("ppb_sys_smoke",     "System Smoke Trunk",       "i", 120.0f);
    vis.NewJob("ppb_sys_7",         "System Function Trunk",    "j", 120.0f);
    vis.NewJob("ppb_sys_8",         "System Lasttest Trunk",    "k", 120.0f);
    vis.NewJob("ppb_sys_9",         "System Calibration Trunk", "l", 120.0f);
    vis.NewJob("ppb_sys_10",        "System Regression Trunk",  "m", 120.0f);
    vis.NewGroup("Entwicklungsmuster (EM)", 80.0f, 0.0f);
    vis.NewSubGroup("Builds", 105.0f);
    vis.NewJob("em_build",          "MPC Branch",               "n", 120.0f);
    vis.NewJob("em_build_sim",      "MPC Simulation Branch",    "o", 120.0f);
    vis.NewSubGroup("Module Tests", 0.0f);
    vis.NewJob("em_mod_smoke",      "Tests Branch Smoke",       "p", 120.0f);
    vis.NewJob("em_mod_normal",     "Tests Branch Normal",      "q", 120.0f);
    vis.NewJob("em_mod_intensive",  "Tests Branch Intensive",   "r", 120.0f);
    vis.UpdateLayout();
    
    VideoCoreDisplay display;
    vis.SetViewPort(display.Width(), display.Height());
    cout << "display_size=(" << display.Width() << ", " << display.Height() << ")" << endl;
    
    display.BeginFrame();
    glEnable(GL_DEPTH_TEST);
    glClearColor(.1f, .1f, .3f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLfloat lightPosition[] = { 2.0f, 2.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT0);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    display.EndFrame();
    
    for (int i = 0; i < 300; ++i) {           
        display.BeginFrame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        vis.RenderFrame();
        display.EndFrame();
    }
    
    return 0;
}
