///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_AGECOLOREDPARTICLES_H_
#define VECTOID_SCENEGRAPH_OPENGL_AGECOLOREDPARTICLES_H_

#include <Vectoid/SceneGraph/AgeColoredParticles.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders particles in different colors, depending of their age.
class AgeColoredParticles : public Vectoid::SceneGraph::AgeColoredParticles {
 public:
    AgeColoredParticles()                                            = delete;
    AgeColoredParticles(const std::shared_ptr<Context> &context, const std::shared_ptr<Core::Particles> &particles);
    AgeColoredParticles(const AgeColoredParticles &other)            = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    AgeColoredParticles(AgeColoredParticles &&other)                 = delete;
    AgeColoredParticles &operator=(AgeColoredParticles &&other)      = delete;

    void Render() override;
    
  private:
    std::vector<GLfloat> vertexBuffer_;
    std::vector<GLfloat> colorBuffer_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_AGECOLOREDPARTICLES_H_
