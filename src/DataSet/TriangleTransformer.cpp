///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/TriangleTransformer.h>

using std::shared_ptr;

using Vectoid::Core::ThreePoints;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;
using Vectoid::Core::Transform;

namespace Vectoid {
namespace DataSet {

TriangleTransformer::TriangleTransformer(const shared_ptr<TriangleProviderInterface> &triangleProvider, float scale,
                                         const Transform<float> &transform)
        : provider_{triangleProvider},
          scale_{scale},
          rotation_{transform},
          translation_{transform} {
    rotation_.SetTranslationPart(Vector<float>{0.0f, 0.0f, 0.0f});
    translation_.SetRotationPart(Vector<float>{1.0f, 0.0f, 0.0f}, Vector<float>{0.0f, 1.0f, 0.0f},
                                 Vector<float>{0.0f, 0.0f, 1.0f});
}

void TriangleTransformer::PrepareToProvideTriangles() {
    provider_->PrepareToProvideTriangles();
}

bool TriangleTransformer::ProvideNextTriangle(ThreePoints &outTriangle) {
    bool success { provider_->ProvideNextTriangle(triangle_) };
    if (success) {
        provider_->ProvideNormal(normal_);

        for (int i = 0; i < 3; ++i) {
            Vector<float> point { scale_ * triangle_[i] };
            rotation_.ApplyTo(point);
            translation_.ApplyTo(point);
            triangle_[i] = point;
        }

        rotation_.ApplyTo(normal_);

        outTriangle = triangle_;
    }

    return success;
}

void TriangleTransformer::ProvideNormal(Vector<float> &outNormal) {
    outNormal = normal_;
}

bool TriangleTransformer::TriangleError() {
    return provider_->TriangleError();
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
