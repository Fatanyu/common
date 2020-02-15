#include "Exception.hpp"


namespace kaktus
{

    Exception::Exception(const char *message, const std::experimental::source_location &source_location): m_source_location(source_location)
    {
        m_message = message;
        formatMessage();
    }

    void Exception::formatMessage()
    {
        //stringstream for some reason not working https://stackoverflow.com/questions/41854840/var-create-unable-to-create-variable-object
        m_finalMessage.append( m_source_location.file_name());
        m_finalMessage.append(m_delimiter);
        m_finalMessage.append(std::to_string(m_source_location.line()));
        m_finalMessage.append(m_delimiter);
        m_finalMessage.append(std::to_string(m_source_location.column()));
        m_finalMessage.append(m_delimiter);
        m_finalMessage.append(m_source_location.function_name());
        m_finalMessage.append(m_delimiter);
        m_finalMessage.append(m_message);
    }

}