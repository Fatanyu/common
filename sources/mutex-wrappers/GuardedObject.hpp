#pragma once

#include <mutex>

/**
 * Purpose is to give someone object with active mutex and you do not trust that person with locking.
 * As long as this instance exists, mutex is locked.
 * You need to inherit and use friend to construct this class.
 */

template<typename Object, typename Mutex>
class GuardedObject
{
public:
    Object &object()
    {
        return object;
    }

protected:
    GuardedObject(Object &object, Mutex &mutex) : m_object(object), m_guard(mutex)
    {}

    Object &m_object;
    std::lock_guard<Mutex> m_guard;
};

