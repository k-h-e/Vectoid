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
    
    auto visualization = make_shared<Visualization>(1.0f, .4f, .07f, .1f, -2.0f);
    auto display       = make_shared<QtGLDisplay>(visualization);
    auto controller    = make_shared<QtController>(display, visualization);

    visualization->NewGroup("Pre-Production Build (PPB)", 0.0f, 0.0f);
    visualization->NewSubGroup("Builds", 0.0f);
    visualization->NewJob("ppb_build",         "Regular");
    visualization->NewJob("ppb_build_sim",     "Simulation");
    visualization->NewJob("ppb_build_kw",      "Klocwork");
    visualization->NewJob("ppb_build_cov",     "Coverage");
    visualization->NewJob("ppb_build_cov_int", "Coverage Integration");
    visualization->NewSubGroup("Module Tests", 0.0f);
    visualization->NewJob("ppb_mod_smoke",     "Smoke");
    visualization->NewJob("ppb_mod_normal",    "Normal");
    visualization->NewJob("ppb_mod_intensive", "Intensive");
    visualization->NewSubGroup("System Tests", 0.0f);
    visualization->NewJob("ppb_sys_smoke",     "Smoke");
    visualization->NewJob("ppb_sys_7",         "07");
    visualization->NewJob("ppb_sys_8",         "08");
    visualization->NewJob("ppb_sys_9",         "09");
    visualization->NewJob("ppb_sys_10",        "10");
    visualization->NewGroup("Entwicklungsmuster (EM)", 80.0f, 0.0f);
    visualization->NewSubGroup("Builds", 105.0f);
    visualization->NewJob("em_build",          "Regular");
    visualization->NewJob("em_build_sim",      "Simulation");
    visualization->NewSubGroup("Module Tests", 0.0f);
    visualization->NewJob("em_mod_smoke",      "Smoke");
    visualization->NewJob("em_mod_normal",     "Normal");
    visualization->NewJob("em_mod_intensive",  "Intensive");
    visualization->UpdateLayout();

    visualization->SetJobCounts("ppb_build",         100, 200);
    visualization->SetJobCounts("ppb_build_sim",     100, 200);
    visualization->SetJobCounts("ppb_build_kw",      100, 200);
    visualization->SetJobCounts("ppb_build_cov",     100, 200);
    visualization->SetJobCounts("ppb_build_cov_int", 100, 200);
    visualization->SetJobCounts("ppb_mod_smoke",     100, 200);
    visualization->SetJobCounts("ppb_mod_normal",    100, 200);
    visualization->SetJobCounts("ppb_mod_intensive", 100, 200);
    visualization->SetJobCounts("ppb_sys_smoke",     100, 200);
    visualization->SetJobCounts("ppb_sys_7",         100, 200);
    visualization->SetJobCounts("ppb_sys_8",         100, 200);
    visualization->SetJobCounts("ppb_sys_9",         100, 200);
    visualization->SetJobCounts("ppb_sys_10",        100, 200);
    visualization->SetJobCounts("em_build",          100, 200);
    visualization->SetJobCounts("em_build_sim",      100, 200);
    visualization->SetJobCounts("em_mod_smoke",      100, 200);
    visualization->SetJobCounts("em_mod_normal",     100, 200);
    visualization->SetJobCounts("em_mod_intensive",  100, 200);

    display->resize((int)(1920.0f * .7f), (int)(1080.0f * .7f));
    display->show();
    app.exec();

    return 0;
}
