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
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace DataSet {

//! Three-dimensional regular grid holding scalars (of data type <c>float</c>) for its data points.
/*!
 *  Scalar values get lazily evaluated via the provided sampling function. The scalar value for any given grid point
 *  gets evaluated only once and is then buffered for future reference. 
 */
class RegularScalarGrid : public virtual K::Core::Interface {
  public:
    RegularScalarGrid()                                          = delete;
    RegularScalarGrid(const Core::Vector<float> &minCorner, const Core::Vector<float> &cellSize, int numPointsX,
                      int numPointsY, int numPointsZ,
                      std::function<float(const Core::Vector<float> &point)> sampleFunction);
    RegularScalarGrid(const RegularScalarGrid &other)            = delete;
    RegularScalarGrid &operator=(const RegularScalarGrid &other) = delete;
    RegularScalarGrid(RegularScalarGrid &&other)                 = delete;
    RegularScalarGrid &operator=(RegularScalarGrid &&other)      = delete;
    ~RegularScalarGrid();

    //! Tells the grid's dimensions (in numbers of points >= 2).
    void GetDimensions(int &numPointsX, int &numPointsY, int &numPointsZ) const;
    //! Returns the specified grid point.
    Core::Vector<float> Point(int gridX, int gridY, int gridZ) const;
    //! Returns the scalar value associated with the specified grid point.
    float Value(int gridX, int gridY, int gridZ);

  private:
    Core::Vector<float>                                    minCorner_;
    Core::Vector<float>                                    cellSize_;
    int                                                    numPointsX_;
    int                                                    numPointsY_;
    int                                                    numPointsZ_;
    std::vector<float>                                     values_;
    std::vector<bool>                                      valuePresentFlags_;
    std::function<float(const Core::Vector<float> &point)> sampleFunction_;
    int                                                    numPointsEvaluated_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_REGULARSCALARGRID_H_
