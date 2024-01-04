///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_OPENGL_H_
#define VECTOID_SCENEGRAPH_OPENGL_OPENGL_H_

#if defined(K_PLATFORM_MAC)
#include <OpenGL/gl.h>
#elif defined(K_PLATFORM_IOS)
#include <OpenGLES/ES1/gl.h>
#elif defined(K_PLATFORM_LINUX)
#include <gl/gl.h>
#else
#error Unknown platform.
#endif

#endif    // VECTOID_SCENEGRAPH_OPENGL_OPENGL_H_

