#include <gtest/gtest.h>

#include "LoggerTestFunctions.test.hpp"
#include <loggers/LoggerSingleThread.hpp>

#include <ostream>
#include <fstream>

namespace fatanyu
{

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
    fatanyu::testDefaultLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.trace(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
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
    fatanyu::testDefaultLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.debug(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
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
    fatanyu::testDefaultLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.info(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
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
    fatanyu::testDefaultLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.warning(messageToLog.c_str());
    });


    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
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
    fatanyu::testDefaultLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.error(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
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
    fatanyu::testDefaultLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.critical(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    fatanyu::testAdvancedLog<fatanyu::LoggerSingleThread>(messageToLog, messageType, [&](fatanyu::LoggerSingleThread &logger) {
        logger.critical(messageToLog.c_str(), fatanyu::dummy_source_location());
    });
}