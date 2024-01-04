///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VISITORINTERFACE_H_
#define VECTOID_SCENEGRAPH_VISITORINTERFACE_H_

#include <memory>
#include <K/Core/Interface.h>

namespace Vectoid {
namespace SceneGraph {

class TreeNode;

//! Interface to scene graph tree visitors.
class VisitorInterface : public virtual K::Core::Interface {
  public:
    virtual void Visit(const std::shared_ptr<TreeNode> &node) = 0;
    virtual void Leave(const std::shared_ptr<TreeNode> &node) = 0;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VISITORINTERFACE_H_

