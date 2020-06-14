#include <gtest/gtest.h>
#include <loggers/LoggerMultiThread.hpp>
#include "LoggerTestFunctions.test.hpp"

#include <ostream>
#include <fstream>
#include <thread>

class LoggerMultiThreadFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }
    void TearDown() override
    {

    }
    std::string message()
    {
        return kaktus::to_string(m_severityLevel).append(" message");
    }
    void severity(kaktus::SeverityLevel severityLevel)
    {
        m_severityLevel = severityLevel;
    }
    auto severity()
    {
        return m_severityLevel;
    }
    kaktus::SeverityLevel m_severityLevel = kaktus::SeverityLevel::trace;

};

TEST_F(LoggerMultiThreadFixture, Constructor)
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

TEST_F(LoggerMultiThreadFixture, trace)
{
    severity(kaktus::SeverityLevel::trace);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.trace(message());
    });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.trace(message(), dummy_source_location());
    });
}

TEST_F(LoggerMultiThreadFixture, debug)
{
    severity(kaktus::SeverityLevel::debug);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.debug(message());
    });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.debug(message(), dummy_source_location());
    });
}

TEST_F(LoggerMultiThreadFixture, info)
{
    severity(kaktus::SeverityLevel::info);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.info(message());
    });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.info(message(), dummy_source_location());
    });
}

TEST_F(LoggerMultiThreadFixture, warning)
{
    severity(kaktus::SeverityLevel::warning);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.warning(message());
    });


    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.warning(message(), dummy_source_location());
    });
}

TEST_F(LoggerMultiThreadFixture, error)
{
    severity(kaktus::SeverityLevel::error);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.error(message());
    });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.error(message(), dummy_source_location());
    });
}

TEST_F(LoggerMultiThreadFixture, critical)
{
    severity(kaktus::SeverityLevel::critical);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.critical(message());
    });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerMultiThread>(message(), severity(), [&](kaktus::LoggerMultiThread &logger) {
        logger.critical(message(), dummy_source_location());
    });
}

TEST_F(LoggerMultiThreadFixture, multipleThreads)
{
    const unsigned int iterationLimit = 100; //higher count with bad or without mutex can cause crash
    std::stringstream sstream;
    kaktus::LoggerMultiThread logger(sstream);

    //
    // Prepare lambdas for threads
    //

    auto criticalLambda([&]() -> void {
        testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
            logger.critical(message);
        });
    });

    auto errorLambda([&]() -> void {
        testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
            logger.error(message);
        });
    });

    auto warningLambda([&]() -> void {
        testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
            logger.warning(message);
        });
    });

    auto infoLambda([&]() -> void {
        testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
            logger.info(message);
        });
    });

    auto debugLambda([&]() -> void {
        testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
            logger.debug(message);
        });
    });

    auto traceLambda([&]() -> void {
        testThreadMainFunction(iterationLimit, logger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
            logger.trace(message);
        });
    });

    //
    // getting character counts for single iteration
    //

    const unsigned int singleIteration = 1;
    std::stringstream singleLine;
    kaktus::LoggerMultiThread testerLogger(singleLine);
    testThreadMainFunction(singleIteration, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
        logger.critical(message);
    });

    unsigned int charactersInSingleCriticalLine = singleLine.str().length();
    singleLine.str(std::string());

    testThreadMainFunction(singleIteration, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
        logger.error(message);
    });

    unsigned int charactersInSingleErrorLine = singleLine.str().length();
    singleLine.str(std::string());

    testThreadMainFunction(singleIteration, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
        logger.warning(message);
    });

    unsigned int charactersInSingleWarningLine = singleLine.str().length();
    singleLine.str(std::string());

    testThreadMainFunction(singleIteration, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
        logger.info(message);
    });

    unsigned int charactersInSingleInfoLine = singleLine.str().length();
    singleLine.str(std::string());

    testThreadMainFunction(singleIteration, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
        logger.debug(message);
    });

    unsigned int charactersInSingleDebugLine = singleLine.str().length();
    singleLine.str(std::string());

    testThreadMainFunction(singleIteration, testerLogger, [&](kaktus::LoggerMultiThread &logger, const std::string &message) {
        logger.trace(message);
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
    catch (kaktus::Exception &exception)
    {
        std::cerr << exception.what() << std::endl;
        FAIL();
    }
    catch (std::exception &exception)
    {
        std::cerr << exception.what() << std::endl;
        FAIL();
    }


    std::cout << "Got characters:  " << sstream.str().length() << std::endl;
    ASSERT_EQ(expectedCharacterCount, sstream.str().length());
}
