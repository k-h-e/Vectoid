///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/RegularScalarGrid.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/BoundingBox.h>

using std::function;
using std::to_string;
using std::vector;
using K::Core::Log;
using K::Core::NumberTools;
using Vectoid::Core::BoundingBox;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace DataSet {

RegularScalarGrid::RegularScalarGrid(
    const Vector<float> &minCorner, const Vector<float> &cellSize, int numPointsX, int numPointsY, int numPointsZ,
    std::function<float(const Core::Vector<float> &point)> sampleFunction)
        : minCorner_{minCorner},
          cellSize_{cellSize},
          numPointsX_{numPointsX},
          numPointsY_{numPointsY},
          numPointsZ_{numPointsZ},
          sampleFunction_{sampleFunction},
          numPointsEvaluated_{0}  {
    if (cellSize_.x <= 0.0f) { cellSize_.x = 1.0f; }
    if (cellSize_.y <= 0.0f) { cellSize_.y = 1.0f; }
    if (cellSize_.z <= 0.0f) { cellSize_.z = 1.0f; }
    NumberTools::ClampMin(numPointsX_, 2);
    NumberTools::ClampMin(numPointsY_, 2);
    NumberTools::ClampMin(numPointsZ_, 2);
    values_.resize(static_cast<vector<float>::size_type>(numPointsX_)
                       * static_cast<vector<float>::size_type>(numPointsY_)
                       * static_cast<vector<float>::size_type>(numPointsZ_),
                   0.0f);
    valuePresentFlags_.resize(static_cast<vector<float>::size_type>(numPointsX_)
                                  * static_cast<vector<float>::size_type>(numPointsY_)
                                  * static_cast<vector<float>::size_type>(numPointsZ_),
                              false);
}

RegularScalarGrid::~RegularScalarGrid(){
    int numTotal { numPointsX_ * numPointsY_ * numPointsZ_ };
    int percent  { static_cast<int>(100.0f*static_cast<float>(numPointsEvaluated_)/static_cast<float>(numTotal)
                                        + .5f) };
    Log::Print(Log::Level::Debug, this, [&]{
        return "evaluated " + to_string(numPointsEvaluated_) + " of " + to_string(numTotal) + " grid points ("
                   + to_string(percent) + "%)";
    });
}

void RegularScalarGrid::GetDimensions(int &numPointsX, int &numPointsY, int &numPointsZ) const {
    numPointsX = numPointsX_; 
    numPointsY = numPointsY_; 
    numPointsZ = numPointsZ_; 
}

Vector<float> RegularScalarGrid::Point(int gridX, int gridY, int gridZ) const {
    NumberTools::Clamp(gridX, 0, numPointsX_ - 1);
    NumberTools::Clamp(gridY, 0, numPointsY_ - 1);
    NumberTools::Clamp(gridZ, 0, numPointsZ_ - 1);
    return Vector{minCorner_.x + static_cast<float>(gridX)*cellSize_.x,
                  minCorner_.y + static_cast<float>(gridY)*cellSize_.y,
                  minCorner_.z + static_cast<float>(gridZ)*cellSize_.z};
}

float RegularScalarGrid::Value(int gridX, int gridY, int gridZ) {
    NumberTools::Clamp(gridX, 0, numPointsX_ - 1);
    NumberTools::Clamp(gridY, 0, numPointsY_ - 1);
    NumberTools::Clamp(gridZ, 0, numPointsZ_ - 1);
    int index { gridZ*numPointsX_*numPointsY_ + gridY*numPointsX_ + gridX };
    if (!valuePresentFlags_[index]) {
        values_[index] = sampleFunction_(Point(gridX, gridY, gridZ));
        valuePresentFlags_[index] = true;
        ++numPointsEvaluated_;
    }
    return values_[index];
}

}    // Namespace Vectoid.
}    // Namespace K.
