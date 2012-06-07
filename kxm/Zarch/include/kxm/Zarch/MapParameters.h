//
//  MapParameters.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_MAPPARAMETERS_H_
#define KXM_ZARCH_MAPPARAMETERS_H_


#include <kxm/Vectoid/Range.h>


namespace kxm {
namespace Zarch {

//! Centrally holds parameters for a given map ("world", "level", ...).
/*!
 *  \ingroup Zarch
 *
 *  \param numCellsX
 *  \param numCellsZ
 *  Each must be even and at least <c>2</c>.
 *  
 *  \param cellSize
 *  A cell's projection into the <c>xz</c>-plane is a square (see above). This parameter controls
 *  the square's edge length.
 *
 *  Depending on the aforementioned parameters, the resulting terrain will cover in the
 *  <c>xz</c>-plane the axis-parallel, rectangular area given by <c>(x = -numCellsX/2 * cellSize,
 *  z = -numCellsZ/2 * cellSize)</c> and <c>(x = numCellsX/2 * cellSize, z = numCellsZ/2
 *  * cellSize)</c>.
 *
 *  \param numVisibleCellsX
 *  \param numVisibleCellsZ
 *  Number of cells in <c>x</c> and <c>z</c> directions, respectively, that are visible at a given
 *  point in time. Must both be even and at least <c>2</c>, and less or equal to their respective
 *  <c>numCells</c> parameter. Which subset of the terrain's cells is actually visible is controlled
 *  via the observer position set via SetObserverPosition().
 */
struct MapParameters {
    int            numCellsX, numCellsZ,
                   numVisibleCellsX, numVisibleCellsZ;
    float          cellSize,
                   gravity,
                   landerThrust,
                   cameraMinHeight,
                   maxThrusterParticleAge,
                   maxShotParticleAge,
                   thrusterExhaustVelocity,
                   thrusterExhaustInterval,
                   thrusterParticleSpread,
                   thrusterJetSize,
                   shotVelocity,
                   shotFiringInterval;
    Vectoid::Range xRange, zRange;
    int            numStars;
    Vectoid::Range starFieldCoordRange;
    float          starFieldMinHeight;
    
    MapParameters();
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_MAPPARAMETERS_H_
