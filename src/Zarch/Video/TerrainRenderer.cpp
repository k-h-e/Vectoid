//
//  TerrainRenderer.cpp
//  kxm
//
//  Created by Kai Hergenroether on 6/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <Zarch/Video/TerrainRenderer.h>

#include <kxm/Core/IntModN.h>
#include <Zarch/Terrain.h>
#include <Zarch/MapParameters.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {
namespace Video {

TerrainRenderer::TerrainRenderer(shared_ptr<Terrain> terrain,
                                 shared_ptr<MapParameters> mapParameters)
        : terrain_(terrain),
          mapParameters_(mapParameters),
          observerX_(0.0f),
          observerZ_(0.0f) {
    vertices_.resize(2 * 3 * 3);    // Two triangles.
}

void TerrainRenderer::SetObserverPosition(float x, float z) {
    observerX_ = x;
    observerZ_ = z;
}

void TerrainRenderer::Render(RenderContext *context) {
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
    Vector  cellColor;
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
                               ? terrain_->InterpolateHeight(
                                     modCellX, modCellZ,
                                     interpolateLowX  ? remainderX : 0.0f,
                                     interpolateLowZ  ? remainderZ : 0.0f)
                               : terrain_->CellHeight(modCellX.ToInt(), modCellZ.ToInt());
            heightLowXHighZ  =   (interpolateLowX || interpolateHighZ)
                               ? terrain_->InterpolateHeight(
                                     modCellX, modCellZ,
                                     interpolateLowX  ? remainderX : 0.0f,
                                     interpolateHighZ ? remainderZ : mapParameters_->cellSize)
                               : terrain_->CellHeight(modCellX.ToInt(), (modCellZ + 1).ToInt());
            heightHighXLowZ  =   (interpolateHighX || interpolateLowZ)
                               ? terrain_->InterpolateHeight(
                                     modCellX, modCellZ,
                                     interpolateHighX ? remainderX : mapParameters_->cellSize,
                                     interpolateLowZ  ? remainderZ : 0.0f)
                               : terrain_->CellHeight((modCellX + 1).ToInt(), modCellZ.ToInt());
            heightHighXHighZ =   (interpolateHighX || interpolateHighZ)
                               ? terrain_->InterpolateHeight(modCellX, modCellZ,
                                     interpolateHighX ? remainderX : mapParameters_->cellSize,
                                     interpolateHighZ ? remainderZ : mapParameters_->cellSize)
                               : terrain_->CellHeight((modCellX + 1).ToInt(),
                                                      (modCellZ + 1).ToInt());
            
            vertexData = &vertices_[0];
            *vertexData++ = lowX;   *vertexData++ = heightLowXLowZ;    *vertexData++ = lowZ;
            *vertexData++ = lowX;   *vertexData++ = heightLowXHighZ;   *vertexData++ = highZ;
            *vertexData++ = highX;  *vertexData++ = heightHighXLowZ;   *vertexData++ = lowZ;

            *vertexData++ = highX;  *vertexData++ = heightHighXLowZ;   *vertexData++ = lowZ;
            *vertexData++ = lowX;   *vertexData++ = heightLowXHighZ;   *vertexData++ = highZ;
            *vertexData++ = highX;  *vertexData++ = heightHighXHighZ;  *vertexData++ = highZ;
            
            cellColor = terrain_->CellColor(modCellX.ToInt(), modCellZ.ToInt());
            glColor4f(cellColor.x, cellColor.y, cellColor.z, 1.0f);
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


}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
