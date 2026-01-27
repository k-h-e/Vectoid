///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_GLYPHS_H_
#define VECTOID_SCENEGRAPH_GLYPHS_H_

#include <stdint.h>

#include <Vectoid/SceneGraph/Node.h>

namespace Vectoid {
namespace SceneGraph {

//! Manages textures for text glyphs.
class Glyphs : public Node {
  public:
    Glyphs()                               = delete;
    Glyphs(const Glyphs &other)            = delete;
    Glyphs &operator=(const Glyphs &other) = delete;
    Glyphs(Glyphs &&other)                 = delete;
    Glyphs &operator=(Glyphs &&other)      = delete;
    
    //! Binds the texture for the specified glyph, if present.
    /*!
     *  Interacts with the underlying graphics system.
     */
    virtual void BindGlyphTexture(uint8_t glyph) = 0;
    
  protected:
    static constexpr int numGlyphs   { 79 };
    static constexpr int glyphWidth  { 19 };
    static constexpr int glyphHeight { 34 };

    static const uint8_t glyphData[];
    static const uint8_t glyphCodes[];

    Glyphs(const std::shared_ptr<Context> &context);
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_GLYPHS_H_
