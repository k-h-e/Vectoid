///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_TRIANGLETRANSFORMER_H_
#define VECTOID_DATASET_TRIANGLETRANSFORMER_H_

#include <memory>

#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/Core/Transform.h>

namespace Vectoid {
namespace DataSet {

//! Triangle provider decorator, transforming the provided triangles on the fly.
class TriangleTransformer : public virtual Core::TriangleProviderInterface {
  public:
    //! Scale is applied first.
    TriangleTransformer(const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider, float scale,
                        const Vectoid::Core::Transform<float> &transform);
    TriangleTransformer()                                            = delete;
    TriangleTransformer(const TriangleTransformer &other)            = delete;
    TriangleTransformer &operator=(const TriangleTransformer &other) = delete;
    TriangleTransformer(TriangleTransformer &&other)                 = delete;
    TriangleTransformer &operator=(TriangleTransformer &&other)      = delete;
    ~TriangleTransformer()                                           = default;

    // TriangleProviderInterface...
    void PrepareToProvideTriangles() override;
    bool ProvideNextTriangle(Core::ThreePoints &outTriangle) override;
    void ProvideNormal(Core::Vector<float> &outNormal) override;
    bool TriangleError() override;

  private:
    std::shared_ptr<Core::TriangleProviderInterface> provider_;
    float                                            scale_;
    Vectoid::Core::Transform<float>                  rotation_;
    Vectoid::Core::Transform<float>                  translation_;
    Core::ThreePoints                                triangle_;
    Core::Vector<float>                              normal_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TRIANGLETRANSFORMER_H_
