#pragma once

#include <gtest/gtest.h>

#include <string>
#include <functional>
#include <sstream>
#include <experimental/source_location>
#include <loggers/LoggerMultiThread.hpp>


namespace fatanyu
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

        EXPECT_NE(result.find(fatanyu::formatColumn(messageToLog.c_str())), std::string::npos);
        EXPECT_NE(result.find(fatanyu::formatColumn(messageType.c_str())), std::string::npos);
    }

    template <typename GenericLogger>
    void testAdvancedLog(const std::string &messageToLog, const std::string &messageType,
                         const std::function<void(GenericLogger &genericLogger)>& logMessage)
    {
        std::stringstream stringstream;
        GenericLogger genericLogger(stringstream);

        EXPECT_NO_THROW(logMessage(genericLogger));
        std::string result = stringstream.str();
        auto dummySourceLocation = fatanyu::dummy_source_location();
        std::stringstream wantedLine;
        // column date && time is not part of check
        wantedLine << fatanyu::formatColumn(messageType.c_str())
                   << fatanyu::formatColumn(dummySourceLocation.file_name())
                   << fatanyu::formatColumn(dummySourceLocation.line())
                   << fatanyu::formatColumn(dummySourceLocation.column())
                   << fatanyu::formatColumn(dummySourceLocation.function_name())
                   << fatanyu::formatColumn(messageToLog.c_str())
                   << std::endl;
        EXPECT_NE(result.find(wantedLine.str()), std::string::npos);
    }

    void testThreadMainFunction(unsigned int iterationLimit, fatanyu::LoggerMultiThread &genericLogger, const std::function<void(fatanyu::LoggerMultiThread &genericLogger, const std::string &messageToLog)>& logMessage);
}