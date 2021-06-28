#ifndef VECTOID_CORE_TOOLS_H_
#define VECTOID_CORE_TOOLS_H_

namespace Vectoid {
namespace Core {

//! Various tool functions.
class Tools {
  public:
    //! Returns the index in <c>[0, 2]</c> according to modulo 3. Use only with input close to <c>[0, 2]</c>.
    inline static int IndexMod3(int index) {
        while (index < 0) {
            index += 3;
        }
        while (index >= 3) {
            index -= 3;
        }
        return index;
    }
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_TOOLS_H_
