#ifndef KXM_ZARCH_TERRAIN_H_
#define KXM_ZARCH_TERRAIN_H_

#include <vector>
#include <memory>
#include <random>

#include <kxm/Core/IntModN.h>
#include <kxm/Core/Interface.h>
#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Zarch/MapParameters.h>

namespace kxm {
namespace Zarch {

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
class Terrain : public virtual Core::Interface {
  public:
    //! Well, constructor.
    Terrain(std::shared_ptr<const MapParameters> mapParameters);
    
    //! Returns the height at the specified position in the <c>xz</c>-plane. 
    inline float Height(float x, float z);
    //! Returns the height at the specified position in the <c>xz</c>-plane. 
    inline float InterpolateHeight(kxm::Core::IntModN cellX, kxm::Core::IntModN cellZ,
                                   float remainderX, float remainderZ);
    //! Gives access to the height for the specified cell data point.
    inline float &CellHeight(int cellX, int cellZ);
    //! Gives access to the height for the specified cell data point.
    inline Vectoid::Vector &CellColor(int cellX, int cellZ);
    
  private:
    enum FormationType { MountainFormation = 0,
                         ValleyFormation,
                         NumFormations };
    
    Terrain(const Terrain &other);
    Terrain &operator=(const Terrain &other);
    
    void GenerateTerrain();
    void GenerateMountainFormation();
    void GenerateValleyFormation();
    
    std::shared_ptr<const MapParameters> mapParameters_;
    std::vector<float>                   heights_;
    std::vector<Vectoid::Vector>         colors_;
    std::default_random_engine           randomEngine_;
    std::uniform_int_distribution<>      randomFormation_,
                                         randomCellX_, randomCellZ_;
};

float Terrain::Height(float x, float z) {
    mapParameters_->xRange.ClampModulo(&x);
    mapParameters_->zRange.ClampModulo(&z);
    int   cellX, cellZ;
    float remainderX, remainderZ;    
    mapParameters_->xRange.ComputeSlotUnchecked(x, mapParameters_->cellSize, &cellX, &remainderX);
    mapParameters_->zRange.ComputeSlotUnchecked(z, mapParameters_->cellSize, &cellZ, &remainderZ);
    Core::IntModN cellXModN(mapParameters_->numCellsX, 0);  cellXModN.SetValue(cellX);
    Core::IntModN cellZModN(mapParameters_->numCellsZ, 0);  cellZModN.SetValue(cellZ);
    return InterpolateHeight(cellXModN, cellZModN, remainderX, remainderZ);
}

float Terrain::InterpolateHeight(
        Core::IntModN cellX, Core::IntModN cellZ, float remainderX, float remainderZ) {
    float s = remainderX / mapParameters_->cellSize,
          t = remainderZ / mapParameters_->cellSize;
    return   (1.0f - t) * (  (1.0f - s) * CellHeight(cellX.ToInt(), cellZ.ToInt())
                           + s          * CellHeight((cellX + 1).ToInt(), cellZ.ToInt()))
           + t          * (  (1.0f - s) * CellHeight(cellX.ToInt(), (cellZ + 1).ToInt())
                           + s          * CellHeight((cellX + 1).ToInt(), (cellZ + 1).ToInt()));
}

float &Terrain::CellHeight(int cellX, int cellZ) {
    return heights_[cellZ*mapParameters_->numCellsX + cellX];
}

inline Vectoid::Vector &Terrain::CellColor(int cellX, int cellZ) {
    return colors_[cellZ*mapParameters_->numCellsX + cellX];
}

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_TERRAIN_H_
