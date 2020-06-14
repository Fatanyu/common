#pragma once

#include <gtest/gtest.h>

#include <string>
#include <functional>
#include <sstream>
#include <experimental/source_location>
#include <loggers/LoggerMultiThread.hpp>

template<typename Streamable>
std::string formatToString(const Streamable &value)
{
    std::stringstream stringstream;
    kaktus::formatToStream(stringstream, value);
    return stringstream.str();
}

std::experimental::source_location dummy_source_location() noexcept;

template<typename GenericLogger>
void testDefaultLog(const std::string &messageToLog, const kaktus::SeverityLevel &severityLevel,
                    const std::function<void(GenericLogger &genericLogger)> &logMessage)
{
    std::stringstream stringstream;
    GenericLogger genericLogger(stringstream);

    EXPECT_NO_THROW(logMessage(genericLogger));
    std::string result = stringstream.str();

    std::cout << result << std::endl;
    EXPECT_NE(result.find(formatToString(messageToLog)), std::string::npos);
    EXPECT_NE(result.find(formatToString(kaktus::to_string(severityLevel))), std::string::npos);
}

template<typename GenericLogger>
void testAdvancedLog(const std::string &messageToLog, const kaktus::SeverityLevel &severityLevel,
                     const std::function<void(GenericLogger &genericLogger)> &logMessage)
{
    std::stringstream stringstream;
    GenericLogger genericLogger(stringstream);

    EXPECT_NO_THROW(logMessage(genericLogger));
    std::string result = stringstream.str();
    auto dummySourceLocation = dummy_source_location();
    std::stringstream wantedLine;
    // column date && time is not part of check
    wantedLine << formatToString(kaktus::to_string(severityLevel))
               << formatToString(dummySourceLocation.file_name())
               << formatToString(dummySourceLocation.line())
               << formatToString(dummySourceLocation.column())
               << formatToString(dummySourceLocation.function_name())
               << formatToString(messageToLog)
               << std::endl;
    EXPECT_NE(result.find(wantedLine.str()), std::string::npos);
}

void testThreadMainFunction(unsigned int iterationLimit, kaktus::LoggerMultiThread &genericLogger,
                            const std::function<void(kaktus::LoggerMultiThread &genericLogger,
                                                     const std::string &messageToLog)> &logMessage);
