#include <gtest/gtest.h>
#include <loggers/LoggerMultiThread.hpp>
#include "LoggerTestFunctions.test.hpp"

#include <ostream>
#include <fstream>
#include <thread>

using MultiThreadLogger = kaktus::LoggerMultiThread<std::string, std::ostream>;

void threadMain(unsigned int iterationLimit, kaktus::SeverityLevel severityLevel,
                MultiThreadLogger &logger)
{
    std::string message("some message");
    for (unsigned int current = 0; current < iterationLimit; current++)
    {
        logger.log(message, severityLevel, dummy_source_location());
    }
}

class LoggerMultiThreadFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_logger = std::make_unique<MultiThreadLogger>(m_stringstream);
        m_stringstream.str("");
    }

    void TearDown() override
    {
        m_logger.reset();
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

    void logMessage()
    {
        m_logger->log(message(), severity(), dummy_source_location());

        std::string result = m_stringstream.str();

        std::cout << result << std::endl;
        EXPECT_NE(result.find(formatToString(message())), std::string::npos);
        EXPECT_NE(result.find(formatToString(kaktus::to_string(severity()))), std::string::npos);
    }

    kaktus::SeverityLevel m_severityLevel = kaktus::SeverityLevel::trace;
    std::unique_ptr<MultiThreadLogger> m_logger;
    std::stringstream m_stringstream;
};

TEST_F(LoggerMultiThreadFixture, Constructor)
{
    std::stringstream stringstream;
    std::ofstream ofstream("someFile", std::ios::out);
    std::ofstream emptyOfstream("", std::ios::out);

    EXPECT_NO_THROW( MultiThreadLogger loggerMultiThread(stringstream));
    EXPECT_NO_THROW(MultiThreadLogger loggerMultiThread);
    EXPECT_NO_THROW(MultiThreadLogger loggerMultiThread(std::cerr));
    EXPECT_NO_THROW(MultiThreadLogger loggerMultiThread(ofstream));
    EXPECT_THROW(MultiThreadLogger loggerMultiThread(emptyOfstream), kaktus::Exception);
    EXPECT_THROW(MultiThreadLogger loggerMultiThread(emptyOfstream), std::exception);

}

TEST_F(LoggerMultiThreadFixture, trace)
{
    severity(kaktus::SeverityLevel::trace);
    EXPECT_NO_THROW(logMessage());
    severity(kaktus::SeverityLevel::debug);
    EXPECT_NO_THROW(logMessage());
    severity(kaktus::SeverityLevel::info);
    EXPECT_NO_THROW(logMessage());
    severity(kaktus::SeverityLevel::warning);
    EXPECT_NO_THROW(logMessage());
    severity(kaktus::SeverityLevel::error);
    EXPECT_NO_THROW(logMessage());
    severity(kaktus::SeverityLevel::critical);
    EXPECT_NO_THROW(logMessage());
    severity(kaktus::SeverityLevel::debug);
    EXPECT_NO_THROW(logMessage());
}


TEST_F(LoggerMultiThreadFixture, multipleThreads)
{
    unsigned int iterationLimit = 10000; //higher count with bad or without mutex can cause crash
    std::stringstream sstream;
    MultiThreadLogger logger(sstream);

    const unsigned int singleIteration = 1;
    std::stringstream singleLine;
    std::vector<unsigned int> charactersInSingleLine;
    std::vector<kaktus::SeverityLevel> severityLevels{
            kaktus::SeverityLevel::critical,
            kaktus::SeverityLevel::error,
            kaktus::SeverityLevel::warning,
            kaktus::SeverityLevel::info,
            kaktus::SeverityLevel::debug,
            kaktus::SeverityLevel::trace
    };

    //
    // getting character counts for single iteration
    //

    for(const auto level : severityLevels)
    {
        MultiThreadLogger testerLogger(singleLine);
        threadMain(singleIteration, level, testerLogger);

        charactersInSingleLine.push_back(singleLine.str().length());
        singleLine.str(std::string());
    }

    unsigned int expectedCharacterCount = 0;
    for(const auto count : charactersInSingleLine)
    {
        expectedCharacterCount += count;
    }
    expectedCharacterCount *= iterationLimit;
    std::cout << "Expected characters: " << expectedCharacterCount << std::endl;

    //
    // Test execution
    //

    try
    {
        std::thread critical(threadMain, iterationLimit, kaktus::SeverityLevel::critical, std::ref(logger));
        std::thread error(threadMain, iterationLimit, kaktus::SeverityLevel::error, std::ref(logger));
        std::thread warning(threadMain, iterationLimit, kaktus::SeverityLevel::warning, std::ref(logger));
        std::thread info(threadMain, iterationLimit, kaktus::SeverityLevel::info, std::ref(logger));
        std::thread debug(threadMain, iterationLimit, kaktus::SeverityLevel::debug, std::ref(logger));
        std::thread trace(threadMain, iterationLimit, kaktus::SeverityLevel::trace, std::ref(logger));


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
