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

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <kxm/Core/IntModN.h>
#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>


namespace kxm {
namespace Vectoid {

//! Terrain as known from the Acorn Archimedes game "Zarch".
/*! 
 *  \ingroup Vectoid
 *
 *  The terrain extents in the <c>x</c> and <c>z</c> directions, with the <c>y</c> direction
 *  corresponding to the concept of height. The terrain is composed of "cells", the projection into
 *  the <c>xz</c>-plane of which are squares of a fixed size. The heights of a cell's four vertices
 *  are given by the corresponding datapoints of a rectilinear grid, the dimensions of which match
 *  the numbers of cells in <c>x</c> and <c>z</c> directions respectively.
 */ 
class ZarchTerrain : public virtual GeometryInterface {
  public:
    //! Well, constructor.
    /*!
     *  \param numCellsX
     *  \param numCellsZ
     *  Each must be even and at least <c>2</c>.
     *  
     *  \param cellSize
     *  A cell's projection into the <c>xz</c>-plane is a square (see above). This parameter
     *  controls the square's edge length.
     *
     *  Depending on the aforementioned parameters, the resulting terrain will cover in the
     *  <c>xz</c>-plane the axis-parallel, rectangular area given by <c>(x = -numCellsX/2 *
     *  cellSize, z = -numCellsZ/2 * cellSize)</c> and <c>(x = numCellsX/2 * cellSize,
     *  z = numCellsZ/2 * cellSize)</c>.
     *
     *  \param numVisibleCellsX
     *  \param numVisibleCellsZ
     *  Number of cells in <c>x</c> and <c>z</c> directions, respectively, that are visible at a
     *  given point in time. Must both be even and at least <c>2</c>, and less or equal to their 
     *  respective <c>numCells</c> parameter. Which subset of the terrain's cells is actually
     *  visible is controlled via the observer position set via SetObserverPosition().
     *  
     */
    ZarchTerrain(int numCellsX, int numCellsZ, float cellSize,
                 int numVisibleCellsX, int numVisibleCellsZ);
    
    //! Sets the observer's position in the <c>xz</c>-plane.
    void SetObserverPosition(float x, float z); 
    void Render(RenderContext *context);
    
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
    
    int                                       numCellsX_, numCellsZ_,
                                              numVisibleCellsX_, numVisibleCellsZ_;
    float                                     cellSize_,
                                              observerX_, observerZ_;
    std::vector<float>                        heights_;
    std::vector<GLfloat>                      vertices_;
    boost::random::mt19937                    randomGenerator_;
    boost::random::uniform_int_distribution<> randomFormation_,
                                              randomCellX_, randomCellZ_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_ZARCHTERRAIN_H_
