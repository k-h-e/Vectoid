//
//  ItemGroups.h
//  kxm
//
//  Created by Kai Hergenröther on 8/13/12.
//
//


#ifndef KXM_CORE_ITEMGROUPS_H_
#define KXM_CORE_ITEMGROUPS_H_


#include <vector>


namespace kxm {
namespace Core {

//! Container organizing its items into groups, between which items can be efficiently moved.
/*!
 *  \ingroup Core
 */
template<class T> class ItemGroups {
    struct GroupInfo;
  public:
    //! Allows for iterating over the items of a given group. Can also be used to move items
    //! between groups.
    /*!
     *  \ingroup Core
     */
    class Iterator {
      public:
        //! Moves the iterator one item forward and returns the new current item if such is present,
        //! otherwise <c>0</c>.
        T *GetNext();
        //! If the iterator is currently pointing to an item, that item gets moved to the specified
        //! target group without invalidating the iterator. Otherwise, nothing happens.
        void MoveTo(int targetGroup);
        //! Same as MoveTo(), but with the idle group set as the target for convenience.
        void MoveToIdle();
      private:
        friend class ItemGroups;
        ItemGroups *itemGroups_;
        int        anchor_,
                   next_,
                   current_,
                   group_;
        Iterator(ItemGroups *itemGroups, int group);
    };
    
    ItemGroups();
    //! Adds a new empty item group and returns its id.
    int AddGroup();
    //! Adds a new item to the specified group and grants access to it. The item is taken from the
    //! idle pool (group), or, if the idle pool is currently empty, an all new item is created.
    T *AddItem(int group);
    //! Tells the number of items in the specified group.
    int Count(int group);
    //! Gets an iterator for the specified group. The iterator also allows for moving items between
    //! groups.
    /*! 
     *  The ItemGroups container object must be kept alive by the client context for as long as the
     *  iterator is used.
     */
    Iterator GetIterator(int group);
    
  private:
    struct GroupInfo {
        int anchor,    // Id of the group's anchor item.
            count;     // Number of items in the group.
        
        GroupInfo(int anAnchor) {
            anchor = anAnchor;
            count  = 0;
        }
    };
    
    struct ItemInfo {
        int prev, next;
        T   item;
        
        ItemInfo(int prevId, int nextId) {
            prev = prevId;
            next = nextId;
        }
    };
    
    std::vector<ItemInfo>  items_;
    std::vector<GroupInfo> groups_;
    int                    idleGroup_,
                           idleGroupAnchor_;
    
    //! Creates an all new idle item and returns its id.
    int CreateIdleItem();
    //! Efficiently moves the specified item from its current group to the group implicitly given by
    //! the specified target group anchor. Both group's item counts are <b>not</b> updated - this
    //! must be done by the calling context.
    void MoveItem(int item, int targetGroupAnchor);
    
    // Can get copied and assigned.
};

template<class T>
ItemGroups<T>::ItemGroups() {
    idleGroup_ = AddGroup();
    idleGroupAnchor_ = groups_[idleGroup_].anchor;
}

template<class T>
int ItemGroups<T>::AddGroup() {
    int newItem = items_.size();
    ItemInfo newItemInfo(newItem, newItem);
    items_.push_back(newItemInfo);
    
    int newGroup = groups_.size();
    GroupInfo newGroupInfo(newItem);
    groups_.push_back(newGroupInfo);
    
    return newGroup;
}

template<class T>
T *ItemGroups<T>::AddItem(int targetGroup) {
    int idleItem = items_[idleGroupAnchor_].next;
    if (idleItem == idleGroupAnchor_)
        idleItem = CreateIdleItem();
    GroupInfo &targetGroupInfo = groups_[targetGroup];
    MoveItem(idleItem, targetGroupInfo.anchor);
    --groups_[idleGroup_].count;
    ++targetGroupInfo.count;
    return &items_[idleItem].item;
}

template<class T>
int ItemGroups<T>::Count(int group) {
    return groups_[group].count;
}

template<class T>
typename ItemGroups<T>::Iterator ItemGroups<T>::GetIterator(int group) {
    return Iterator(this, group);
}

template<class T>
int ItemGroups<T>::CreateIdleItem() {
    int newItem = items_.size();
    ItemInfo &anchorInfo     = items_[idleGroupAnchor_],
             &anchorPredInfo = items_[anchorInfo.prev],
             newItemInfo(anchorInfo.prev, idleGroupAnchor_);
    anchorPredInfo.next = newItem;
    anchorInfo.prev     = newItem;
    items_.push_back(newItemInfo);
    ++groups_[idleGroup_].count;
    return newItem;
}

template<class T>
void ItemGroups<T>::MoveItem(int item, int targetGroupAnchor) {
    // Unlink from current group...
    ItemInfo &info     = items_[item],
             &prevInfo = items_[info.prev],
             &nextInfo = items_[info.next];
    prevInfo.next = info.next;
    nextInfo.prev = info.prev;
    // Link into target group...
    ItemInfo &anchorInfo     = items_[targetGroupAnchor],
             &anchorPredInfo = items_[anchorInfo.prev];
    anchorPredInfo.next = item;
    info.prev           = anchorInfo.prev;
    info.next           = targetGroupAnchor;
    anchorInfo.prev     = item;
}

template<class T>
ItemGroups<T>::Iterator::Iterator(ItemGroups *itemGroups, int group)
    : itemGroups_(itemGroups),
      anchor_(itemGroups->groups_[group].anchor),
      next_(itemGroups->items_[anchor_].next),
      current_(-1),
      group_(group) {
}

template<class T>
T *ItemGroups<T>::Iterator::GetNext() {
    if (next_ != anchor_) {
        ItemInfo &currentInfo = itemGroups_->items_[next_];
        current_ = next_;
        next_    = currentInfo.next;
        return &currentInfo.item;
    }
    else {
        current_ = -1;
        return 0;
    }
}

template<class T>
void ItemGroups<T>::Iterator::MoveTo(int targetGroup) {
    if (current_ != -1) {
        GroupInfo &targetGroupInfo = itemGroups_->groups_[targetGroup];
        itemGroups_->MoveItem(current_, targetGroupInfo.anchor);
        --itemGroups_->groups_[group_].count;
        ++targetGroupInfo.count;
        current_ = -1;
    }
}

template<class T>
void ItemGroups<T>::Iterator::MoveToIdle() {
    MoveTo(itemGroups_->idleGroup_);
}

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_ITEMGROUPS_H_

