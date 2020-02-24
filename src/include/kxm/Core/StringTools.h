#ifndef KXM_CORE_STRINGTOOLS_H_
#define KXM_CORE_STRINGTOOLS_H_

#include <string>
#include <vector>

namespace kxm {
namespace Core {

class StringTools {
  public:
    static void Tokenize(const std::string &text, char separator, std::vector<std::string> *outTokens);
    static bool Parse(const std::string &text, int *outValue);
    static bool Parse(const std::string &text, float *outValue);
};

}    // Namespace Core.
}    // namespace kxm.

#endif    // KXM_CORE_STRINGTOOLS_H_
