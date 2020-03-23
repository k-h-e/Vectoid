#ifndef KXM_VECTOID_TRIANGLEPROVIDERINTERFACE_H_
#define KXM_VECTOID_TRIANGLEPROVIDERINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Vectoid {

class Vector;
class ThreePoints;

//! Interface to entities iteratively providing triangles.
/*!
 *  \ingroup Vectoid
 */
class TriangleProviderInterface : public virtual kxm::Core::Interface {
  public:
    //! Tells the provider to (re)start providing triangles from the beginning.
    virtual void PrepareToProvideTriangles() = 0;
    //! Provides the next triangle vertex data.
    /*!
     *  \return
     *  <c>false</c> in case there are no more triangles. The output parameter is then undefined, and
     *  <c>TriangleError()</c> should be checked.
     */
    virtual bool ProvideNextTriangle(ThreePoints *outTriangle) = 0;
    //! Provides the normal for the current triangle if normals are supported by the provider, and <c>(0, 1, 0)</c>
    //! otherwise.
    virtual void ProvideNormal(Vector *outNormal) = 0;
    //! Tells whether or not the last triangle readout ended because of an error.
    virtual bool TriangleError() = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_TRIANGLEPROVIDERINTERFACE_H_
