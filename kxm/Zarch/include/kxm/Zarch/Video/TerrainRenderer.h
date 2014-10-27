//
//  TerrainRenderer.h
//  kxm
//
//  Created by Kai Hergenroether on 6/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KXM_ZARCH_TERRAINRENDERER_H_
#define KXM_ZARCH_TERRAINRENDERER_H_


#include <vector>
#include <memory>

#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>


namespace Vectoid {
    class RenderContext;
}

namespace kxm {
namespace Zarch {

class Terrain;
class MapParameters;

//! Renders the terrain.
/*!
 *  \ingroup Zarch
 */
class TerrainRenderer : public virtual Vectoid::GeometryInterface {
  public:
    TerrainRenderer(std::shared_ptr<Terrain> terrain,
                    std::shared_ptr<MapParameters> mapParameters);
    
    //! Sets the observer's position in the <c>xz</c>-plane.
    void SetObserverPosition(float x, float z);
    void Render(Vectoid::RenderContext *context);
    
  private:
    TerrainRenderer(const TerrainRenderer &other);
    TerrainRenderer &operator=(const TerrainRenderer &other);
    
    std::shared_ptr<Terrain>             terrain_;
    std::shared_ptr<const MapParameters> mapParameters_;
    float                                observerX_, observerZ_;
    std::vector<GLfloat>                 vertices_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_TERRAINRENDERER_H_

