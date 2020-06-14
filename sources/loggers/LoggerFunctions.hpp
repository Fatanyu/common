#pragma once
#include <string>
#include <chrono>

namespace kaktus
{
    /**
     * @return "YYYY-MM-DD hh:mm:ss" (24 hour format)
     */
    inline std::string time()
    {
        std::string buffer(20, '\0'); //20 should be enough for this time format
        std::time_t timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        strftime(buffer.data(), buffer.capacity(), "%F %X", localtime(&timeNow));
        return buffer;
    }

    template <typename Stream, typename Streamable>
    void formatToStream(Stream &stream, const Streamable &value)
    {
        stream << "[" << value << "]";
    }
}