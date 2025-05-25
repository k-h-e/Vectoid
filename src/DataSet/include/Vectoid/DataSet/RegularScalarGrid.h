///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_REGULARSCALARGRID_H_
#define VECTOID_DATASET_REGULARSCALARGRID_H_

#include <functional>
#include <vector>

#include <K/Core/Interface.h>
#include <Vectoid/Core/Range.h>
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {
    template<typename T> class BoundingBox;
}
}

namespace Vectoid {
namespace DataSet {

//! Three-dimensional regular grid holding scalars (of data type <c>float</c>). 
class RegularScalarGrid : public virtual K::Core::Interface {
  public:
    RegularScalarGrid()                                          = delete;
    RegularScalarGrid(int numPointsX, int numPointsY, int numPointsZ, const Core::BoundingBox<float> &spatialDomain);
    RegularScalarGrid(const RegularScalarGrid &other)            = delete;
    RegularScalarGrid &operator=(const RegularScalarGrid &other) = delete;
    RegularScalarGrid(RegularScalarGrid &&other)                 = delete;
    RegularScalarGrid &operator=(RegularScalarGrid &&other)      = delete;
    ~RegularScalarGrid()                                         = default;

    //! Tells the grid's dimensions (in numbers of points >= 2).
    void GetDimensions(int &numPointsX, int &numPointsY, int &numPointsZ) const;
    //! Returns the specified grid point.
    Core::Vector<float> Point(int gridX, int gridY, int gridZ) const;
    //! Gives access to the scalar value associated with the specified grid point.
    float &Value(int gridX, int gridY, int gridZ);
    //! Gives read access to the scalar value associated with the specified grid point.
    const float &Value(int gridX, int gridY, int gridZ) const;
    //! Samples scalar data values for all grid points using the specified function.
    void Sample(std::function<float(const Core::Vector<float> &point)> sampleFunction);

  private:
    int                numPointsX_;
    int                numPointsY_;
    int                numPointsZ_;
    Core::Range<float> xRange_;
    Core::Range<float> yRange_;
    Core::Range<float> zRange_;
    std::vector<float> values_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_REGULARSCALARGRID_H_
