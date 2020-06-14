#include <gtest/gtest.h>

#include "LoggerTestFunctions.test.hpp"
#include <loggers/LoggerSingleThread.hpp>

#include <ostream>
#include <fstream>

class LoggerSingleThreadFixture : public ::testing::Test
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


TEST_F(LoggerSingleThreadFixture, Constructor)
{
    std::stringstream stringstream;
    std::ofstream ofstream("someFile", std::ios::out);
    std::ofstream emptyOfstream("", std::ios::out);

    EXPECT_NO_THROW(kaktus::LoggerSingleThread loggerSingleThread(stringstream));
    EXPECT_NO_THROW(kaktus::LoggerSingleThread loggerSingleThread);
    EXPECT_NO_THROW(kaktus::LoggerSingleThread loggerSingleThread(std::cerr));
    EXPECT_NO_THROW(kaktus::LoggerSingleThread loggerSingleThread(ofstream));
    EXPECT_THROW(kaktus::LoggerSingleThread loggerSingleThread(emptyOfstream), kaktus::Exception);
    EXPECT_THROW(kaktus::LoggerSingleThread loggerSingleThread(emptyOfstream), std::exception);

}

TEST_F(LoggerSingleThreadFixture, trace)
{
    severity(kaktus::SeverityLevel::trace);
    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerSingleThread>(message(),
                                               severity(),
                                               [&](kaktus::LoggerSingleThread &logger) {
                logger.trace(message());
            });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerSingleThread>(message(),
                                                severity(),
                                                [&](kaktus::LoggerSingleThread &logger) {
                logger.trace(message(), dummy_source_location());
            });
}

TEST_F(LoggerSingleThreadFixture, debug)
{
    severity(kaktus::SeverityLevel::debug);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerSingleThread>(message(),
                                                severity(),
                                                [&](kaktus::LoggerSingleThread &logger) {
                logger.debug(message());
            });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerSingleThread>(message(),
                                                severity(),
                                                [&](kaktus::LoggerSingleThread &logger) {
                logger.debug(message(), dummy_source_location());
            });
}

TEST_F(LoggerSingleThreadFixture, info)
{
    severity(kaktus::SeverityLevel::info);


    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerSingleThread>(message(),
                                               severity(),
                                               [&](kaktus::LoggerSingleThread &logger) {
                logger.info(message());
            });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerSingleThread>(message(),
                                                severity(),
                                                [&](kaktus::LoggerSingleThread &logger) {
                logger.info(message(), dummy_source_location());
            });
}

TEST_F(LoggerSingleThreadFixture, warning)
{
    severity(kaktus::SeverityLevel::warning);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerSingleThread>(message(),
                                               severity(),
                                               [&](kaktus::LoggerSingleThread &logger) {
                logger.warning(message());
            });


    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerSingleThread>(message(),
                                                severity(),
                                                [&](kaktus::LoggerSingleThread &logger) {
                logger.warning(message(), dummy_source_location());
            });
}

TEST_F(LoggerSingleThreadFixture, error)
{
    severity(kaktus::SeverityLevel::error);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerSingleThread>(message(),
                                               severity(),
                                               [&](kaktus::LoggerSingleThread &logger) {
                logger.error(message());
            });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerSingleThread>(message(),
                                                severity(),
                                                [&](kaktus::LoggerSingleThread &logger) {
                logger.error(message(), dummy_source_location());
            });
}

TEST_F(LoggerSingleThreadFixture, critical)
{
    severity(kaktus::SeverityLevel::critical);

    //
    // Default logging
    //
    testDefaultLog<kaktus::LoggerSingleThread>(message(),
                                               severity(),
                                               [&](kaktus::LoggerSingleThread &logger) {
                logger.critical(message());
            });

    //
    // Full logging with mocking source_location
    //

    testAdvancedLog<kaktus::LoggerSingleThread>(message(),
                                                severity(),
                                                [&](kaktus::LoggerSingleThread &logger) {
                logger.critical(message(), dummy_source_location());
            });
}