#include <gtest/gtest.h>
#include <loggers/LoggerMultiThread.hpp>
#include "LoggerTestFunctions.test.hpp"

#include <ostream>
#include <fstream>
#include <thread>

TEST(LoggerMultiThread, Constructor)
{
    std::stringstream stringstream;
    std::ofstream ofstream("someFile", std::ios::out);
    std::ofstream emptyOfstream("", std::ios::out);

    EXPECT_NO_THROW(kaktus::LoggerMultiThread loggerMultiThread(stringstream));
    EXPECT_NO_THROW(kaktus::LoggerMultiThread loggerMultiThread);
    EXPECT_NO_THROW(kaktus::LoggerMultiThread loggerMultiThread(std::cerr));
    EXPECT_NO_THROW(kaktus::LoggerMultiThread loggerMultiThread(ofstream));
    EXPECT_THROW(kaktus::LoggerMultiThread loggerMultiThread(emptyOfstream), kaktus::Exception);
    EXPECT_THROW(kaktus::LoggerMultiThread loggerMultiThread(emptyOfstream), std::exception);

}

TEST(LoggerMultiThread, trace)
{
    std::string messageToLog("tracing message");
    std::string messageType("trace");

    //
    // Default logging
    //
    kaktus::testDefaultLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.trace(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    kaktus::testAdvancedLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.trace(messageToLog.c_str(), kaktus::dummy_source_location());
    });
}

TEST(LoggerMultiThread, debug)
{
    std::string messageToLog("debugging message");
    std::string messageType("debug");

    //
    // Default logging
    //
    kaktus::testDefaultLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.debug(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    kaktus::testAdvancedLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.debug(messageToLog.c_str(), kaktus::dummy_source_location());
    });
}

TEST(LoggerMultiThread, info)
{
    std::string messageToLog("info message");
    std::string messageType("info");

    //
    // Default logging
    //
    kaktus::testDefaultLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.info(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    kaktus::testAdvancedLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.info(messageToLog.c_str(), kaktus::dummy_source_location());
    });
}

TEST(LoggerMultiThread, warning)
{
    std::string messageToLog("warning message");
    std::string messageType("warning");

    //
    // Default logging
    //
    kaktus::testDefaultLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.warning(messageToLog.c_str());
    });


    //
    // Full logging with mocking source_location
    //

    kaktus::testAdvancedLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.warning(messageToLog.c_str(), kaktus::dummy_source_location());
    });
}

TEST(LoggerMultiThread, error)
{
    std::string messageToLog("error message");
    std::string messageType("error");

    //
    // Default logging
    //
    kaktus::testDefaultLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.error(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    kaktus::testAdvancedLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.error(messageToLog.c_str(), kaktus::dummy_source_location());
    });
}

TEST(LoggerMultiThread, critical)
{
    std::string messageToLog("critical message");
    std::string messageType("critical");

    //
    // Default logging
    //
    kaktus::testDefaultLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.critical(messageToLog.c_str());
    });

    //
    // Full logging with mocking source_location
    //

    kaktus::testAdvancedLog<kaktus::LoggerMultiThread>(messageToLog, messageType, [&](kaktus::LoggerMultiThread &logger) {
        logger.critical(messageToLog.c_str(), kaktus::dummy_source_location());
    });
}

TEST(LoggerMultiThread, multipleThreads)
{
    const unsigned int iterationLimit = 100; //higher count with bad or without mutex can cause crash
    std::stringstream sstream;
    kaktus::LoggerMultiThread logger(sstream);

    //
    // Prepare lambdas for threads
    //

    auto criticalLambda([&]() -> void {
        kaktus::testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
            logger.critical(messageToLog.c_str());
        });
    });

    auto errorLambda([&]() -> void {
        kaktus::testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
            logger.error(messageToLog.c_str());
        });
    });

    auto warningLambda([&]() -> void {
        kaktus::testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
            logger.warning(messageToLog.c_str());
        });
    });

    auto infoLambda([&]() -> void {
        kaktus::testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
            logger.info(messageToLog.c_str());
        });
    });

    auto debugLambda([&]() -> void {
        kaktus::testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
            logger.debug(messageToLog.c_str());
        });
    });

    auto traceLambda([&]() -> void {
        kaktus::testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
            logger.trace(messageToLog.c_str());
        });
    });

    //
    // getting character counts for single iteration
    //

    std::stringstream singleLine;
    kaktus::LoggerMultiThread testerLogger(singleLine);
    kaktus::testThreadMainFunction(1, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
        logger.critical(messageToLog.c_str());
    });

    unsigned int charactersInSingleCriticalLine = singleLine.str().length();
    singleLine.str(std::string());

    kaktus::testThreadMainFunction(1, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
        logger.error(messageToLog.c_str());
    });

    unsigned int charactersInSingleErrorLine = singleLine.str().length();
    singleLine.str(std::string());

    kaktus::testThreadMainFunction(1, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
        logger.warning(messageToLog.c_str());
    });

    unsigned int charactersInSingleWarningLine = singleLine.str().length();
    singleLine.str(std::string());

    kaktus::testThreadMainFunction(1, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
        logger.info(messageToLog.c_str());
    });

    unsigned int charactersInSingleInfoLine = singleLine.str().length();
    singleLine.str(std::string());

    kaktus::testThreadMainFunction(1, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
        logger.debug(messageToLog.c_str());
    });

    unsigned int charactersInSingleDebugLine = singleLine.str().length();
    singleLine.str(std::string());

    kaktus::testThreadMainFunction(1, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &messageToLog) {
        logger.trace(messageToLog.c_str());
    });

    unsigned int charactersInSingleTraceLine = singleLine.str().length();
    singleLine.str(std::string());

    unsigned int expectedCharacterCount = iterationLimit *
            (charactersInSingleCriticalLine +
            charactersInSingleErrorLine +
            charactersInSingleWarningLine +
            charactersInSingleInfoLine +
            charactersInSingleDebugLine +
            charactersInSingleTraceLine);

    std::cout << "Expected characters: " << expectedCharacterCount << std::endl;

    //
    // Test execution
    //

    try
    {
        std::thread critical(criticalLambda);
        std::thread error(errorLambda);
        std::thread warning(warningLambda);
        std::thread info(infoLambda);
        std::thread debug(debugLambda);
        std::thread trace(traceLambda);


        critical.join();
        error.join();
        warning.join();
        info.join();
        debug.join();
        trace.join();
    }
    catch (std::exception &exception)
    {
        std::cerr << exception.what() << std::endl;
        FAIL();
    }
    std::cout << "Got characters:  " << sstream.str().length() << std::endl;
    ASSERT_EQ(expectedCharacterCount, sstream.str().length());
}
