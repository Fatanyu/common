#include "LoggerTestFunctions.test.hpp"


std::experimental::source_location dummy_source_location() noexcept
{
    return std::experimental::source_location::current("dummy-file-name.cpp",
                                                       "myDummyFunctionName",
                                                       42,
                                                       0);
}

void testThreadMainFunction(unsigned int iterationLimit, kaktus::LoggerMultiThread &genericLogger,
                            const std::function<void(kaktus::LoggerMultiThread &genericLogger,
                                    const std::string &message)> &logMessage)
{
    std::string message("some message");
    for (unsigned int current = 0; current < iterationLimit; current++)
    {
        logMessage(genericLogger, message);
    }
}
