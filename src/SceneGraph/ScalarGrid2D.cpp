///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/ScalarGrid2D.h>

#include <K/Core/NumberTools.h>

using std::shared_ptr;
using K::Core::NumberTools;

namespace Vectoid {
namespace SceneGraph {

ScalarGrid2D::ScalarGrid2D(const shared_ptr<Context> &context, float width, float height, int numColumns, int numRows)
        : Geometry(context),
          width_{width},
          height_{height},
          numColumns_{numColumns},
          numRows_{numRows} {
    if (!(width_ > 0.0f)) {
        width_ = 1.0f;
    }
    if (!(height_ > 0.0f)) {
        height_ = 1.0f;
    }
    NumberTools::ClampMin(&numColumns_, 2);
    NumberTools::ClampMin(&numRows_, 2);
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
