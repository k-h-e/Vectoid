//
//  CompactPool.h
//  kxm
//
//  Created by Kai Hergenröther on 11/28/12.
//
//


#ifndef KXM_CORE_COMPACTPOOL_H_
#define KXM_CORE_COMPACTPOOL_H_


#include <vector>
#include <deque>

#include <kxm/Core/logging.h>


namespace kxm {
namespace Core {

//! Pool of objects of homogeneous type.
/*!
 *  \ingroup Core
 *
 *  The pool owns the objects at all times, both idle ones as those handed out to clients.
 *
 *  In contrast to \ref Pool, objects get allocated adjacently to each other, which might cause
 *  adjacent-field-overwrite problems when adjacent objects get accessed from different threads.
 */
template<class T>
class CompactPool {
  public:
    CompactPool();
    //! Pool items get allocted in blocks, the size of which increases whenever new items are
    //! allocated. Here you can specify the initial block size, in items.
    CompactPool(int minBlockSize);
    //! Pool items get allocted in blocks, the size of which increases whenever new items are
    //! allocated. Here you can specify both initial and maximum blocksize, in items.
    CompactPool(int minBlockSize, int maxBlockSize);
    ~CompactPool();
    //! Gets another object for the client to use - if none is currently idle, a new one gets
    //! transparently created.
    /*!
     *  Note that as the pool retains ownership over the object, the handed out pointer is a weak
     *  reference. Furthermore, the handed-out object must not be accessed after the pool has been
     *  destroyed.
     *
     *  When the client is done using the object, it must "return" the object to the pool via Put()
     *  to allow re-use. The client must no longer access the object after Put()ing it back.
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
    CompactPool(const CompactPool &other);
    CompactPool &operator=(const CompactPool &other);
    
    std::vector<T *> objectBlocks_;
    std::deque<T *>  free_;
    int              numObjects_,
                     blockSize_,
                     maxBlockSize_;
};

template<class T>
CompactPool<T>::CompactPool()
        : numObjects_(0),
          blockSize_(16),
          maxBlockSize_(-1) {
}

template<class T>
CompactPool<T>::CompactPool(int minBlockSize)
        : numObjects_(0),
          maxBlockSize_(-1) {
    if (minBlockSize < 1)
        minBlockSize = 1;
    blockSize_ = minBlockSize;
}

template<class T>
CompactPool<T>::CompactPool(int minBlockSize, int maxBlockSize)
        : numObjects_(0) {
    if (minBlockSize < 1)
        minBlockSize = 1;
    if (maxBlockSize < minBlockSize)
        maxBlockSize = minBlockSize;
    blockSize_    = minBlockSize;
    maxBlockSize_ = maxBlockSize;
}

template<class T>
CompactPool<T>::~CompactPool() {
    for (typename std::vector<T *>::iterator iter = objectBlocks_.begin();
         iter != objectBlocks_.end(); ++iter)
        delete[] *iter;
}

template<class T>
T *CompactPool<T>::Get() {
    if (!free_.size()) {
        T *newBlock = new T[blockSize_];
        objectBlocks_.push_back(newBlock);
        numObjects_ += blockSize_;
        for (int i = 0; i < blockSize_; ++i)
            free_.push_back(&newBlock[i]);
        
        int maxSize = (maxBlockSize_ > 0) ? maxBlockSize_ : INT_MAX;
        blockSize_ *= 2;
        if ((blockSize_ > maxSize) || (blockSize_ <= 0))
            blockSize_ = maxSize;
    }
    
    T *result = free_.front();
    free_.pop_front();
    
    //Log(this).Stream() << "Get() : " << Count() << " items in pool, active="
    //                   << Count() - FreeCount() << std::endl;
    return result;
}

template<class T>
void CompactPool<T>::Put(T *object) {
    free_.push_back(object);
    //Log(this).Stream() << "Put() : " << Count() << " items in pool, active="
    //                   << Count() - FreeCount() << std::endl;
}

template<class T>
int CompactPool<T>::Count() {
    return numObjects_;
}

template<class T>
int CompactPool<T>::FreeCount() {
    return (int)free_.size();
}

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_COMPACTPOOL_H_
