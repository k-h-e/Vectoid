///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_GEODE_H_
#define VECTOID_SCENEGRAPH_GEODE_H_

#include <memory>
#include <Vectoid/SceneGraph/TreeNode.h>

namespace Vectoid {
namespace SceneGraph {

class Geometry;

//! This scene graph node represents actual geometry in the scene (geode = geometry node).
/*!
 *  A geode's geometry may be <c>nullptr</c> (empty).
 */
class Geode : public TreeNode {
  public:
    Geode()                              = delete;
    Geode(const Geode &other)            = delete;
    Geode &operator=(const Geode &other) = delete;
    Geode(Geode &&other)                 = delete;
    Geode &operator=(Geode &&other)      = delete;

    //! Replaces the geode's geometry with the specified one.
    /*!
     *  A geode's geometry may be <c>nullptr</c> (empty).
     */
    void SetGeometry(const std::shared_ptr<Geometry> &geometry);
    void RenderPre() override;

  protected:
    /*!
     *  A geode's geometry may be <c>nullptr</c> (empty).
     */
    Geode(const std::shared_ptr<Context> &context, const std::shared_ptr<Geometry> &geometry);
    
  private:
    std::shared_ptr<Geometry> geometry_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_GEODE_H_
