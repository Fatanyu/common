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

inline std::experimental::source_location dummy_source_location() noexcept
{
    return std::experimental::source_location::current("dummy-file-name.cpp",
                                                       "myDummyFunctionName",
                                                       42,
                                                       0);
}

