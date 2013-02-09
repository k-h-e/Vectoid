//
//  ReusableItems.h
//  kxm
//
//  Created by Kai Hergenröther on 2/8/13.
//
//


#ifndef KXM_CORE_REUSABLEITEMS_H_
#define KXM_CORE_REUSABLEITEMS_H_


#include <vector>


namespace kxm {
namespace Core {

//! Pool-like item container, keeping track of which items are currently in use and which are idle
//! (= waiting to be re-used), and providing efficient means of moving items between those two
//! states.
/*!
 *  \ingroup Core
 *
 *  The template parameter type <code>T</code> must be copyable and default-constructible. 
 *
 *  There's no support for multithreaded use. Specifically, the items might get stored in a compact
 *  way without spacer fields.
 */
template<class T>
class ReusableItems {
  public:
    class Iterator;
    
    ReusableItems();
    //! Provides another item for the client to use, either by taking one from the set of idle
    //! items, or by creating a new one if no idle item is currently present.
    /*!
     *  The item remains owned by the container. With respect to iterations of the in-use items, the
     *  new items gets appended at the end.
     *
     *  When the client has finished using the item, it must put it back into the pool of idle items
     *  for future re-use using \ref Put().
     */
    T &Get();
    //! Same as \ref Get(), but also provides the id of the item returned.
    T &Get(int *id);
    //! Puts back the specified item into the idle pool for future re-use.
    /*!
     *  The item \ref Put() back last will be the first item that \ref Get() returns to use.
     */
    void Put(int id);
    //! Returns an iterator allowing to iterate over the items currently in use.
    /*!
     *  The iterator may only be used as long as the container lives. Unless noted otherwise, 
     *  operations on the container invalidate handed-out iterators.
     */
    Iterator GetIterator();
    //! Grants access to the specified item.
    T &Item(int id);
    //! Tells how many items are currently in use.
    int Count();
    
  private:
    struct ItemInfo {
        int      prev, next;
        T        item;
    };
    ReusableItems(const ReusableItems &other);
    ReusableItems &operator=(const ReusableItems &other);
    void AddIdleItem();
    
    std::vector<ItemInfo> items_;
    int                   inUseAnchor_, idleAnchor_;
    int                   idleCount_;
};

//! Allows for iterating over the items currently in use.
/*!
 *  \ingroup Core
 */
template<class T>
class ReusableItems<T>::Iterator {
  public:
    //! Returns the next item, or <code>0</code> in case there are no more items.
    T *Next();
    //! If the iterator has returned an item in the last call to \ref Next(), this item's id is
    //! returned. Otherwise, the method's behavior is undefined.
    /*!
     *  The current item can be \ref Put() back using the returned id without invalidating the
     *  iterator.
     */
    int ItemId();
    
  private:
    friend class ReusableItems;
    Iterator(std::vector<ItemInfo> &items, int inUseAnchor);
    std::vector<ItemInfo> &items_;
    int                    currentItem_, nextItem_,
                           inUseAnchor_;
};

template<class T>
ReusableItems<T>::ReusableItems()
        : idleCount_(0) {
    ItemInfo info;
    inUseAnchor_ = (int)items_.size();
    info.prev = inUseAnchor_;
    info.next = inUseAnchor_;
    items_.push_back(info);
    idleAnchor_ = (int)items_.size();
    info.prev = idleAnchor_;
    info.next = idleAnchor_;
    items_.push_back(info);
}

template<class T>
T &ReusableItems<T>::Get(int *id) {
    if (!idleCount_)
        AddIdleItem();
    
    ItemInfo &idleAnchorInfo   = items_[idleAnchor_];
    int       item             = idleAnchorInfo.next;
    ItemInfo &itemInfo         = items_[item];
    int       nextIdleItem     = itemInfo.next;
    idleAnchorInfo.next        = nextIdleItem;
    items_[nextIdleItem].prev  = idleAnchor_;
    
    ItemInfo &inUseAnchorInfo  = items_[inUseAnchor_];
    int       lastInUseItem    = inUseAnchorInfo.prev;
    items_[lastInUseItem].next = item;
    itemInfo.prev              = lastInUseItem;
    itemInfo.next              = inUseAnchor_;
    inUseAnchorInfo.prev       = item;
    
    --idleCount_;
    *id = item;
    return itemInfo.item;
}

template<class T>
T &ReusableItems<T>::Get() {
    int id;
    return Get(&id);
}

template<class T>
void ReusableItems<T>::Put(int id) {
    ItemInfo &itemInfo = items_[id];
    items_[itemInfo.prev].next = itemInfo.next;
    items_[itemInfo.next].prev = itemInfo.prev;
    
    ItemInfo &idleAnchorInfo   = items_[idleAnchor_];
    int firstIdleItem          = idleAnchorInfo.next;
    idleAnchorInfo.next        = id;
    itemInfo.prev              = idleAnchor_;
    itemInfo.next              = firstIdleItem;
    items_[firstIdleItem].prev = id;
    
    ++idleCount_;
}

template<class T>
typename ReusableItems<T>::Iterator ReusableItems<T>::GetIterator() {
    return Iterator(items_, inUseAnchor_);
}

template<class T>
T &ReusableItems<T>::Item(int id) {
    return items_[id].item;
}

template<class T>
int ReusableItems<T>::Count() {
    return (int)items_.size() - 2 - idleCount_;
}

template<class T>
void ReusableItems<T>::AddIdleItem() {
    ItemInfo &idleAnchorInfo = items_[idleAnchor_],
             newItemInfo;
    int newItem       = (int)items_.size(),
        firstIdleItem = idleAnchorInfo.next;
    
    idleAnchorInfo.next        = newItem;
    newItemInfo.prev           = idleAnchor_;
    newItemInfo.next           = firstIdleItem;
    items_[firstIdleItem].prev = newItem;
    
    items_.push_back(newItemInfo);
    ++idleCount_;
}

template<class T>
ReusableItems<T>::Iterator::Iterator(std::vector<ItemInfo> &items, int inUseAnchor)
        : items_(items),
          inUseAnchor_(inUseAnchor),
          currentItem_(-1) {
    nextItem_ = items_[inUseAnchor_].next;
}

template<class T>
T *ReusableItems<T>::Iterator::Next() {
    if (nextItem_ == inUseAnchor_)
        return 0;
    currentItem_              = nextItem_;
    ItemInfo &currentItemInfo = items_[currentItem_];
    nextItem_                 = currentItemInfo.next;
    return &currentItemInfo.item;
}

template<class T>
int ReusableItems<T>::Iterator::ItemId() {
    assert(currentItem_ != -1);
    return currentItem_;
}

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_REUSABLEITEMS_H_

