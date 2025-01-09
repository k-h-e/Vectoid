///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_IO_STLWRITER_H_
#define VECTOID_IO_STLWRITER_H_

namespace K {
    namespace Core {
        class SeekableBlockingOutStreamInterface;
    }
    namespace IO {
        class Path;
    }
}
namespace Vectoid {
    namespace Core {
        class TriangleProviderInterface;
    }
}

namespace Vectoid {
namespace IO {

//! Writes (binary) STL files.
class StlWriter {
  public:
    //! Writes triangles to a binary STL file.
    /*!
     *  \return <c>true</c> in case of success. Otherwise, the state of the output stream is undefined.
     */
    static bool Write(Core::TriangleProviderInterface &triangleProvider,
                      K::Core::SeekableBlockingOutStreamInterface &outStream);
    //! Writes triangles to a binary STL file.
    /*!
     *  \return <c>true</c> in case of success. Otherwise, the state of the written file is undefined.
     */
    static bool Write(Core::TriangleProviderInterface &triangleProvider, const K::IO::Path &fileName);
};

}    // Namespace IO.
}    // Namespace Vectoid.

#endif    // VECTOID_IO_STLWRITER_H_
