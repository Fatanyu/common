#pragma once

#include <mutex-wrappers/WrapperWithMutex.hpp>
#include <exceptions/Exception.hpp>
#include "SeverityLevel.hpp"
#include "LoggerFunctions.hpp"

#include <experimental/source_location>
#include <ostream>
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

namespace kaktus
{
    class LoggerMultiThread
    {
    public:
        explicit LoggerMultiThread(std::ostream &ostream = std::cout) : m_stream({ostream})
        {}
        ~LoggerMultiThread() = default;

        template <typename Streamable>
        void trace(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            m_stream.print(message, source_location, SeverityLevel::trace);
        }

        template <typename Streamable>
        void debug(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            m_stream.print(message, source_location, SeverityLevel::debug);
        }

        template <typename Streamable>
        void info(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            m_stream.print(message, source_location, SeverityLevel::info);
        }

        template <typename Streamable>
        void warning(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            m_stream.print(message, source_location, SeverityLevel::warning);
        }

        template <typename Streamable>
        void error(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            m_stream.print(message, source_location, SeverityLevel::error);
        }

        template <typename Streamable>
        void critical(const Streamable message, const std::experimental::source_location &source_location =
                std::experimental::source_location::current())
        {
            m_stream.print(message, source_location, SeverityLevel::critical);
        }

    protected:

        class MultiThreadStreamWrapper : public WrapperWithMutex<std::ostream, std::mutex>
        {
        public:
            explicit MultiThreadStreamWrapper(std::ostream &ostream) : WrapperWithMutex<std::ostream, std::mutex>(ostream)
            {
                if(!m_object)
                {
                    throw kaktus::Exception("Given stream is not open.");
                }
            }
            template <typename Streamable>
            void print(const Streamable message, const std::experimental::source_location &source_location,
                    const SeverityLevel severityLevel)
            {
                std::lock_guard<std::mutex> lockGuard(m_mutex);
                formatToStream(m_object, time());
                formatToStream(m_object, kaktus::to_string(severityLevel));
                formatToStream(m_object, source_location.file_name());
                formatToStream(m_object, source_location.line());
                formatToStream(m_object, source_location.column());
                formatToStream(m_object, source_location.function_name());
                formatToStream(m_object, message);
                m_object << std::endl;
            }
        };

        kaktus::LoggerMultiThread::MultiThreadStreamWrapper m_stream;
    };
}
