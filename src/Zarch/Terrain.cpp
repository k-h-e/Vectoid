#include <kxm/Zarch/Terrain.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Core/IntModN.h>
#include <kxm/Zarch/MapParameters.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

Terrain::Terrain(shared_ptr<const MapParameters> mapParameters)
        : mapParameters_(mapParameters) {
    int numCells = mapParameters_->numCellsX * mapParameters_->numCellsZ;
    heights_.resize(numCells);
    colors_.resize(numCells);
    randomFormation_ = uniform_int_distribution<>(0, (int)NumFormations - 1);
    randomCellX_     = uniform_int_distribution<>(0, mapParameters_->numCellsX - 1);
    randomCellZ_     = uniform_int_distribution<>(0, mapParameters_->numCellsZ - 1);
    GenerateTerrain();
}

void Terrain::GenerateTerrain() {
    int  i           = 0;
    bool secondColor = false;
    for (int x = 0; x < mapParameters_->numCellsX; x++) {
        for (int z = 0; z < mapParameters_->numCellsZ; z++) {
            heights_[i] = 0.0f;
            if (secondColor)
                colors_[i] = Vector(.3f, .45f, .15f);
            else
                colors_[i] = Vector(.4f, .6f, .2f);
            i++;
            secondColor = !secondColor;
        }
        secondColor = !secondColor;
    }
    
    for (int i = 0; i < 100; i++) {
        FormationType formation = (FormationType)randomFormation_(randomEngine_);
        switch (formation) {
            case ValleyFormation:
                GenerateValleyFormation();
                break;
            case MountainFormation:
            default:
                GenerateMountainFormation();
                break;
        }
    }
    
    for (int i = 0; i < mapParameters_->numCellsX; i++) {
        heights_[i]                                                             = 1.0f;
        heights_[(mapParameters_->numCellsZ - 1)*mapParameters_->numCellsX + i] = 1.0f;
    }
    for (int i = 0; i < mapParameters_->numCellsZ; i++) {
        heights_[i*mapParameters_->numCellsX]                                   = 1.0f;
        heights_[i*mapParameters_->numCellsX + (mapParameters_->numCellsX - 1)] = 1.0f;
    }
    
    Range heightRange(heights_[0]);
    for (int x = 0; x < mapParameters_->numCellsX; x++) {
        for (int z = 0; z < mapParameters_->numCellsZ; z++) {
            heightRange.Grow(CellHeight(x, z));
        }
    }
    float seaLevel = heightRange.AffineCombination(.2f);
    for (int x = 0; x < mapParameters_->numCellsX; x++) {
        for (int z = 0; z < mapParameters_->numCellsZ; z++) {
            CellHeight(x, z) -= seaLevel;
        }
    }

    // TESTING: Base...
    for (int x = -2; x <= 2; ++x) {
        for (int z = -2; z <= 2; ++z) {
            int xx = mapParameters_->numCellsX/2 + x,
                zz = mapParameters_->numCellsZ/2 + z;
            CellHeight(xx, zz) = 1.5f;
        }
    }
    for (int x = -3; x <= 2; ++x) {
        for (int z = -3; z <= 2; ++z) {
            int xx = mapParameters_->numCellsX/2 + x,
                zz = mapParameters_->numCellsZ/2 + z;
            CellColor(xx, zz) = (xx + zz) % 2 ? Vector(.4f, .4f, .4f) : Vector(.6f, .6f, .6f);
        }
    }

    // Water...
    for (int x = 0; x < mapParameters_->numCellsX; x++) {
        for (int z = 0; z < mapParameters_->numCellsZ; z++) {
            IntModN xMod(mapParameters_->numCellsX, 0);
            xMod.SetValue(x);
            IntModN zMod(mapParameters_->numCellsZ, 0);
            zMod.SetValue(z);
            if (       (CellHeight(x, z)                                   <= 0.0f)
                    && (CellHeight((xMod + 1).ToInt(), z)                  <= 0.0f)
                    && (CellHeight(x, (zMod + 1).ToInt())                  <= 0.0f)
                    && (CellHeight((xMod + 1).ToInt(), (zMod + 1).ToInt()) <= 0.0f)) {
                CellHeight(x, z)                                   = 0.0f;
                CellHeight((xMod + 1).ToInt(), z)                  = 0.0f;
                CellHeight(x, (zMod + 1).ToInt())                  = 0.0f;
                CellHeight((xMod + 1).ToInt(), (zMod + 1).ToInt()) = 0.0f;
                CellColor(x, z) = Vector(.2f, .2f, .8f);
            }
        }
    }
}

void Terrain::GenerateMountainFormation() {
    IntModN baseCellX(mapParameters_->numCellsX, 0);
    baseCellX.SetValue(randomCellX_(randomEngine_));
    IntModN baseCellZ(mapParameters_->numCellsZ, 0);
    baseCellZ.SetValue(randomCellZ_(randomEngine_));
    int   extent = 5;
    float height = 1.5f;
    for (int x = -extent; x <= extent; x++) {
        for (int z = -extent; z <= extent; z++) {
            float normalizedRadius =   (float)(sqrt((float)x*(float)x + (float)z*(float)z))
                                     / (float)extent,
                  cellHeight       = (1.0f - normalizedRadius*normalizedRadius) * height;
            if (cellHeight < 0.0f)
                cellHeight = 0.0f;
            float &targetHeight = CellHeight((baseCellX + x).ToInt(), (baseCellZ + z).ToInt());
            targetHeight = .5f*targetHeight + .5f*cellHeight;
        }
    }
}

void Terrain::GenerateValleyFormation() {
    IntModN baseCellX(mapParameters_->numCellsX, 0);
    baseCellX.SetValue(randomCellX_(randomEngine_));
    IntModN baseCellZ(mapParameters_->numCellsZ, 0);
    baseCellZ.SetValue(randomCellZ_(randomEngine_));
    int   extent = 2;
    float height = -.5f;
    for (int x = -extent; x <= extent; x++) {
        for (int z = -extent; z <= extent; z++) {
            float normalizedRadius =   (float)(sqrt((float)x*(float)x + (float)z*(float)z))
                                     / (float)extent,
                  cellHeight       = (1.0f - normalizedRadius*normalizedRadius) * height;
            if (cellHeight < 0.0f)
                cellHeight = 0.0f;
            float &targetHeight = CellHeight((baseCellX + x).ToInt(), (baseCellZ + z).ToInt());
            targetHeight = .5f*targetHeight + .5f*cellHeight;
        }
    }
}

}    // Namespace Zarch.
}    // Namespace kxm.
