#include <gtest/gtest.h>
#include <loggers/LoggerSingleThread.hpp>

#include <ostream>
#include <fstream>

namespace fatanyu
{
    std::string formatColumn(const char* value)
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

    void testDefaultLog(const std::string &messageToLog, const std::string &messageType,
                        const std::function<void(fatanyu::LoggerSingleThread &loggerSingleThread)>& logMessage)
    {
        std::stringstream stringstream;
        fatanyu::LoggerSingleThread loggerSingleThread(stringstream);

        EXPECT_NO_THROW(logMessage(loggerSingleThread));
        std::string result = stringstream.str();

        EXPECT_NE(result.find(fatanyu::formatColumn(messageToLog.c_str())), std::string::npos);
        EXPECT_NE(result.find(fatanyu::formatColumn(messageType.c_str())), std::string::npos);
    }

    void testAdvancedLog(const std::string &messageToLog, const std::string &messageType,
                         const std::function<void(fatanyu::LoggerSingleThread &loggerSingleThread)>& logMessage)
    {
        std::stringstream stringstream;
        fatanyu::LoggerSingleThread loggerSingleThread(stringstream);

        EXPECT_NO_THROW(logMessage(loggerSingleThread));
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
}


TEST(LoggerSingleThread, Constructor)
{
    std::stringstream stringstream;
    std::ofstream ofstream("someFile", std::ios::out);
    std::ofstream emptyOfstream("", std::ios::out);

    EXPECT_NO_THROW(fatanyu::LoggerSingleThread loggerSingleThread(stringstream));
    EXPECT_NO_THROW(fatanyu::LoggerSingleThread loggerSingleThread);
    EXPECT_NO_THROW(fatanyu::LoggerSingleThread loggerSingleThread(std::cerr));
    EXPECT_NO_THROW(fatanyu::LoggerSingleThread loggerSingleThread(ofstream));
    EXPECT_THROW(fatanyu::LoggerSingleThread loggerSingleThread(emptyOfstream), fatanyu::Exception);
    EXPECT_THROW(fatanyu::LoggerSingleThread loggerSingleThread(emptyOfstream), std::exception);

}

TEST(LoggerSingleThread, trace)
{
    std::string messageToLog("tracing message");
    std::string messageType("trace");

    //
    // Default logging
    //
    fatanyu::testDefaultLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.trace(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.trace(messageToLog.c_str(), fatanyu::dummy_source_location());
    });
}

TEST(LoggerSingleThread, debug)
{
    std::string messageToLog("debugging message");
    std::string messageType("debug");

    //
    // Default logging
    //
    fatanyu::testDefaultLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.debug(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.debug(messageToLog.c_str(), fatanyu::dummy_source_location());
    });
}

TEST(LoggerSingleThread, info)
{
    std::string messageToLog("info message");
    std::string messageType("info");

    //
    // Default logging
    //
    fatanyu::testDefaultLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.info(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.info(messageToLog.c_str(), fatanyu::dummy_source_location());
    });
}

TEST(LoggerSingleThread, warning)
{
    std::string messageToLog("warning message");
    std::string messageType("warning");

    //
    // Default logging
    //
    fatanyu::testDefaultLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.warning(messageToLog.c_str());
    });


    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.warning(messageToLog.c_str(), fatanyu::dummy_source_location());
    });
}

TEST(LoggerSingleThread, error)
{
    std::string messageToLog("error message");
    std::string messageType("error");

    //
    // Default logging
    //
    fatanyu::testDefaultLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.error(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.error(messageToLog.c_str(), fatanyu::dummy_source_location());
    });
}

TEST(LoggerSingleThread, critical)
{
    std::string messageToLog("critical message");
    std::string messageType("critical");

    //
    // Default logging
    //
    fatanyu::testDefaultLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.critical(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.critical(messageToLog.c_str(), fatanyu::dummy_source_location());
    });
}