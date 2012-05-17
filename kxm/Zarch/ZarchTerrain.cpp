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

using std::vector;
using boost::random::uniform_int_distribution;
using kxm::Core::IntModN;
using kxm::Vectoid::RenderContext;


namespace kxm {
namespace Zarch {

ZarchTerrain::ZarchTerrain(int numCellsX, int numCellsZ, float cellSize,
                           int numVisibleCellsX, int numVisibleCellsZ) {
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
    
    numCellsX_        = numCellsX;
    numCellsZ_        = numCellsZ;
    numVisibleCellsX_ = numVisibleCellsX;
    numVisibleCellsZ_ = numVisibleCellsZ;
    cellSize_         = cellSize;
    observerX_        = 0.0f;
    observerZ_        = 0.0f;
    
    heights_.resize(numCellsX * numCellsZ);
    vertices_.resize(2 * 3 * 3);    // Two triangles.
    randomFormation_ = uniform_int_distribution<>(0, (int)NumFormations - 1);
    randomCellX_     = uniform_int_distribution<>(0, numCellsX_ - 1);
    randomCellZ_     = uniform_int_distribution<>(0, numCellsZ_ - 1);
    GenerateTerrain();
}

void ZarchTerrain::SetObserverPosition(float x, float z) {
    observerX_ = x;
    observerZ_ = z;
}

void ZarchTerrain::Render(RenderContext *context) {
    glVertexPointer(3, GL_FLOAT, 0, &vertices_[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    float   baseX = observerX_ + (float)(numCellsX_/2 - numVisibleCellsX_/2) * cellSize_,
            baseZ = observerZ_ + (float)(numCellsZ_/2 - numVisibleCellsZ_/2) * cellSize_;
    int     baseCellX = (int)(baseX / cellSize_),
            baseCellZ = (int)(baseZ / cellSize_);
    float   remainderX = baseX - (float)baseCellX*cellSize_,
            remainderZ = baseZ - (float)baseCellZ*cellSize_;
    if (baseX < 0.0f) {
        --baseCellX;
        remainderX += cellSize_;
    }
    if (baseZ < 0.0f) {
        --baseCellZ;
        remainderZ += cellSize_;
    }
    float   lowX, lowZ, highX, highZ,
            heightLowXLowZ, heightLowXHighZ, heightHighXLowZ, heightHighXHighZ;
    bool    interpolateLowX, interpolateHighX, interpolateLowZ, interpolateHighZ;
    IntModN modCellX = IntModN(numCellsX_, 0) + baseCellX;
    int     cellX    = baseCellX;
    GLfloat *vertexData;
    for (int x = 0; x <= numVisibleCellsX_; x++) {
        lowX             = (float)(cellX - numCellsX_/2) * cellSize_;
        interpolateLowX  = false;
        highX            = lowX + cellSize_;
        interpolateHighX = false;
        if (x == 0) {
            lowX             += remainderX;
            interpolateLowX   = true;
        }
        else if (x == numVisibleCellsX_) {
            highX            -= cellSize_ - remainderX;
            interpolateHighX  = true;
        }
        IntModN modCellZ = IntModN(numCellsZ_, 0) + baseCellZ;
        int     cellZ    = baseCellZ;  
        for (int z = 0; z <= numVisibleCellsZ_; z++) {
            lowZ             = (float)(cellZ - numCellsZ_/2) * cellSize_;
            interpolateLowZ  = false;
            highZ            = lowZ + cellSize_;
            interpolateHighZ = false;
            if (z == 0) {
                lowZ             += remainderZ;
                interpolateLowZ   = true;
            }
            else if (z == numVisibleCellsZ_) {
                highZ            -= cellSize_ - remainderZ;
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
                                                   interpolateHighZ ? remainderZ : cellSize_)
                               : Height(modCellX.ToInt(), (modCellZ + 1).ToInt());
            heightHighXLowZ  =   (interpolateHighX || interpolateLowZ)
                               ? InterpolateHeight(modCellX, modCellZ,
                                                   interpolateHighX ? remainderX : cellSize_,
                                                   interpolateLowZ  ? remainderZ : 0.0f)
                               : Height((modCellX + 1).ToInt(), modCellZ.ToInt());
            heightHighXHighZ =   (interpolateHighX || interpolateHighZ)
                               ? InterpolateHeight(modCellX, modCellZ,
                                                   interpolateHighX ? remainderX : cellSize_,
                                                   interpolateHighZ ? remainderZ : cellSize_)
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
    float s = remainderX / cellSize_,
          t = remainderZ / cellSize_;
    return   (1.0f - t) * (  (1.0f - s) * Height(cellX.ToInt(), cellZ.ToInt())
                           + s          * Height((cellX + 1).ToInt(), cellZ.ToInt()))
           + t          * (  (1.0f - s) * Height(cellX.ToInt(), (cellZ + 1).ToInt())
                           + s          * Height((cellX + 1).ToInt(), (cellZ + 1).ToInt()));
}

void ZarchTerrain::GenerateTerrain() {
    for (int i = 0; i < numCellsX_ * numCellsZ_; i++)
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
    
    for (int i = 0; i < numCellsX_; i++) {
        heights_[i]                               = 1.0f;
        heights_[(numCellsZ_ - 1)*numCellsX_ + i] = 1.0f;
    }
    for (int i = 0; i < numCellsZ_; i++) {
        heights_[i*numCellsX_]                   = 1.0f;
        heights_[i*numCellsX_ + (numCellsX_ -1)] = 1.0f;
    }
}

void ZarchTerrain::GenerateMountainFormation() {
    IntModN baseCellX(numCellsX_, 0);  baseCellX.SetValue(randomCellX_(randomGenerator_));
    IntModN baseCellZ(numCellsZ_, 0);  baseCellZ.SetValue(randomCellZ_(randomGenerator_));
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
    IntModN baseCellX(numCellsX_, 0);  baseCellX.SetValue(randomCellX_(randomGenerator_));
    IntModN baseCellZ(numCellsZ_, 0);  baseCellZ.SetValue(randomCellZ_(randomGenerator_));
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
    return heights_[cellZ*numCellsX_ + cellX];
}


}    // Namespace Zarch.
}    // Namespace kxm.
