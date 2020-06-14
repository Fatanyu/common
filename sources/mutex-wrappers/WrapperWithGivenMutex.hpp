#pragma once

/**
 * Trivial use case:
 * You want to hide std::stream behind std::mutex. Use inheritance.
 *
 * class StreamWrapper : public WrapperWithGivenMutex<std::ostream, std::mutex>
 * {
 * public:
 *     StreamWrapper(std::ostream &ostream, std::mutex &mutex) : WrapperWithGivenMutex<std::ostream, std::mutex>(ostream, mutex)
 *     {}
 *
 *     void write(const std::string &message)
 *     {
 *         std::lock_guard<std::mutex> guard(m_mutex);
 *         m_object << message << std::endl;
 *     }
 * };
 */

template <typename Object, typename Mutex>
class WrapperWithGivenMutex
{
public:
    WrapperWithGivenMutex(Object &object, Mutex &mutex) : m_object(object), m_mutex(mutex)
    {}
protected:
    Object &m_object;
    Mutex &m_mutex;
};