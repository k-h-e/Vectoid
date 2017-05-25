#ifndef KXM_CORE_INTERFACE_H_
#define KXM_CORE_INTERFACE_H_

/*!
 *  \defgroup Core Core
 *  \brief Platform core classes.
 *
 *
 */

namespace kxm {
namespace Core {

//! Base class to all hierarchy classes, basically providing the virtual destructor to allow for polymorphic object
//! deletion.
/*!
 *  \ingroup Core
 */
class Interface {
  public:
    virtual ~Interface();
};

}    // Namespace Core.
}    // Namespace kxm.

#endif    // KXM_CORE_INTERFACE_H_
