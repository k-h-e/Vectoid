//
//  EventPoolInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_GAME_POOLINTERFACE_H_
#define KXM_GAME_POOLINTERFACE_H_

/*!
 *  \defgroup Game Game Engine Infrastructure
 */


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

//! Interface to item pools.
/*!
 *  \ingroup Game
 */
template<class T>
class PoolInterface : public virtual Core::Interface {
  public:
    virtual T &Get(int *id) = 0;
    virtual T &Access(int id) = 0;
    virtual void Put(int id) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_POOLINTERFACE_H_
