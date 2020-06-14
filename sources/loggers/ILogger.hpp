#pragma once


#include <experimental/source_location>
#include "SeverityLevel.hpp"

namespace kaktus
{
    template <typename Streamable>
    class ILogger
    {
    public:
        virtual void log(Streamable message, SeverityLevel severityLevel,
                const std::experimental::source_location &source_location) = 0;
    };


    template <typename Streamable>
    class IPrettyLogger
    {
        virtual void trace(const Streamable message, const std::experimental::source_location &source_location) = 0;
        virtual void debug(const Streamable message, const std::experimental::source_location &source_location) = 0;
        virtual void info(const Streamable message, const std::experimental::source_location &source_location) = 0;
        virtual void warning(const Streamable message, const std::experimental::source_location &source_location) = 0;
        virtual void error(const Streamable message, const std::experimental::source_location &source_location) = 0;
        virtual void critical(const Streamable message, const std::experimental::source_location &source_location) = 0;
    };
}