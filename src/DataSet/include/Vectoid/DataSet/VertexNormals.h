///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_VERTEXNORMALS_H_
#define VECTOID_DATASET_VERTEXNORMALS_H_

#include <memory>
#include <vector>

#include <Vectoid/Core/ExtendedTriangleProviderInterface.h>
#include <Vectoid/Core/ThreePoints.h>

namespace Vectoid {
    namespace DataSet {
        class Triangles;
    }
}

namespace Vectoid {
namespace DataSet {

//! Provides vertex normals for an underlying \ref Triangles container.
class VertexNormals : public virtual Core::ExtendedTriangleProviderInterface {
  public:
    VertexNormals(const std::shared_ptr<Triangles> &triangles);
    VertexNormals()                                      = delete;
    VertexNormals(const VertexNormals &other)            = delete;
    VertexNormals &operator=(const VertexNormals &other) = delete;
    VertexNormals(VertexNormals &&other)                 = delete;
    VertexNormals &operator=(VertexNormals &&other)      = delete;
    ~VertexNormals()                                     = default;

    // ExtendedTriangleProviderInterface...
    void PrepareToProvideTriangles() override;
    bool ProvideNextTriangle(Core::ThreePoints &outTriangle) override;
    void ProvideNormal(Core::Vector<float> &outNormal) override;
    void ProvideVertexNormals(Core::ThreePoints &outVertexNormals) override;
    bool TriangleError() override;

  private:
    bool ComputeVertexNormals();
  
    std::shared_ptr<Triangles>       triangles_;
    std::vector<Core::Vector<float>> vertexNormals_;
    int                              currentTriangle_;
    Core::Vector<float>              currentTriangleNormal_;
    Core::ThreePoints                currentTriangleVertexNormals_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_VERTEXNORMALS_H_
