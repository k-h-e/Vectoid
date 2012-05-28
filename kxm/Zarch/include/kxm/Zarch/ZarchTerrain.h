//
//  ZarchTerrain.h
//  kxm
//
//  Created by Kai Hergenroether on 4/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_ZARCHTERRAIN_H_
#define KXM_VECTOID_ZARCHTERRAIN_H_


#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <kxm/Core/IntModN.h>
#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>


namespace kxm {
namespace Zarch {

class MapParameters;

//! Terrain as known from the Acorn Archimedes game "Zarch".
/*! 
 *  \ingroup Zarch
 *
 *  The terrain extents in the <c>x</c> and <c>z</c> directions, with the <c>y</c> direction
 *  corresponding to the concept of height. The terrain is composed of "cells", the projection into
 *  the <c>xz</c>-plane of which are squares of a fixed size. The heights of a cell's four vertices
 *  are given by the corresponding datapoints of a rectilinear grid, the dimensions of which match
 *  the numbers of cells in <c>x</c> and <c>z</c> directions respectively.
 *
 *  The terrain has "modulo-characteristics" in <c>x</c>- and <c>z</c>-directions (it repeats
 *  itself). 
 */ 
class ZarchTerrain : public virtual Vectoid::GeometryInterface {
  public:
    //! Well, constructor.
    ZarchTerrain(boost::shared_ptr<const MapParameters> mapParameters);
    
    //! Sets the observer's position in the <c>xz</c>-plane.
    void SetObserverPosition(float x, float z);
    //! Returns the height at the specified position in the <c>xz</c>-plane. 
    float ComputeHeight(float x, float z);
    void Render(Vectoid::RenderContext *context);
    
  private:
    enum FormationType { MountainFormation = 0,
                         ValleyFormation,
                         NumFormations };
    
    ZarchTerrain(const ZarchTerrain &other);
    ZarchTerrain &operator=(const ZarchTerrain &other);
    
    float InterpolateHeight(kxm::Core::IntModN cellX, kxm::Core::IntModN cellZ,
                            float remainderX, float remainderZ);
    void GenerateTerrain();
    void GenerateMountainFormation();
    void GenerateValleyFormation();
    float &Height(int cellX, int cellZ);
    
    boost::shared_ptr<const MapParameters>    mapParameters_;
    float                                     observerX_, observerZ_;
    std::vector<float>                        heights_;
    std::vector<GLfloat>                      vertices_;
    boost::random::mt19937                    randomGenerator_;
    boost::random::uniform_int_distribution<> randomFormation_,
                                              randomCellX_, randomCellZ_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_VECTOID_ZARCHTERRAIN_H_
