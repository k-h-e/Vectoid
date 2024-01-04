///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_CONTEXT_H_
#define VECTOID_SCENEGRAPH_CONTEXT_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace SceneGraph {

class Node;

//! Base class to entities holding context information for scene graph nodes.
/*!
 *  Intended to be subclassed in rendering-platform-specific way.
 */
class Context : public virtual K::Core::Interface {
  public:
    Context();
    Context(const Context &other)            = delete;
    Context &operator=(const Context &other) = delete;
    Context(Context &&other)                 = delete;
    Context &operator=(Context &&other)      = delete;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_CONTEXT_H_
