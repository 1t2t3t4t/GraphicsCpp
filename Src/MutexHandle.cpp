#include "Mutex.h"
#include "MutexHandle.h"

MutexHandle::~MutexHandle()
{
    if (mOwner)
    {
        mOwner->OnDestroy();
    }
}