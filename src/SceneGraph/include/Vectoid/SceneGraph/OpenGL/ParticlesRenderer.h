///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_PARTICLESRENDERER_H_
#define VECTOID_SCENEGRAPH_OPENGL_PARTICLESRENDERER_H_

#include <Vectoid/SceneGraph/ParticlesRenderer.h>

#include <vector>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders particles.
class ParticlesRenderer : public Vectoid::SceneGraph::ParticlesRenderer {
  public:
    ParticlesRenderer()                                          = delete;
    ParticlesRenderer(const std::shared_ptr<Context> &context,
                      const std::shared_ptr<Core::Particles> &particles);
    ParticlesRenderer(const ParticlesRenderer &other)            = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    ParticlesRenderer(ParticlesRenderer &&other)                 = delete;
    ParticlesRenderer &operator=(ParticlesRenderer &&other)      = delete;

    void Render() override;
    
  private:
    std::vector<GLfloat> vertexBuffer_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_PARTICLESRENDERER_H_
