#pragma once

#include "MutexHandle.h"
#include <mutex>

class Mutex final
{
public:
    [[nodiscard]] MutexHandle Lock();

    void OnDestroy();

private:
    std::mutex mutex;
    bool mIsLock = false;
};