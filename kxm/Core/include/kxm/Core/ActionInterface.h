//
//  ActionInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_CORE_ACTIONINTERFACE_H_
#define KXM_CORE_ACTIONINTERFACE_H_


namespace kxm {
namespace Core {

//! Interface to actions that can be executed.
/*!
 *  \ingroup Core
 */
class ActionInterface : public virtual Interface {
  public:
    //! Executes the action.
    virtual void ExecuteAction() = 0;
};

}
}


#endif    // KXM_CORE_ACTIONINTERFACE_H_

