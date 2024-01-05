///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_LITCOLORCODEDTRIANGLES_H_
#define VECTOID_SCENEGRAPH_LITCOLORCODEDTRIANGLES_H_

#include <memory>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
    namespace Core {
        class ExtendedTriangleProviderInterface;
        class TriangleProviderInterface;
    }
}

namespace Vectoid {
namespace SceneGraph {

//! Renders lit, color-coded triangles (useful e.g. for depth maps).
class LitColorCodedTriangles : public Geometry {
  public:
    LitColorCodedTriangles()                                               = delete;
    LitColorCodedTriangles(const LitColorCodedTriangles &other)            = delete;
    LitColorCodedTriangles &operator=(const LitColorCodedTriangles &other) = delete;
    LitColorCodedTriangles(LitColorCodedTriangles &&other)                 = delete;
    LitColorCodedTriangles &operator=(LitColorCodedTriangles &&other)      = delete;
    //! Sets a color coding function. Pass empty function to unset.
    void SetColorCodingFunction(
        const std::function<Vectoid::Core::Vector<float>(const Vectoid::Core::Vector<float> &)> &colorCodingFunction);
    //! Turns on Gouraud shading.
    void EnableGouraudShading(const std::shared_ptr<Core::ExtendedTriangleProviderInterface> &triangleProvider);
    //! Turns off Gouraud shading.
    void DisableGouraudShading();
    
  protected:
    LitColorCodedTriangles(const std::shared_ptr<Context> &context,
                           const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);

    std::shared_ptr<Core::TriangleProviderInterface>                                  triangleProvider_;
    std::shared_ptr<Core::ExtendedTriangleProviderInterface>                          gouraudTriangleProvider_;
    std::function<Vectoid::Core::Vector<float>(const Vectoid::Core::Vector<float> &)> colorCodingFunction_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_LITCOLORCODEDTRIANGLES_H_
