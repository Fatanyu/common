#pragma once

#include <experimental/source_location>
#include <ostream>
#include <iostream>
#include <exceptions/Exception.hpp>
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

        void trace(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            print(message, source_location, "trace");
        }

        void debug(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            print(message, source_location, "debug");
        }

        void info(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            print(message, source_location, "info");
        }

        void warning(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            print(message, source_location, "warning");
        }

        void error(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            print(message, source_location, "error");
        }

        void critical(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            print(message, source_location, "critical");
        }

    protected:
        void print(const char *message, const std::experimental::source_location &source_location, const char* severityLevel) noexcept
        {
            formatColumnAndPrint(currentTime().c_str());
            formatColumnAndPrint(severityLevel);
            formatColumnAndPrint(source_location.file_name());
            formatColumnAndPrint(source_location.line());
            formatColumnAndPrint(source_location.column());
            formatColumnAndPrint(source_location.function_name());
            formatColumnAndPrint(message);
            m_ostream << std::endl;
        }

        static std::string currentTime() noexcept
        {
            const int bufferSize = 20;
            char buffer[bufferSize];
            std::time_t timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            strftime(buffer, bufferSize, "%F %X", localtime(&timeNow));
            return buffer;
        }

        template <typename Streamable>
        void formatColumnAndPrint(Streamable value) noexcept
        {
            m_ostream << "[" << value << "]";
        }
        std::ostream &m_ostream;
    };
}
