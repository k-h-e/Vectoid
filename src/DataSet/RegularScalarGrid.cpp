///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/RegularScalarGrid.h>

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/BoundingBox.h>

using std::function;
using std::vector;
using K::Core::NumberTools;
using Vectoid::Core::BoundingBox;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace DataSet {

RegularScalarGrid::RegularScalarGrid(int numPointsX, int numPointsY, int numPointsZ,
                                     const BoundingBox<float> &spatialDomain)
        : numPointsX_{numPointsX},
          numPointsY_{numPointsY},
          numPointsZ_{numPointsZ},
          xRange_{spatialDomain.MinCorner().x, spatialDomain.MaxCorner().x},
          yRange_{spatialDomain.MinCorner().y, spatialDomain.MaxCorner().y},
          zRange_{spatialDomain.MinCorner().z, spatialDomain.MaxCorner().z} {
    NumberTools::ClampMin(numPointsX_, 2);
    NumberTools::ClampMin(numPointsY_, 2);
    NumberTools::ClampMin(numPointsZ_, 2);
    values_.resize(static_cast<vector<float>::size_type>(numPointsX_)
                       * static_cast<vector<float>::size_type>(numPointsY_)
                       * static_cast<vector<float>::size_type>(numPointsZ_),
                   0.0f);
}

void RegularScalarGrid::GetDimensions(int &numPointsX, int &numPointsY, int &numPointsZ) const {
    numPointsX = numPointsX_; 
    numPointsY = numPointsY_; 
    numPointsZ = numPointsZ_; 
}

Vector<float> RegularScalarGrid::Point(int gridX, int gridY, int gridZ) const {
    return Vector{xRange_.AffineCombination(static_cast<float>(gridX) / static_cast<float>(numPointsX_ - 1)),
                  yRange_.AffineCombination(static_cast<float>(gridY) / static_cast<float>(numPointsY_ - 1)),
                  zRange_.AffineCombination(static_cast<float>(gridZ) / static_cast<float>(numPointsZ_ - 1))};
}

float &RegularScalarGrid::Value(int gridX, int gridY, int gridZ) {
    NumberTools::Clamp(gridX, 0, numPointsX_ - 1);
    NumberTools::Clamp(gridY, 0, numPointsY_ - 1);
    NumberTools::Clamp(gridZ, 0, numPointsZ_ - 1);
    return values_[gridZ*numPointsX_*numPointsY_ + gridY*numPointsX_ + gridX];
}

const float &RegularScalarGrid::Value(int gridX, int gridY, int gridZ) const {
    return const_cast<RegularScalarGrid *>(this)->Value(gridX, gridY, gridZ);
}

void RegularScalarGrid::Sample(function<float(const Vector<float> &point)> sampleFunction) {
    for (int z = 0; z < numPointsZ_; ++z) {
        for (int y = 0; y < numPointsY_; ++y) {
            for (int x = 0; x < numPointsX_; ++x) {
                Value(x, y, z) = sampleFunction(Point(x, y, z));
            } 
        }    
    }
}

}    // Namespace Vectoid.
}    // Namespace K.
