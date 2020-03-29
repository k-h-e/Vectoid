#ifndef KXM_CORE_NUMBERTOOLS_H_
#define KXM_CORE_NUMBERTOOLS_H_

namespace kxm {
namespace Core {

class NumberTools {
  public:
    static const double pi;

    static void Clamp(int *numba, int min, int max);
    static void Clamp(float *numba, float min, float max);
    static void ClampMin(int *numba, int min);
    static void ClampMax(int *numba, int max);
    static void ClampMin(float *numba, float min);
    static void ClampMax(float *numba, float max);
};

}    // Namespace Core.
}    // namespace kxm.

#endif    // KXM_CORE_NUMBERTOOLS_H_
