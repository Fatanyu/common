#pragma once

#include <experimental/source_location>
#include <ostream>
#include <iostream>
#include <exceptions/Exception.hpp>
#include <chrono>

namespace fatanyu
{
    class LoggerSingleThread
    {
    public:
        explicit LoggerSingleThread(std::ostream &ostream = std::cout) : m_ostream(ostream)
        {
            if(!ostream)
            {
                throw fatanyu::Exception("Given stream is not open.");
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
            m_ostream << formatCollumn(currentTime().c_str()) <<
                      formatCollumn(severityLevel) <<
                      formatCollumn(source_location.file_name()) <<
                      formatCollumn(source_location.line()) <<
                      formatCollumn(source_location.column()) <<
                      formatCollumn(source_location.function_name()) <<
                      formatCollumn(message) << std::endl;
        }

        static std::string currentTime()
        {
            const int bufferSize = 20;
            char buffer[bufferSize];
            std::time_t timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            strftime(buffer, bufferSize, "%F %X", localtime(&timeNow));
            return buffer;
        }

        static std::string formatCollumn(const char* value)
        {
            return std::string("[").append(value).append("]");
        }

        static std::string formatCollumn(int value)
        {
            return std::string("[").append(std::to_string(value)).append("]");
        }

        std::ostream &m_ostream;
    };
}
