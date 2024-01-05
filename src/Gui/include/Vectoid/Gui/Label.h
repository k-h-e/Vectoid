///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_LABEL_H_
#define VECTOID_GUI_LABEL_H_

#include <string>
#include <Vectoid/Gui/GuiElement.h>
#include <Vectoid/SceneGraph/TextConsole.h>

namespace Vectoid {
    namespace SceneGraph {
        class CoordSys;
        class TextConsole;
    }
}

namespace Vectoid {
namespace Gui {

//! Label GUI element.
class Label : public GuiElement {
  public:
    friend class Gui;
    
    Label()                              = delete;
    Label(const Label &other)            = delete;
    Label &operator=(const Label &other) = delete;
    Label(Label &&other)                 = delete;
    Label &operator=(Label &&other)      = delete;
    ~Label()                             = default;
    
    //! Sets the label text as specified.
    void SetText(const std::string &text);
    //! Sets the label text as specified.
    void SetText(int line, const std::string &text, Vectoid::SceneGraph::TextConsole::Color color);
    //! Writes the specified line of text to the console, wrapping it into multiple rows if necessary.
    void WriteLine(const std::string &line, Vectoid::SceneGraph::TextConsole::Color color);
    //! Clears the label text.
    void ClearText();
    
    void AddSceneGraphNodes(SceneGraph::CoordSys *guiCoordSys) override;
    Size UpdateRequiredSizes() override;
    void Layout(const Frame &frame) override;
    GuiElement *TouchedElement(const TouchInfo &touch) override;
    void OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches) override;
    
  private:
    Label(const std::string &text, const Size &glyphSize, const std::shared_ptr<Context> &context);
    Label(int width, int height, const Size &glyphSize, const std::shared_ptr<Context> &context);
    
    void Construct(int width, int height, const Size &glyphSize);
    
    std::shared_ptr<SceneGraph::TextConsole> textConsole_;
    std::shared_ptr<SceneGraph::CoordSys>    coordSys_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_LABEL_H_
