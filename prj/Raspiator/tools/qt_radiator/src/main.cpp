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
    
    auto visualization = make_shared<Visualization>("http://jenkins.org",
                                                    1.0f, .4f, .0015f, .08f, .11f, -2.0f,
                                                    Vector(-1.0, 0.0, 0.0));
    auto display       = make_shared<QtGLDisplay>(visualization);
    auto controller    = make_shared<QtController>(display, visualization);

    visualization->NewGroup("Pre-Production Build (PPB)", 0.0f, 0.0f);
    visualization->NewSubGroup("Builds", 0.0f);
    visualization->NewJob("ppb_build",         "MPC Trunk",                "a", 120.0f);
    visualization->NewJob("ppb_build_sim",     "MPC Simulation Trunk",     "b", 120.0f);
    visualization->NewJob("ppb_build_kw",      "MPC Klocwork Trunk",       "c", 120.0f);
    visualization->NewJob("ppb_build_cov",     "MPC Coverage Trunk",       "d", 120.0f);
    visualization->NewJob("ppb_build_cov_int", "MPC Coverage Integration", "e", 120.0f);
    visualization->NewSubGroup("Module Tests", 0.0f);
    visualization->NewJob("ppb_mod_smoke",     "Tests Trunk Smoke",        "f", 120.0f);
    visualization->NewJob("ppb_mod_normal",    "Tests Trunk Normal",       "g", 120.0f);
    visualization->NewJob("ppb_mod_intensive", "Tests Trunk Intensive",    "h", 120.0f);
    visualization->NewSubGroup("System Tests", 0.0f);
    visualization->NewJob("ppb_sys_smoke",     "System Smoke Trunk",       "i", 120.0f);
    visualization->NewJob("ppb_sys_7",         "System Function Trunk",    "j", 120.0f);
    visualization->NewJob("ppb_sys_8",         "System Lasttest Trunk",    "k", 120.0f);
    visualization->NewJob("ppb_sys_9",         "System Calibration Trunk", "l", 120.0f);
    visualization->NewJob("ppb_sys_10",        "System Regression Trunk",  "m", 120.0f);
    visualization->NewGroup("Entwicklungsmuster (EM)", 80.0f, 0.0f);
    visualization->NewSubGroup("Builds", 105.0f);
    visualization->NewJob("em_build",          "MPC Branch",               "n", 120.0f);
    visualization->NewJob("em_build_sim",      "MPC Simulation Branch",    "o", 120.0f);
    visualization->NewSubGroup("Module Tests", 0.0f);
    visualization->NewJob("em_mod_smoke",      "Tests Branch Smoke",       "p", 120.0f);
    visualization->NewJob("em_mod_normal",     "Tests Branch Normal",      "q", 120.0f);
    visualization->NewJob("em_mod_intensive",  "Tests Branch Intensive",   "r", 120.0f);
    visualization->UpdateLayout();

    display->resize((int)(1920.0f * .7f), (int)(1080.0f * .7f));
    display->show();
    app.exec();

    return 0;
}
