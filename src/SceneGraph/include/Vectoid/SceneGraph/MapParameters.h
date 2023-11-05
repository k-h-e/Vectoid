///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_MAPPARAMETERS_H_
#define VECTOID_SCENEGRAPH_MAPPARAMETERS_H_

#include <Vectoid/Core/Range.h>
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace SceneGraph {

//! Centrally holds parameters for a given map ("world", "level", ...).
/*!
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
    int                         numCellsX, numCellsZ,
                                numVisibleCellsX, numVisibleCellsZ;
    float                       cellSize,
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
    Vectoid::Core::Range<float> xRange, zRange;
    int                         numStars;
    Vectoid::Core::Range<float> starFieldCoordRange;
    float                       starFieldMinHeight;
    
    MapParameters();
    //! Applies \ref Vectoid::Range::CorrectForObserver() for <c>x</c>- and <c>z</c>-directions.
    inline void CorrectForObserver(Vectoid::Core::Vector<float> *inOutPosition,
                                   const Vectoid::Core::Vector<float> &observerPosition) const;
};

void MapParameters::CorrectForObserver(Vectoid::Core::Vector<float> *inOutPosition,
                                       const Vectoid::Core::Vector<float> &observerPosition) const {
    xRange.CorrectForObserver(&inOutPosition->x, observerPosition.x);
    zRange.CorrectForObserver(&inOutPosition->z, observerPosition.z);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_MAPPARAMETERS_H_
