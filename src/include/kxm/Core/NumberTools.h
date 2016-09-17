#ifndef KXM_CORE_NUMBERTOOLS_H_
#define KXM_CORE_NUMBERTOOLS_H_

namespace kxm {
namespace Core {
namespace NumberTools {

static const float piAsFloat = 3.141592654f;

inline void Clamp(int *numba, int min, int max) {
    if (*numba < min)
        *numba = min;
    else if (*numba > max)
        *numba = max;
}

inline void Clamp(float *numba, float min, float max) {
    if (*numba < min)
        *numba = min;
    else if (*numba > max)
        *numba = max;
}

inline void ClampMin(int *numba, int min) {
    if (*numba < min)
        *numba = min;
}

inline void ClampMin(float *numba, float min) {
    if (*numba < min)
        *numba = min;
}

}    // Namespace NumberTools.
}    // Namespace Core.
}    // namespace kxm.

#endif    // KXM_CORE_NUMBERTOOLS_H_
