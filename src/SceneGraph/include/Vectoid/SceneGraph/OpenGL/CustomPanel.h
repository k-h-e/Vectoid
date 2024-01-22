///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_CUSTOMPANEL_H_
#define VECTOID_SCENEGRAPH_OPENGL_CUSTOMPANEL_H_

#include <Vectoid/SceneGraph/CustomPanel.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;

//! Custom panel geometry.
class CustomPanel : public SceneGraph::CustomPanel {
  public:
    CustomPanel(const std::shared_ptr<Context> &context, float width, float height);
    CustomPanel()                                    = delete;
    CustomPanel(const CustomPanel &other)            = delete;
    CustomPanel &operator=(const CustomPanel &other) = delete;
    CustomPanel(CustomPanel &&other)                 = delete;
    CustomPanel &operator=(CustomPanel &&other)      = delete;
    ~CustomPanel()                                   = default;
    
    void Render() override;

  private:
    void SetupRectangle(float left, float top, float right, float bottom, GLfloat *outVertices);
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_CUSTOMPANEL_H_
