#pragma once

#include <exceptions/Exception.hpp>
#include "SeverityLevel.hpp"
#include "LoggerFunctions.hpp"

#include <experimental/source_location>
#include <ostream>
#include <iostream>
#include <chrono>

namespace kaktus
{
    class LoggerSingleThread
    {
    public:
        explicit LoggerSingleThread(std::ostream &ostream = std::cout) : m_ostream(ostream)
        {
            if(!ostream)
            {
                throw kaktus::Exception("Given stream is not open.");
            }
        }
        ~LoggerSingleThread() = default;

        template <typename Streamable>
        void trace(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            print(message, source_location, SeverityLevel::trace);
        }

        template <typename Streamable>
        void debug(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            print(message, source_location, SeverityLevel::debug);
        }

        template <typename Streamable>
        void info(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            print(message, source_location, SeverityLevel::info);
        }

        template <typename Streamable>
        void warning(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            print(message, source_location, SeverityLevel::warning);
        }

        template <typename Streamable>
        void error(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            print(message, source_location, SeverityLevel::error);
        }

        template <typename Streamable>
        void critical(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            print(message, source_location, SeverityLevel::critical);
        }

    protected:
        template <typename Streamable>
        void print(const Streamable message, const std::experimental::source_location &source_location,
                const SeverityLevel severityLevel)
        {
            formatToStream(m_ostream, time());
            formatToStream(m_ostream, kaktus::to_string(severityLevel));
            formatToStream(m_ostream, source_location.file_name());
            formatToStream(m_ostream, source_location.line());
            formatToStream(m_ostream, source_location.column());
            formatToStream(m_ostream, source_location.function_name());
            formatToStream(m_ostream, message);
            m_ostream << std::endl;
        }

        std::ostream &m_ostream;
    };
}
