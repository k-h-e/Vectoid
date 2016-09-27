#include <kxm/Zarch/LanderGeometry.h>

#include <kxm/Vectoid/Vector.h>

using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

LanderGeometry::LanderGeometry() {
    AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( -.5f, 0.0f,   .5f), Vector( 0.0f, 0.0f,  -1.0f),
                Vector( .8f,  .8f,  .2f));
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector(  .5f, 0.0f,   .5f), Vector( 0.0f,  .35f,  0.0f),
                Vector( .8f,  .8f,  .2f));
    
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector( 0.0f,  .35f,  0.0f), Vector( 0.0f,  .5f, - .8f),
                Vector( .8f,  .5f,  .2f));
    AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 0.0f,  .5f, - .8f), Vector( 0.0f,  .35f,  0.0f),
                Vector( .8f,  .5f,  .2f));
    
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector( 0.0f,  .5f, - .8f), Vector(-1.0f,  .1f,  -1.0f),
                Vector( .5f,  .8f,  .2f));
    AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 1.0f,  .1f, -1.0f), Vector( 0.0f,  .5f, - .8f),
                Vector( .5f,  .8f,  .2f));
    
    AddTriangle(Vector(-.5f, 0.0f,  .5f), Vector(-1.0f,  .1f, -1.0f), Vector( 0.0f, 0.0f,  -1.0f),
                Vector( .2f,  .5f,  .8f));
    AddTriangle(Vector( .5f, 0.0f,  .5f), Vector( 0.0f, 0.0f,  -1.0f), Vector( 1.0f,  .1f, -1.0f),
                Vector( .2f,  .5f,  .8f));
    
    AddTriangle(Vector(0.0f,  .5f, -.8f), Vector( 0.0f, 0.0f,  -1.0f), Vector(-1.0f,  .1f, -1.0f),
                Vector(.8f,   .2f,  .3f));
    AddTriangle(Vector(0.0f,  .5f, -.8f), Vector( 1.0f,  .1f, -1.0f), Vector( 0.0f, 0.0f,  -1.0f),
                Vector(.8f, .2f, .3f));
    
    Move(Vector(0.0f, 0.0f, .35f));
    Scale(.65f);
}

}    // Namespace Zarch.
}    // Namespace kxm.
