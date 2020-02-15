#pragma once

#include <gtest/gtest.h>

#include <string>
#include <functional>
#include <sstream>
#include <experimental/source_location>
#include <loggers/LoggerMultiThread.hpp>


namespace kaktus
{
    std::string formatColumn(const char* value);
    std::string formatColumn(int value);

    std::experimental::source_location dummy_source_location() noexcept;

    template <typename GenericLogger>
    void testDefaultLog(const std::string &messageToLog, const std::string &messageType,
                        const std::function<void(GenericLogger &genericLogger)>& logMessage)
    {
        std::stringstream stringstream;
        GenericLogger genericLogger(stringstream);

        EXPECT_NO_THROW(logMessage(genericLogger));
        std::string result = stringstream.str();

        std::cout << result << std::endl;
        EXPECT_NE(result.find(kaktus::formatColumn(messageToLog.c_str())), std::string::npos);
        EXPECT_NE(result.find(kaktus::formatColumn(messageType.c_str())), std::string::npos);
    }

    template <typename GenericLogger>
    void testAdvancedLog(const std::string &messageToLog, const std::string &messageType,
                         const std::function<void(GenericLogger &genericLogger)>& logMessage)
    {
        std::stringstream stringstream;
        GenericLogger genericLogger(stringstream);

        EXPECT_NO_THROW(logMessage(genericLogger));
        std::string result = stringstream.str();
        auto dummySourceLocation = kaktus::dummy_source_location();
        std::stringstream wantedLine;
        // column date && time is not part of check
        wantedLine << kaktus::formatColumn(messageType.c_str())
                   << kaktus::formatColumn(dummySourceLocation.file_name())
                   << kaktus::formatColumn(dummySourceLocation.line())
                   << kaktus::formatColumn(dummySourceLocation.column())
                   << kaktus::formatColumn(dummySourceLocation.function_name())
                   << kaktus::formatColumn(messageToLog.c_str())
                   << std::endl;
        EXPECT_NE(result.find(wantedLine.str()), std::string::npos);
    }

    void testThreadMainFunction(unsigned int iterationLimit, kaktus::LoggerMultiThread &genericLogger, const std::function<void(kaktus::LoggerMultiThread &genericLogger, const std::string &messageToLog)>& logMessage);
}