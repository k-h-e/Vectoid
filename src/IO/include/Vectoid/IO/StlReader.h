#ifndef VECTOID_IO_STLREADER_H_
#define VECTOID_IO_STLREADER_H_

#include <string>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/Core/Vector.h>

namespace K {
    namespace Core {
        class BinaryReaderInterface;
    }
}

namespace Vectoid {
namespace IO {

//! Reads triangles from (binary) STL files.
class StlReader : public virtual Core::TriangleProviderInterface {
  public:
    StlReader(const std::string &fileName);
    StlReader()                                  = delete;
    StlReader(const StlReader &other)            = delete;
    StlReader &operator=(const StlReader &other) = delete;
    StlReader(StlReader &&other)                 = delete;
    StlReader &operator=(StlReader &&other)      = delete;
    ~StlReader()                                 = default;
    
    void PrepareToProvideTriangles() override;
    bool ProvideNextTriangle(Core::ThreePoints *outTriangle) override;
    void ProvideNormal(Core::Vector<float> *outNormal) override;
    bool TriangleError() override;
    
  private:
    void CheckFinished();
    
    std::string                                     fileName_;
    std::shared_ptr<K::Core::BinaryReaderInterface> reader_;                  // Present <=> readout active.
    bool                                            error_;
    uint32_t                                        numTriangles_;            // Valid <=> reader present.
    uint32_t                                        numTrianglesProvided_;    // Valid <=> reader present.
    Core::Vector<float>                             normal_;                  // Valid after successful
                                                                              //     ProvideNextTriangle().
};

}    // Namespace IO.
}    // Namespace Vectoid.

#endif    // VECTOID_IO_STLREADER_H_
