#pragma once

#include <exception>
#include <string>
#include <experimental/source_location>
#include <sstream>

namespace fatanyu
{
    class Exception : public std::exception
    {
    public:
        explicit Exception(const char* message, const std::experimental::source_location& source_location = std::experimental::source_location::current());
        ~Exception() = default;

        [[nodiscard]]
        const char *what() const noexcept override
        {
            return m_finalMessage.c_str();
        }

    protected:
        void formatMessage();

        const char* m_message;
        const char* m_delimiter = ":";
        std::string m_finalMessage;
        const std::experimental::source_location& m_source_location;
    };
}