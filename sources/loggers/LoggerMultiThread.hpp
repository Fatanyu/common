#pragma once

#include <experimental/source_location>
#include <ostream>
#include <iostream>
#include <exceptions/Exception.hpp>
#include <chrono>
#include <mutex>

namespace fatanyu
{
    class LoggerMultiThread
    {
    public:
        explicit LoggerMultiThread(std::ostream &ostream = std::cout) : m_stream({ostream})
        {}
        ~LoggerMultiThread() = default;

        void trace(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            m_stream.print(message, source_location, "trace");
        }

        void debug(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            m_stream.print(message, source_location, "debug");
        }

        void info(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            m_stream.print(message, source_location, "info");
        }

        void warning(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            m_stream.print(message, source_location, "warning");
        }

        void error(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            m_stream.print(message, source_location, "error");
        }

        void critical(const char *message, const std::experimental::source_location &source_location = std::experimental::source_location::current()) noexcept
        {
            m_stream.print(message, source_location, "critical");
        }

    protected:

        class MultiThreadStreamWrapper
        {
        public:
            explicit MultiThreadStreamWrapper(std::ostream &ostream) : m_ostream(ostream)
            {
                if(!ostream)
                {
                    throw fatanyu::Exception("Given stream is not open.");
                }
            }

            void print(const char *message, const std::experimental::source_location &source_location, const char* severityLevel) noexcept
            {
                std::lock_guard<std::mutex> streamGuard(m_streamMutex);
                m_ostream << formatColumn(currentTime().c_str()) <<
                          formatColumn(severityLevel) <<
                          formatColumn(source_location.file_name()) <<
                          formatColumn(source_location.line()) <<
                          formatColumn(source_location.column()) <<
                          formatColumn(source_location.function_name()) <<
                          formatColumn(message) << std::endl;
            }

        protected:
            static std::string currentTime()
            {
                const int bufferSize = 20;
                char buffer[bufferSize];
                std::time_t timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                strftime(buffer, bufferSize, "%F %X", localtime(&timeNow));
                return buffer;
            }

            static std::string formatColumn(const char* value)
            {
                return std::string("[").append(value).append("]");
            }

            static std::string formatColumn(int value)
            {
                return std::string("[").append(std::to_string(value)).append("]");
            }

            std::ostream &m_ostream;
            std::mutex m_streamMutex;
        };

        fatanyu::LoggerMultiThread::MultiThreadStreamWrapper m_stream;
    };
}
