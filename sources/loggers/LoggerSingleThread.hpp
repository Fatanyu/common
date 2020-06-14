#pragma once

#include <exceptions/Exception.hpp>
#include "SeverityLevel.hpp"
#include "LoggerFunctions.hpp"
#include "ILogger.hpp"

#include <experimental/source_location>
#include <ostream>
#include <iostream>

namespace kaktus
{
    template <typename Streamable, typename Stream>
    class LoggerSingleThread : public ILogger<Streamable>
    {
    public:
        explicit LoggerSingleThread(Stream &stream = std::cout) : m_stream(stream)
        {
            if(!stream)
            {
                throw kaktus::Exception("Given stream is not open.");
            }
        }
        ~LoggerSingleThread() = default;

        void log(const Streamable message, const SeverityLevel severityLevel,
                const std::experimental::source_location &source_location)
        {
            formatToStream(m_stream, time());
            formatToStream(m_stream, kaktus::to_string(severityLevel));
            formatToStream(m_stream, source_location.file_name());
            formatToStream(m_stream, source_location.line());
            formatToStream(m_stream, source_location.column());
            formatToStream(m_stream, source_location.function_name());
            formatToStream(m_stream, message);
            m_stream << std::endl;
        }

    protected:
        Stream &m_stream;
    };
}
