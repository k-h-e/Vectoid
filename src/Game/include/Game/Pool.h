//
//  Pool.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#ifndef KXM_GAME_POOL_H_
#define KXM_GAME_POOL_H_


#include <kxm/Core/ReusableItems.h>
#include <Game/PoolInterface.h>


namespace kxm {
namespace Game {

//! Pool of items of given type, implemented by a collection of a given item sub type.
/*!
 *  \ingroup Game
 */
template<class ItemType, class SubType>
class Pool : public virtual PoolInterface<ItemType> {
  public:
    Pool() : pool_(1) {}
    ItemType &Get(int *id) { return pool_.Get(0, id); }
    ItemType &Access(int id) { return pool_.Item(id); }
    void Put(int id) { pool_.Put(id); }
    
  private:
    Pool(const Pool &other);
    Pool &operator=(const Pool &other);
  
    Core::ReusableItems<SubType> pool_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_POOL_H_

