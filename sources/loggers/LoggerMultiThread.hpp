#pragma once

#include <mutex-wrappers/WrapperWithMutex.hpp>
#include <exceptions/Exception.hpp>
#include "SeverityLevel.hpp"
#include "LoggerFunctions.hpp"
#include "ILogger.hpp"

#include <experimental/source_location>
#include <ostream>
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

namespace kaktus
{
    template <typename Streamable, typename Stream>
    class LoggerMultiThread : public ILogger<Streamable>
    {
    public:
        explicit LoggerMultiThread(Stream &stream = std::cout) : m_stream({stream})
        {
            if(!stream)
            {
                throw kaktus::Exception("Given stream is not open.");
            }
        }
        ~LoggerMultiThread() = default;

        void log(const Streamable message, const SeverityLevel severityLevel, const std::experimental::source_location &source_location)
        {
            m_stream.print(message, severityLevel, source_location);
        }

    protected:

        class MultiThreadStreamWrapper : public WrapperWithMutex<Stream, std::mutex>
        {
        public:
            explicit MultiThreadStreamWrapper(Stream &ostream) : WrapperWithMutex<Stream, std::mutex>(ostream)
            {

                if(!this->m_object)
                {
                    throw kaktus::Exception("Given stream is not open.");
                }
            }
            void print(const Streamable message, const SeverityLevel severityLevel,
                    const std::experimental::source_location &source_location)
            {
                std::lock_guard<std::mutex> lockGuard(this->m_mutex);
                formatToStream(this->m_object, time());
                formatToStream(this->m_object, kaktus::to_string(severityLevel));
                formatToStream(this->m_object, source_location.file_name());
                formatToStream(this->m_object, source_location.line());
                formatToStream(this->m_object, source_location.column());
                formatToStream(this->m_object, source_location.function_name());
                formatToStream(this->m_object, message);
                this->m_object << std::endl;
            }
        };

        kaktus::LoggerMultiThread<Streamable, Stream>::MultiThreadStreamWrapper m_stream;
    };
}
