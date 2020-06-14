#pragma once
/**
 * Trivial use case:
 * You want to hide std::stream behind std::mutex. Use inheritance.
 *
 * class StreamWrapper : public WrapperWithMutex<std::ostream, std::mutex>
 * {
 * public:
 *     StreamWrapper(std::ostream &ostream) : WrapperWithMutex<std::ostream, std::mutex>(ostream)
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
class WrapperWithMutex
{
public:
    explicit WrapperWithMutex(Object &object) : m_object(object)
    {}

protected:
    Object &m_object;
    Mutex m_mutex;
};
