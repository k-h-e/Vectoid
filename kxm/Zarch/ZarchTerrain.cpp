//
//  ZarchTerrain.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/ZarchTerrain.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Core/IntModN.h>
#include <kxm/Zarch/MapParameters.h>

using std::vector;
using boost::shared_ptr;
using boost::random::uniform_int_distribution;
using kxm::Core::IntModN;
using kxm::Vectoid::RenderContext;


namespace kxm {
namespace Zarch {

ZarchTerrain::ZarchTerrain(shared_ptr<const MapParameters> mapParameters)
        : mapParameters_(mapParameters),
          observerX_(0.0f),
          observerZ_(0.0f) {
    heights_.resize(mapParameters_->numCellsX * mapParameters_->numCellsZ);
    vertices_.resize(2 * 3 * 3);    // Two triangles.
    randomFormation_ = uniform_int_distribution<>(0, (int)NumFormations - 1);
    randomCellX_     = uniform_int_distribution<>(0, mapParameters_->numCellsX - 1);
    randomCellZ_     = uniform_int_distribution<>(0, mapParameters_->numCellsZ - 1);
    GenerateTerrain();
}

void ZarchTerrain::SetObserverPosition(float x, float z) {
    observerX_ = x;
    observerZ_ = z;
}

float ZarchTerrain::ComputeHeight(float x, float z) {
    mapParameters_->xRange.ClampModulo(&x);
    mapParameters_->zRange.ClampModulo(&z);
    int   cellX, cellZ;
    float remainderX, remainderZ;    
    mapParameters_->xRange.ComputeSlotUnchecked(x, mapParameters_->cellSize, &cellX, &remainderX);
    mapParameters_->zRange.ComputeSlotUnchecked(z, mapParameters_->cellSize, &cellZ, &remainderZ);
    IntModN cellXModN(mapParameters_->numCellsX, 0);  cellXModN.SetValue(cellX);
    IntModN cellZModN(mapParameters_->numCellsZ, 0);  cellZModN.SetValue(cellZ);
    return InterpolateHeight(cellXModN, cellZModN, remainderX, remainderZ);
}

void ZarchTerrain::Render(RenderContext *context) {
    glVertexPointer(3, GL_FLOAT, 0, &vertices_[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    float   baseX =   observerX_
                    +   (float)(mapParameters_->numCellsX/2 - mapParameters_->numVisibleCellsX/2)
                      * mapParameters_->cellSize,
            baseZ =   observerZ_
                    +   (float)(mapParameters_->numCellsZ/2 - mapParameters_->numVisibleCellsZ/2)
                      * mapParameters_->cellSize;
    int     baseCellX = (int)(baseX / mapParameters_->cellSize),
            baseCellZ = (int)(baseZ / mapParameters_->cellSize);
    float   remainderX = baseX - (float)baseCellX*mapParameters_->cellSize,
            remainderZ = baseZ - (float)baseCellZ*mapParameters_->cellSize;
    if (baseX < 0.0f) {
        --baseCellX;
        remainderX += mapParameters_->cellSize;
    }
    if (baseZ < 0.0f) {
        --baseCellZ;
        remainderZ += mapParameters_->cellSize;
    }
    float   lowX, lowZ, highX, highZ,
            heightLowXLowZ, heightLowXHighZ, heightHighXLowZ, heightHighXHighZ;
    bool    interpolateLowX, interpolateHighX, interpolateLowZ, interpolateHighZ;
    IntModN modCellX = IntModN(mapParameters_->numCellsX, 0) + baseCellX;
    int     cellX    = baseCellX;
    GLfloat *vertexData;
    for (int x = 0; x <= mapParameters_->numVisibleCellsX; x++) {
        lowX             = (float)(cellX - mapParameters_->numCellsX/2) * mapParameters_->cellSize;
        interpolateLowX  = false;
        highX            = lowX + mapParameters_->cellSize;
        interpolateHighX = false;
        if (x == 0) {
            lowX             += remainderX;
            interpolateLowX   = true;
        }
        else if (x == mapParameters_->numVisibleCellsX) {
            highX            -= mapParameters_->cellSize - remainderX;
            interpolateHighX  = true;
        }
        IntModN modCellZ = IntModN(mapParameters_->numCellsZ, 0) + baseCellZ;
        int     cellZ    = baseCellZ;  
        for (int z = 0; z <= mapParameters_->numVisibleCellsZ; z++) {
            lowZ             =   (float)(cellZ - mapParameters_->numCellsZ/2)
                               * mapParameters_->cellSize;
            interpolateLowZ  = false;
            highZ            = lowZ + mapParameters_->cellSize;
            interpolateHighZ = false;
            if (z == 0) {
                lowZ             += remainderZ;
                interpolateLowZ   = true;
            }
            else if (z == mapParameters_->numVisibleCellsZ) {
                highZ            -= mapParameters_->cellSize - remainderZ;
                interpolateHighZ  = true;
            }
            
            heightLowXLowZ   =   (interpolateLowX || interpolateLowZ)
                               ? InterpolateHeight(modCellX, modCellZ,
                                                   interpolateLowX  ? remainderX : 0.0f,
                                                   interpolateLowZ  ? remainderZ : 0.0f)
                               : Height(modCellX.ToInt(), modCellZ.ToInt());
            heightLowXHighZ  =   (interpolateLowX || interpolateHighZ)
                               ? InterpolateHeight(modCellX, modCellZ,
                                                   interpolateLowX  ? remainderX : 0.0f,
                                                   interpolateHighZ ? remainderZ
                                                                    : mapParameters_->cellSize)
                               : Height(modCellX.ToInt(), (modCellZ + 1).ToInt());
            heightHighXLowZ  =   (interpolateHighX || interpolateLowZ)
                               ? InterpolateHeight(modCellX, modCellZ,
                                                   interpolateHighX ? remainderX
                                                                    : mapParameters_->cellSize,
                                                   interpolateLowZ  ? remainderZ : 0.0f)
                               : Height((modCellX + 1).ToInt(), modCellZ.ToInt());
            heightHighXHighZ =   (interpolateHighX || interpolateHighZ)
                               ? InterpolateHeight(modCellX, modCellZ,
                                                   interpolateHighX ? remainderX
                                                                    : mapParameters_->cellSize,
                                                   interpolateHighZ ? remainderZ
                                                                    : mapParameters_->cellSize)
                               : Height((modCellX + 1).ToInt(), (modCellZ + 1).ToInt());
            
            vertexData = &vertices_[0];
            *vertexData++ = lowX;   *vertexData++ = heightLowXLowZ;    *vertexData++ = lowZ;
            *vertexData++ = lowX;   *vertexData++ = heightLowXHighZ;   *vertexData++ = highZ;
            *vertexData++ = highX;  *vertexData++ = heightHighXLowZ;   *vertexData++ = lowZ;

            *vertexData++ = highX;  *vertexData++ = heightHighXLowZ;   *vertexData++ = lowZ;
            *vertexData++ = lowX;   *vertexData++ = heightLowXHighZ;   *vertexData++ = highZ;
            *vertexData++ = highX;  *vertexData++ = heightHighXHighZ;  *vertexData++ = highZ;
            
            if (modCellX.ToInt() % 2 == modCellZ.ToInt() % 2)
                glColor4f(.4f, .6f, .2f, 1.0f);
            else
                glColor4f(.3f, .45f, .15f, 1.0f);
            glDrawArrays(GL_TRIANGLES, 0, 2 * 3);
            
            ++modCellZ;
            ++cellZ;
        }
        ++modCellX;
        ++cellX;
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

float ZarchTerrain::InterpolateHeight(IntModN cellX, IntModN cellZ,
                                      float remainderX, float remainderZ) {
    float s = remainderX / mapParameters_->cellSize,
          t = remainderZ / mapParameters_->cellSize;
    return   (1.0f - t) * (  (1.0f - s) * Height(cellX.ToInt(), cellZ.ToInt())
                           + s          * Height((cellX + 1).ToInt(), cellZ.ToInt()))
           + t          * (  (1.0f - s) * Height(cellX.ToInt(), (cellZ + 1).ToInt())
                           + s          * Height((cellX + 1).ToInt(), (cellZ + 1).ToInt()));
}

void ZarchTerrain::GenerateTerrain() {
    for (int i = 0; i < mapParameters_->numCellsX * mapParameters_->numCellsZ; i++)
        heights_[i] = 0.0f;
    for (int i = 0; i < 100; i++) {
        FormationType formation = (FormationType)randomFormation_(randomGenerator_);
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
}

void ZarchTerrain::GenerateMountainFormation() {
    IntModN baseCellX(mapParameters_->numCellsX, 0);
    baseCellX.SetValue(randomCellX_(randomGenerator_));
    IntModN baseCellZ(mapParameters_->numCellsZ, 0);
    baseCellZ.SetValue(randomCellZ_(randomGenerator_));
    int   extent = 5;
    float height = 1.5f;
    for (int x = -extent; x <= extent; x++) {
        for (int z = -extent; z <= extent; z++) {
            float normalizedRadius =   (float)(sqrt((float)x*(float)x + (float)z*(float)z))
                                     / (float)extent,
                  cellHeight       = (1.0f - normalizedRadius*normalizedRadius) * height;
            if (cellHeight < 0.0f)
                cellHeight = 0.0f;
            float &targetHeight = Height((baseCellX + x).ToInt(), (baseCellZ + z).ToInt());
            targetHeight = .5f*targetHeight + .5f*cellHeight;
        }
    }
}

void ZarchTerrain::GenerateValleyFormation() {
    IntModN baseCellX(mapParameters_->numCellsX, 0);
    baseCellX.SetValue(randomCellX_(randomGenerator_));
    IntModN baseCellZ(mapParameters_->numCellsZ, 0);
    baseCellZ.SetValue(randomCellZ_(randomGenerator_));
    int   extent = 2;
    float height = -.5f;
    for (int x = -extent; x <= extent; x++) {
        for (int z = -extent; z <= extent; z++) {
            float normalizedRadius =   (float)(sqrt((float)x*(float)x + (float)z*(float)z))
                                     / (float)extent,
                  cellHeight       = (1.0f - normalizedRadius*normalizedRadius) * height;
            if (cellHeight < 0.0f)
                cellHeight = 0.0f;
            float &targetHeight = Height((baseCellX + x).ToInt(), (baseCellZ + z).ToInt());
            targetHeight = .5f*targetHeight + .5f*cellHeight;
        }
    }
}

float &ZarchTerrain::Height(int cellX, int cellZ) {
    return heights_[cellZ*mapParameters_->numCellsX + cellX];
}


}    // Namespace Zarch.
}    // Namespace kxm.
