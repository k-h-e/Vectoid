///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_CONTEXT_H_
#define VECTOID_GUI_CONTEXT_H_

#include <memory>
#include <optional>
#include <unordered_set>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/Gui/Gui.h>

namespace Vectoid {
    namespace Gui {
        class GuiElement;
    }
    namespace SceneGraph {
        class Glyphs;
        class RenderTargetInterface;
    }
}

namespace Vectoid {
namespace Gui {

//! Holds context information for GUI elements.
class Context : public virtual K::Core::Interface {
  public:
    Context(const std::shared_ptr<SceneGraph::RenderTargetInterface> &renderTarget,
            const std::shared_ptr<SceneGraph::Glyphs> &glyphs, float scale);

    void SetHandler(Gui::HandlerInterface *handler);
    void Unregister(GuiElement *element);
    void SetLayoutRequired(bool required);
    bool LayoutRequired() const;
    void RequestRedraw();
    void SignalSceneChanged(int scene);
    void RequestCyclicUpdateCalls(GuiElement *element, bool requested);
    void OnCyclicUpdate(float deltaTimeS);
    
    const std::shared_ptr<SceneGraph::RenderTargetInterface> renderTarget;
    const std::shared_ptr<SceneGraph::Glyphs>                glyphs;
    const Size                                               glyphSize;
    const float                                              frameWidth;
    const float                                              spacing;
    const Vectoid::Core::Vector<float>                       labelBackgroundColor;
    const float                                              labelBackgroundAlpha;
    const Vectoid::Core::Vector<float>                       menuBackgroundColor;
    const float                                              menuBackgroundAlpha;
    const Vectoid::Core::Vector<float>                       menuTextColor;
    const Vectoid::Core::Vector<float>                       selectionTextColor;
    const Vectoid::Core::Vector<float>                       selectionBackgroundColor;
    
  private:
    void UpdateCyclicUpdateCallsRequest();
    static float ValidateScale(float scale);
  
    Gui::HandlerInterface            *handler_;
    std::optional<bool>              cyclicUpdateCallsRequested_;
    bool                             layoutRequired_;
    std::unordered_set<GuiElement *> elementsNeedingCyclicUpdateCalls_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_CONTEXT_H_
