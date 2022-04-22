#pragma once

class Mutex;

struct MutexHandle
{
    friend class Mutex;

    ~MutexHandle();

private:
    MutexHandle(Mutex* owner) : mOwner(owner) {}

    Mutex *mOwner;
};