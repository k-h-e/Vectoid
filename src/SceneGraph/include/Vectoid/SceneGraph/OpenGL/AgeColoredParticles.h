#ifndef VECTOID_SCENEGRAPH_OPENGL_AGECOLOREDPARTICLES_H_
#define VECTOID_SCENEGRAPH_OPENGL_AGECOLOREDPARTICLES_H_

#include <Vectoid/SceneGraph/AgeColoredParticles.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Renders particles in different colors, depending of their age.
/*!
 *  \ingroup VectoidOpenGL
 */
class AgeColoredParticles : public Vectoid::SceneGraph::AgeColoredParticles {
 public:
    friend class RenderTarget;

    AgeColoredParticles(const AgeColoredParticles &other) = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    void Render();
    
  private:
    AgeColoredParticles(const std::shared_ptr<Core::Particles> &particles);
  
    std::vector<GLfloat> vertexBuffer_;
    std::vector<GLfloat> colorBuffer_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_AGECOLOREDPARTICLES_H_
