#pragma once

#include <exception>
#include <string>
#include <experimental/source_location>
#include <sstream>
#include <concepts>
#include <codecvt>

using namespace std::string_literals;

//template <typename T>
//concept Streamable = std::is_convertible<std::string>;

namespace kaktus
{
    /**
     * Custom exception which also provides additional information via source_location
     */
    class Exception : public std::exception
    {
    public:
        template <typename Streamable>
        explicit Exception(const Streamable message, const std::experimental::source_location& source_location = std::experimental::source_location::current())
        : m_message(message), m_source_location(source_location)
        {
            formatMessage();
        }
        ~Exception() override = default;

        [[nodiscard]]
        const char *what() const noexcept override
        {
            return m_prettyMessage.c_str();
        }

        [[nodiscard]]
        std::string message() const noexcept
        {
            return m_message;
        }

        [[nodiscard]]
        std::string prettyMessage() const noexcept
        {
            return m_prettyMessage;
        }

        [[nodiscard]]
        std::wstring wmessage() const noexcept
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.from_bytes(m_message);
        }

        [[nodiscard]]
        std::wstring wprettyMessage() const noexcept
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.from_bytes(m_prettyMessage);
        }
    protected:
        void formatMessage()
        {
            //stringstream for some reason not working https://stackoverflow.com/questions/41854840/var-create-unable-to-create-variable-object
            m_prettyMessage.append(m_source_location.file_name());
            m_prettyMessage.append(m_delimiter);
            m_prettyMessage.append(std::to_string(m_source_location.line()));
            m_prettyMessage.append(m_delimiter);
            m_prettyMessage.append(std::to_string(m_source_location.column()));
            m_prettyMessage.append(m_delimiter);
            m_prettyMessage.append(m_source_location.function_name());
            m_prettyMessage.append(m_delimiter);
            m_prettyMessage.append(m_message);
        }

        const std::string m_message;
        const std::string m_delimiter = ":"s;
        std::string m_prettyMessage;
        const std::experimental::source_location& m_source_location;
    };
}