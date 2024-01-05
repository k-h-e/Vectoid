///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_SIMPLEGEOMETRY_H_
#define VECTOID_SCENEGRAPH_SIMPLEGEOMETRY_H_

#include <vector>
#include <Vectoid/Core/HasBoundingBoxInterface.h>
#include <Vectoid/Core/BoundingBox.h>

namespace Vectoid {

namespace Core {
    template<typename T> class Vector;
}

namespace SceneGraph {

namespace OpenGL {
    class SimpleGeometryRenderer;
}
namespace Vulkan {
    class SimpleGeometryRenderer;
}

//! Simple triangle-soup geometry.
class SimpleGeometry : public virtual Vectoid::Core::HasBoundingBoxInterface {
  public:
    friend class OpenGL::SimpleGeometryRenderer;
    friend class Vulkan::SimpleGeometryRenderer;
  
    SimpleGeometry();
    SimpleGeometry(const SimpleGeometry &other) = delete;
    SimpleGeometry &operator=(const SimpleGeometry &other) = delete;
    void GetBoundingBox(Vectoid::Core::BoundingBox<float> *outBoundingBox);
    void AddTriangle(
        const Vectoid::Core::Vector<float> &vertex0, const Vectoid::Core::Vector<float> &vertex1,
        const Vectoid::Core::Vector<float> &vertex2, const Vectoid::Core::Vector<float> &color);
    void Move(const Vectoid::Core::Vector<float> &translation);
    void Scale(float factor);
    static std::shared_ptr<SimpleGeometry> NewLanderGeometry();
    static std::shared_ptr<SimpleGeometry> NewSaucerGeometry();
    
  private:
    int                               numTriangles_;
    std::vector<float>                vertexArray_,
                                      colorArray_;
    Vectoid::Core::BoundingBox<float> boundingBox_;
    bool                              boundingBoxValid_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_SIMPLEGEOMETRY_H_
