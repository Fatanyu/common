#include "LoggerTestFunctions.test.hpp"

namespace kaktus
{
    std::string formatColumn(const char *value)
    {
        return std::string("[").append(value).append("]");
    }

    std::string formatColumn(int value)
    {
        return std::string("[").append(std::to_string(value)).append("]");
    }

    std::experimental::source_location dummy_source_location() noexcept
    {
        return std::experimental::source_location::current("dummy-file-name.cpp",
                                                           "myDummyFunctionName",
                                                           42,
                                                           0);
    }

    void testThreadMainFunction(unsigned int iterationLimit, kaktus::LoggerMultiThread &genericLogger, const std::function<void(kaktus::LoggerMultiThread &genericLogger, const std::string &messageToLog)>& logMessage)
    {
        std::string messageToLog("some message");
        for(unsigned int current = 0; current < iterationLimit; current++)
        {
            logMessage(genericLogger, messageToLog);
        }
    }
}