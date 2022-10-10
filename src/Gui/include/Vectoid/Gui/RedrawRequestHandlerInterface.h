#ifndef VECTOID_GUI_REDRAWREQUESTHANDLERINTERFACE_H_
#define VECTOID_GUI_REDRAWREQUESTHANDLERINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace Gui {

//! Interface to UI redraw request handlers.
class RedrawRequestHandlerInterface : public virtual K::Core::Interface {
  public:
    //! Informs the handler that a redraw has been requested.
    virtual void onRedrawRequested() = 0;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_REDRAWREQUESTHANDLERINTERFACE_H_
