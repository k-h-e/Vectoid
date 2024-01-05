///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_VERTEXNORMALTRIANGLEPROVIDER_H_
#define VECTOID_DATASET_VERTEXNORMALTRIANGLEPROVIDER_H_

#include <memory>
#include <Vectoid/Core/ExtendedTriangleProviderInterface.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/DataSet/Triangles.h>

namespace Vectoid {
namespace DataSet {

//! Extended triangle provider adding vertex normals to a regular triangle provider.
class VertexNormalTriangleProvider : public virtual Core::ExtendedTriangleProviderInterface {
  public:
    VertexNormalTriangleProvider(const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    VertexNormalTriangleProvider()                                                     = delete;
    VertexNormalTriangleProvider(const VertexNormalTriangleProvider &other)            = delete;
    VertexNormalTriangleProvider &operator=(const VertexNormalTriangleProvider &other) = delete;
    VertexNormalTriangleProvider(VertexNormalTriangleProvider &&other)                 = delete;
    VertexNormalTriangleProvider &operator=(VertexNormalTriangleProvider &&other)      = delete;
    ~VertexNormalTriangleProvider()                                                    = default;

    bool Precompute();

    void PrepareToProvideTriangles() override;
    bool ProvideNextTriangle(Core::ThreePoints *outTriangle) override;
    void ProvideNormal(Core::Vector<float> *outNormal) override;
    void ProvideVertexNormals(Core::ThreePoints *outVertexNormals) override;
    bool TriangleError() override;

  private:
    const std::shared_ptr<Core::TriangleProviderInterface> triangleProvider_;
    std::unique_ptr<Triangles>                             triangles_;
    std::unique_ptr<std::vector<Core::Vector<float>>>      vertexNormals_;
    int                                                    currentTriangle_;
    Core::Vector<float>                                    currentTriangleNormal_;
    Core::ThreePoints                                      currentTriangleVertexNormals_;
    bool                                                   error_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_VERTEXNORMALTRIANGLEPROVIDER_H_
