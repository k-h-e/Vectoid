///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_GEOMETRYTOOLS_H_
#define VECTOID_DATASET_GEOMETRYTOOLS_H_

namespace Vectoid {
    namespace Core {
        template<typename T> class Vector;
    }
}

namespace Vectoid {
namespace DataSet {

class SimpleTriangleList;

//! Geometry tools.
class GeometryTools {
  public:
    //! Adds a line in the x/y plane.
    static void AddLineXY(SimpleTriangleList *triangleList, const Vectoid::Core::Vector<float> &startPoint,
                          const Vectoid::Core::Vector<float> &endPoint, float width);
    //! Adds a filled circle in the x/y plane.
    static void AddFilledCircleXY(SimpleTriangleList *triangleList, const Vectoid::Core::Vector<float> &center,
                                  float radius, int numSectors);
    //! Adds a filled circle sector in the x/y plane.
    static void AddFilledCircleSectorXY(SimpleTriangleList *triangleList, float radius, float centerAngle,
                                        float openingAngle, int numSectors);
    //! Adds a circle (outline) in the x/y plane.
    static void AddCircleXY(SimpleTriangleList *triangleList, float radius, int numSectors, float width);
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_GEOMETRYTOOLS_H_
