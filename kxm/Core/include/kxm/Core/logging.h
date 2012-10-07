//
//  logging.h
//  kxm
//
//  Created by Kai Hergenröther on 10/7/12.
//
//


#ifndef KXM_CORE_LOGGING_
#define KXM_CORE_LOGGING_


#include <ostream>


namespace kxm {
namespace Core {

class LoggerHandle {
  public:
    LoggerHandle();
    LoggerHandle(std::ostream *stream);
    LoggerHandle(const LoggerHandle &other);
    ~LoggerHandle();
    LoggerHandle &operator=(const LoggerHandle &other);
    
    //! Grants access to the logging stream. This stream may only be accessed while the LoggerHandle
    //! lives! Otherwise you will screw up potentially active thread synchronization!
    std::ostream &Stream();
    
  private:
    std::ostream *stream_;
    bool         haveToUnlock_;
};

//! Returns a handle for the appropriate logging <c>ostream</c>.
LoggerHandle Log(void *origin);
//! Returns a handle for the appropriate logging <c>ostream</c>.
LoggerHandle Log();

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_LOGGING_

