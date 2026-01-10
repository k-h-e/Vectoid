///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_IO_STLREADER_H_
#define VECTOID_IO_STLREADER_H_

#include <K/IO/Path.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/Core/Vector.h>

namespace K {
    namespace Core {
        class SeekableBlockingInStreamInterface;
    }
}

namespace Vectoid {
//! I/O for 3D data.
namespace IO {

//! Reads triangles from (binary) STL files.
class StlReader : public virtual Core::TriangleProviderInterface {
  public:
    //! Constructs a reader for the specified STL file.
    StlReader(const K::IO::Path &fileName);
    //! Constructs a reader for the STL file content embedded as the specified subregion in the specified file.
    StlReader(const K::IO::Path &fileName, uint64_t offset, uint64_t size);
    StlReader()                                  = delete;
    StlReader(const StlReader &other)            = delete;
    StlReader &operator=(const StlReader &other) = delete;
    StlReader(StlReader &&other)                 = delete;
    StlReader &operator=(StlReader &&other)      = delete;
    ~StlReader()                                 = default;
    
    // TriangleProviderInterface...
    void PrepareToProvideTriangles() override;
    bool ProvideNextTriangle(Core::ThreePoints &outTriangle) override;
    void ProvideNormal(Core::Vector<float> &outNormal) override;
    bool TriangleError() override;
    
  private:
    void CheckFinished();
    
    K::IO::Path                                                 fileName_;
    bool                                                        useSubFile_;
    uint64_t                                                    subFileOffset_;    // Unchecked, validated by SubStream.
    uint64_t                                                    subFileSize_;      // Unchecked, validated by SubStream.
    std::shared_ptr<K::Core::SeekableBlockingInStreamInterface> fileStream_;              // Present <=> readout active.
    bool                                                        error_;
    uint32_t                                                    numTriangles_;            // Valid <=> reader present.
    uint32_t                                                    numTrianglesProvided_;    // Valid <=> reader present.
    Core::Vector<float>                                         normal_;                  // Valid after successful
                                                                                          //     ProvideNextTriangle().
};

}    // Namespace IO.
}    // Namespace Vectoid.

#endif    // VECTOID_IO_STLREADER_H_
