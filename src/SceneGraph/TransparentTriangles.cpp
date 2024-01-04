///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/TransparentTriangles.h>

#include <K/Core/NumberTools.h>

using std::shared_ptr;

using K::Core::NumberTools;
using Vectoid::Core::Vector;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {

TransparentTriangles::TransparentTriangles(const shared_ptr<Context> &context,
                                           const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : Geometry(context),
          triangleProvider_(triangleProvider),
          color_(1.0f, 1.0f, 1.0f),
          alpha_(.5f) {
    // Nop.
}

void TransparentTriangles::SetColor(const Vector<float> &color) {
    color_ = color;
    NumberTools::Clamp(&color_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&color_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&color_.z, 0.0f, 1.0f);
}

void TransparentTriangles::SetAlpha(float alpha) {
    alpha_ = alpha;
    NumberTools::Clamp(&alpha_, 0.0f, 1.0f);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
