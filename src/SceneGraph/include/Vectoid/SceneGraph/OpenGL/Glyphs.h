///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_GLYPHS_H_
#define VECTOID_SCENEGRAPH_OPENGL_GLYPHS_H_

#include <optional>
#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Manages textures for text glyphs.
class Glyphs : public SceneGraph::Glyphs {
  public:
    Glyphs()                               = delete;
    Glyphs(const std::shared_ptr<Context> &context);
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    ~Glyphs();
    
    void BindGlyphTexture(uint8_t glyph) override;
    
  private:
    Context *Context() { return static_cast<class Context *>(context_.get()); }
    void GenerateTextures();

    int                    textureSlots_[256];
    std::optional<uint8_t> defaultGlyph_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_OPENGL_GLYPHS_H_
