#include <random>
#include <QApplication>
#include <Vectoid/Vector.h>
#include "Visualization.h"
#include "QtGLDisplay.h"
#include "QtController.h"

using namespace std;
using namespace kxm::Vectoid;
using namespace Raspiator;


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    auto vis = make_shared<Visualization>("http://jenkins.org",
                                          1.0f, .45f, .0015f, .1f, .12f, -2.0f,
                                          Vector(-1.0, 0.0, 0.0));
    auto display    = make_shared<QtGLDisplay>(vis);
    auto controller = make_shared<QtController>(display, vis);

    vis->NewGroup("Pre-Production Build (PPB)", 0.0f, 0.0f);
    vis->NewSubGroup("Builds", 0.0f);
    vis->NewJob("ppb_build",         "MPC Trunk",
                "a", true,  120.0f);
    vis->NewJob("ppb_build_sim",     "MPC Simulation Trunk",
                "b", true, 120.0f);
    vis->NewJob("ppb_build_kw",      "MPC Klocwork Trunk",
                "c", true, 120.0f);
    vis->NewJob("ppb_build_cov",     "MPC Coverage Trunk",
                "d", true, 120.0f);
    vis->NewJob("ppb_build_cov_int", "MPC Coverage Integration",
                "e", true, 120.0f);
    vis->NewSubGroup("Module Tests", 0.0f);
    vis->NewJob("ppb_mod_smoke",     "Tests Trunk Smoke",
                "f", false, 120.0f);
    vis->NewJob("ppb_mod_normal",    "Tests Trunk Normal",
                "g", false, 120.0f);
    vis->NewJob("ppb_mod_intensive", "Tests Trunk Intensive",
                "h", false, 120.0f);
    vis->NewSubGroup("System Tests", 0.0f);
    vis->NewJob("ppb_sys_smoke",     "System Smoke Trunk",
                "i", false, 120.0f);
    vis->NewJob("ppb_sys_7",         "System Function Trunk",
                "j", false, 120.0f);
    vis->NewJob("ppb_sys_8",         "System Lasttest Trunk",
                "k", false, 120.0f);
    vis->NewJob("ppb_sys_9",         "System Calibration Trunk",
                "l", false, 120.0f);
    vis->NewJob("ppb_sys_10",        "System Regression Trunk",
                "m", false, 120.0f);
    vis->NewGroup("Entwicklungsmuster (EM)", 80.0f, 0.0f);
    vis->NewSubGroup("Builds", 105.0f);
    vis->NewJob("em_build",          "MPC Branch",
                "n", true, 120.0f);
    vis->NewJob("em_build_sim",      "MPC Simulation Branch",
                "o", true, 120.0f);
    vis->NewSubGroup("Module Tests", 0.0f);
    vis->NewJob("em_mod_smoke",      "Tests Branch Smoke",
                "p", false, 120.0f);
    vis->NewJob("em_mod_normal",     "Tests Branch Normal",
                "q", false, 120.0f);
    vis->NewJob("em_mod_intensive",  "Tests Branch Intensive",
                "r", false, 120.0f);
    vis->UpdateLayout();

    display->resize((int)(1920.0f * .7f), (int)(1080.0f * .7f));
    display->show();
    app.exec();

    return 0;
}
