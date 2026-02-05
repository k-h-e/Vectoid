///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
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
 *  The resulting terrain will cover in the <c>xz</c>-plane the axis-parallel, rectangular area given by
 *  <c>(x = -numCellsX/2 * cellSize, z = -numCellsZ/2 * cellSize)</c> and
 *  <c>(x = numCellsX/2 * cellSize, z = numCellsZ/2 * cellSize)</c>.
 */
struct MapParameters {
    int                         numCellsX;            //! Must be even and at least <c>2</c>.
    int                         numCellsZ;            //! Must be even and at least <c>2</c>.
    int                         numVisibleCellsX;     //! Number of cells in <c>x</c> and <c>z</c> directions,
    int                         numVisibleCellsZ;     //! respectively, that are visible at a given point in time. Must
                                                      //! both be even and at least <c>2</c>, and less or equal to
                                                      //! their respective <c>numCells</c> parameter. Which subset of
                                                      //! the terrain's cells is actually visible is controlled via the
                                                      //! observer position set via SetObserverPosition().
    float                       cellSize;             //! A cell's projection into the <c>xz</c>-plane is a square (see
                                                      //! above). This parameter controls the square's edge length.
    float                       gravity;
    float                       landerThrust;
    float                       cameraMinHeight;
    float                       maxThrusterParticleAge;
    float                       maxShotParticleAge;
    float                       thrusterExhaustVelocity;
    float                       thrusterExhaustInterval;
    float                       thrusterParticleSpread;
    float                       thrusterJetSize;
    float                       shotVelocity;
    float                       shotFiringInterval;
    Vectoid::Core::Range<float> xRange;
    Vectoid::Core::Range<float> zRange;
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
    xRange.CorrectForObserver(inOutPosition->x, observerPosition.x);
    zRange.CorrectForObserver(inOutPosition->z, observerPosition.z);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_MAPPARAMETERS_H_
