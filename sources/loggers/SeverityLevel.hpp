#pragma once

#include <string>
#include <exceptions/Exception.hpp>

namespace kaktus
{
    enum class SeverityLevel
    {
        trace,
        debug,
        info,
        warning,
        error,
        critical
    };

    inline std::string to_string(SeverityLevel severityLevel) //inline is for google tests
    {
        switch (severityLevel)
        {
            case SeverityLevel::trace:
                return "trace";
            case SeverityLevel::debug:
                return "debug";
            case SeverityLevel::info:
                return "info";
            case SeverityLevel::warning:
                return "warning";
            case SeverityLevel::error:
                return "error";
            case SeverityLevel::critical:
                return "critical";
            default:
                throw kaktus::Exception("Missing implementation");
        }
    }
}