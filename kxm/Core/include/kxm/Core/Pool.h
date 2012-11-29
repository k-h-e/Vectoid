//
//  Pool.h
//  kxm
//
//  Created by Kai Hergenröther on 11/28/12.
//
//


#ifndef KXM_CORE_POOL_H_
#define KXM_CORE_POOL_H_


#include <vector>
#include <deque>


namespace kxm {
namespace Core {

//! Pool of objects of homogeneous type.
/*!
 *  \ingroup Core
 *
 *  The pool owns the objects at all times, both idle ones as those handed out to clients.
 *
 *  In contrast to \ref CompactPool, each object gets individually <c>new</c>ed.
 */
template<class T>
class Pool {
  public:
    Pool();
    ~Pool();
    //! Gets another object for the client to use - if none is currently idle, a new one gets
    //! transparently created.
    /*!
     *  Note that as the pool retains ownership over the object, the handed out pointer is a weak
     *  reference. Furthermore, the handed out object must not be accessed after the pool has been
     *  destroyed.
     *
     *  When the client is done using the object, it must "return" the object to the pool via Put()
     *  to allow re-use. The client must no longer access the object after Put() ing it back.
     */
    T *Get();
    //! Used by clients to "put back" objects previously obtained via Get() when they are done using
    //! those objects.
    void Put(T *object);
    //! Tells the number of pool-owned objects, being the total of both idle ones and those
    //! currently handed out to clients.
    int Count();
    //! Tells the number of free objects currently in the pool.
    int FreeCount();
    
  private:
    Pool(const Pool &other);
    Pool &operator=(const Pool &other);
    
    std::vector<T *> objects_;
    std::deque<T *>  free_;
};


template<class T>
Pool<T>::Pool() {
}

template<class T>
Pool<T>::~Pool() {
    for (typename std::vector<T *>::iterator iter = objects_.begin(); iter != objects_.end();
         ++iter)
        delete *iter;
}

template<class T>
T *Pool<T>::Get() {
    if (free_.size()) {
        T *result = free_.front();
        free_.pop_front();
        return result;
    }
    else {
        T *newObject = new T();
        objects_.push_back(newObject);
        return newObject;
    }
}

template<class T>
void Pool<T>::Put(T *object) {
     free_.push_back(object);
}

template<class T>
int Pool<T>::Count() {
    return (int)objects_.size();
}

template<class T>
int Pool<T>::FreeCount() {
    return (int)free_.size();
}

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_POOL_H_
