#include <Vectoid/Gui/Gui.h>

#include <Vectoid/Gui/GuiElement.h>
#include <Vectoid/Gui/RedrawRequestHandlerInterface.h>
#include <Vectoid/SceneGraph/CoordSys.h>

using std::shared_ptr;
using Vectoid::SceneGraph::CoordSys;
using Vectoid::SceneGraph::RenderTargetInterface;
using Vectoid::Gui::RedrawRequestHandlerInterface;

namespace Vectoid {
namespace Gui {

Gui::Gui(const shared_ptr<RenderTargetInterface> &renderTarget, const shared_ptr<CoordSys> &coordSys,
         const Frame &frame, const shared_ptr<RedrawRequestHandlerInterface> &redrawRequestHandler)
        : renderTarget_{renderTarget},
          coordSys_{coordSys},
          frame_(frame),
          redrawRequestHandler_{redrawRequestHandler} {
    // Nop.
}

int Gui::AddScene(const shared_ptr<GuiElement> &root) {
    int id = static_cast<int>(scenes_.size());
    scenes_.push_back(root);
    return id;
}

void Gui::EnterScene(int scene) {
    coordSys_->RemoveAllChildren();
    auto &sceneRoot = scenes_[scene];
    sceneRoot->AddSceneGraphNodes(coordSys_);
    sceneRoot->UpdateSizes();
    sceneRoot->UpdatePositions(frame_);
    redrawRequestHandler_->onRedrawRequested();
}

}    // Namespace Gui.
}    // Namespace Vectoid.
