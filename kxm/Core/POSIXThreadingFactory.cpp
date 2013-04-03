//
//  POSIXThreadingFactory.cpp
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#include <kxm/Core/POSIXThreadingFactory.h>

#include <pthread.h>
#include <assert.h>

#include <kxm/Core/terminal.h>
#include <kxm/Core/LockInterface.h>
#include <kxm/Core/ConditionVariableInterface.h>
#include <kxm/Core/ThreadControlInterface.h>
#include <kxm/Core/ActionInterface.h>


namespace kxm {
namespace Core {

class POSIXThreadingFactory::POSIXLock : public virtual LockInterface {
  public:
    friend class POSIXThreadingFactory;
    ~POSIXLock();
    void Lock();
    void Unlock();

  private:
    POSIXLock();
    POSIXLock(const POSIXLock &other);
    POSIXLock &operator=(const POSIXLock &other);
    pthread_mutex_t mutex_;
};

class POSIXThreadingFactory::ConditionVariable : public virtual ConditionVariableInterface {
  public:
    friend class POSIXThreadingFactory;
    ~ConditionVariable();
    void Wait();
    void SignalAll();

  private:
    ConditionVariable(pthread_mutex_t *associatedMutex);
    ConditionVariable(const ConditionVariable &other);
    ConditionVariable &operator=(const ConditionVariable &other);
    pthread_cond_t   conditionVariable_;
    pthread_mutex_t *associatedMutex_;
};

class POSIXThreadingFactory::ThreadControl : public virtual ThreadControlInterface {
  public:
    friend class POSIXThreadingFactory;
    void Spawn(ActionInterface *action);
    void Join();
    
  private:
    ThreadControl();
    ThreadControl(const ThreadControl &other);
    ThreadControl &operator=(const ThreadControl &other);
    static void *SpawnerRoutine(void *castActionPtr);
    pthread_t                    thread_;    // Valid iff spawned and not yet joined.
    bool                         spawned_, joined_;
};

LockInterface *POSIXThreadingFactory::CreateLock() const {
    return new POSIXLock();
}

ConditionVariableInterface *POSIXThreadingFactory::CreateConditionVariable(
        LockInterface *associatedLock) const {
    POSIXLock *lock = dynamic_cast<POSIXLock *>(associatedLock);
        // Can't do static cast via virtual base interface. Okay, because not time-critical.
    assert(lock);
    return new ConditionVariable(&lock->mutex_);
}

ThreadControlInterface *POSIXThreadingFactory::CreateThread() const {
    return new ThreadControl();
}

POSIXThreadingFactory::POSIXLock::POSIXLock() {
    if (pthread_mutex_init(&mutex_, 0))
        HandleTerminalCondition("failed to initialize POSIX mutex!");
}

POSIXThreadingFactory::POSIXLock::~POSIXLock() {
    if (pthread_mutex_destroy(&mutex_))
        HandleTerminalCondition("failed to release POSIX mutex!");
}

void POSIXThreadingFactory::POSIXLock::Lock() {
    if (pthread_mutex_lock(&mutex_))
        HandleTerminalCondition("failed to lock POSIX mutex!");
}

void POSIXThreadingFactory::POSIXLock::Unlock() {
    if (pthread_mutex_unlock(&mutex_))
        HandleTerminalCondition("failed to unlock POSIX mutex!");
}

POSIXThreadingFactory::ConditionVariable::ConditionVariable(pthread_mutex_t *associatedMutex)
        : associatedMutex_(associatedMutex) {
    if (pthread_cond_init(&conditionVariable_, 0))
        HandleTerminalCondition("failed to initialize POSIX condition variable!");
}

POSIXThreadingFactory::ConditionVariable::~ConditionVariable() {
    if (pthread_cond_destroy(&conditionVariable_))
        HandleTerminalCondition("failed to release POSIX condition variable!");
}

void POSIXThreadingFactory::ConditionVariable::Wait() {
    if (pthread_cond_wait(&conditionVariable_, associatedMutex_))
        HandleTerminalCondition("failed to wait on POSIX condition variable!");
}

void POSIXThreadingFactory::ConditionVariable::SignalAll() {
    if (pthread_cond_broadcast(&conditionVariable_))
        HandleTerminalCondition("failed to signal on POSIX condition variable!");
}

POSIXThreadingFactory::ThreadControl::ThreadControl()
        : spawned_(false),
          joined_(false) {
}

void POSIXThreadingFactory::ThreadControl::Spawn(ActionInterface *action) {
    if (spawned_)
        return;
    if (pthread_create(&thread_, 0, SpawnerRoutine, reinterpret_cast<void *>(action)))
        HandleTerminalCondition("failed to spawn new thread!");
    spawned_ = true;
}

void POSIXThreadingFactory::ThreadControl::Join() {
    if (joined_)
        return;
    if (spawned_) {
        if (pthread_join(thread_, 0))
            HandleTerminalCondition("failed to join thread!");
    }
    joined_ = true;
}

void *POSIXThreadingFactory::ThreadControl::SpawnerRoutine(void *castActionPtr) {
    reinterpret_cast<ActionInterface *>(castActionPtr)->ExecuteAction();
    return 0;
}

}    // Namespace Core.
}    // Namespace kxm.
