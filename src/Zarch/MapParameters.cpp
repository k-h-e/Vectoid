#include <kxm/Zarch/MapParameters.h>

namespace kxm {
namespace Zarch {

MapParameters::MapParameters()
        : numCellsX(24),
          numCellsZ(24),
          numVisibleCellsX(12),
          numVisibleCellsZ(12),
          cellSize(1.0f),
          gravity(3.0f),
          landerThrust(10.0f),
          cameraMinHeight(5.0f),
          maxThrusterParticleAge(3.0f),
          maxShotParticleAge(3.0f),
          thrusterExhaustVelocity(3.0f),
          thrusterExhaustInterval(.01f),
          thrusterParticleSpread(.25f),
          thrusterJetSize(.1f * .65f),
          shotVelocity(3.0f),
          shotFiringInterval(.1f),
          xRange(0.0f),
          zRange(0.0f),
          numStars(100),
          starFieldCoordRange(0.0f),
          starFieldMinHeight(6.0f) {
    if (numCellsX < 2)
        numCellsX = 2;
    if (numCellsZ < 2)
        numCellsZ = 2;
    numCellsX = (numCellsX / 2) * 2;
    numCellsZ = (numCellsZ / 2) * 2;
    if (numVisibleCellsX < 2)
        numVisibleCellsX = 2;
    if (numVisibleCellsZ < 2)
        numVisibleCellsZ = 2;
    numVisibleCellsX = (numVisibleCellsX / 2) * 2;
    numVisibleCellsZ = (numVisibleCellsZ / 2) * 2;
    if (numVisibleCellsX > numCellsX)
        numVisibleCellsX = numCellsX;
    if (numVisibleCellsZ > numCellsZ)
        numVisibleCellsZ = numCellsZ;
    if (cellSize <= 0.0f)
        cellSize = 1.0f;
    
    xRange.Grow(-(float)(numCellsX / 2) * cellSize);
    xRange.Grow( (float)(numCellsX / 2) * cellSize);
    zRange.Grow(-(float)(numCellsZ / 2) * cellSize);
    zRange.Grow( (float)(numCellsZ / 2) * cellSize);
    
    starFieldCoordRange.Grow(-(float)(numCellsX / 4) * cellSize);
    starFieldCoordRange.Grow( (float)(numCellsX / 4) * cellSize);
}

}    // Namespace Zarch.
}    // Namespace kxm.

