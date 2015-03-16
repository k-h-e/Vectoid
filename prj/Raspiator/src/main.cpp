#include <iostream>
#include <GLES/gl.h>
#include <Vectoid/Vector.h>
#include "VideoCoreDisplay.h"
#include "Visualization.h"

using namespace std;
using namespace kxm::Vectoid;
using namespace Raspiator;


int main(int argc, char **argv) {
    cout << "rpi OpenGL ES test" << endl;
    
    Visualization vis("jenkins.org",
                      1.0f, .45f, .0015f, .1f, .12f, -2.0f, Vector(-1.0f, 0.0f, 0.0f));
    vis.NewGroup("Pre-Production Build (PPB)", 0.0f, 0.0f);
    vis.NewSubGroup("Builds", 0.0f);
    vis.NewJob("ppb_build",         "MPC Trunk",
               "a", true,  120.0f);
    vis.NewJob("ppb_build_sim",     "MPC Simulation Trunk",
               "b", true, 120.0f);
    vis.NewJob("ppb_build_kw",      "MPC Klocwork Trunk",
               "c", true, 120.0f);
    vis.NewJob("ppb_build_cov",     "MPC Coverage Trunk",
               "d", true, 120.0f);
    vis.NewJob("ppb_build_cov_int", "MPC Coverage Integration",
               "e", true, 120.0f);
    vis.NewSubGroup("Module Tests", 0.0f);
    vis.NewJob("ppb_mod_smoke",     "Tests Trunk Smoke",
               "f", false, 120.0f);
    vis.NewJob("ppb_mod_normal",    "Tests Trunk Normal",
               "g", false, 120.0f);
    vis.NewJob("ppb_mod_intensive", "Tests Trunk Intensive",
               "h", false, 120.0f);
    vis.NewSubGroup("System Tests", 0.0f);
    vis.NewJob("ppb_sys_smoke",     "System Smoke Trunk",
               "i", false, 120.0f);
    vis.NewJob("ppb_sys_7",         "System Function Trunk",
               "j", false, 120.0f);
    vis.NewJob("ppb_sys_8",         "System Lasttest Trunk",
               "k", false, 120.0f);
    vis.NewJob("ppb_sys_9",         "System Calibration Trunk",
               "l", false, 120.0f);
    vis.NewJob("ppb_sys_10",        "System Regression Trunk",
               "m", false, 120.0f);
    vis.NewGroup("Entwicklungsmuster (EM)", 80.0f, 0.0f);
    vis.NewSubGroup("Builds", 105.0f);
    vis.NewJob("em_build",          "MPC Branch",
               "n", true, 120.0f);
    vis.NewJob("em_build_sim",      "MPC Simulation Branch",
               "o", true, 120.0f);
    vis.NewSubGroup("Module Tests", 0.0f);
    vis.NewJob("em_mod_smoke",      "Tests Branch Smoke",
               "p", false, 120.0f);
    vis.NewJob("em_mod_normal",     "Tests Branch Normal",
               "q", false, 120.0f);
    vis.NewJob("em_mod_intensive",  "Tests Branch Intensive",
               "r", false, 120.0f);
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
    
    for (int i = 0; i < 600; ++i) {           
        display.BeginFrame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        vis.RenderFrame();
        display.EndFrame();
    }
    
    return 0;
}
