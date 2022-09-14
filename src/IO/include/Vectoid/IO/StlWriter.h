#ifndef VECTOID_IO_STLWRITER_H_
#define VECTOID_IO_STLWRITER_H_

#include <string>

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
     *  \return <c>true</c> in case of success. Otherwise, the state of the written file is undefined.
     */
    static bool Write(Core::TriangleProviderInterface *triangleProvider, const std::string &fileName);
};

}    // Namespace IO.
}    // Namespace Vectoid.

#endif    // VECTOID_IO_STLWRITER_H_
