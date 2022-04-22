#include "Mutex.h"

MutexHandle Mutex::Lock() 
{
    mutex.lock();
    mIsLock = true;
    return this;
}

void Mutex::OnDestroy()
{
    mIsLock = false;
    mutex.unlock();
}