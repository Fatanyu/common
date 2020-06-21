#include <gtest/gtest.h>

#include "LoggerTestFunctions.test.hpp"
#include <loggers/LoggerSingleThread.hpp>

#include <ostream>
#include <fstream>

class LoggerSingleThreadFixture : public ::testing::Test
{
protected:
    using SingleThreadLogger = kaktus::LoggerSingleThread<std::string, std::ostream>;
    void SetUp() override
    {
        m_logger = std::make_unique<SingleThreadLogger>(m_stringstream);
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

        m_logger->log("I should too be logged.", kaktus::SeverityLevel::critical, dummy_source_location()); //std::string logger, char* message

    }

    kaktus::SeverityLevel m_severityLevel = kaktus::SeverityLevel::trace;
    std::unique_ptr<SingleThreadLogger> m_logger;
    std::stringstream m_stringstream;
};


TEST_F(LoggerSingleThreadFixture, Constructor)
{
    std::stringstream stringstream;
    std::ofstream ofstream("someFile", std::ios::out);
    std::ofstream emptyOfstream("", std::ios::out);

    EXPECT_NO_THROW(SingleThreadLogger loggerSingleThread(stringstream));
    EXPECT_NO_THROW(SingleThreadLogger loggerSingleThread);
    EXPECT_NO_THROW(SingleThreadLogger loggerSingleThread(std::cerr));
    EXPECT_NO_THROW(SingleThreadLogger loggerSingleThread(ofstream));
    EXPECT_THROW(SingleThreadLogger loggerSingleThread(emptyOfstream), kaktus::Exception);
    EXPECT_THROW(SingleThreadLogger loggerSingleThread(emptyOfstream), std::exception);

}

TEST_F(LoggerSingleThreadFixture, log)
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