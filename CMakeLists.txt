cmake_minimum_required(VERSION 3.15)
project(common)


set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra")

include_directories(sources)

add_library(exception STATIC sources/exceptions/Exception.hpp sources/exceptions/Exception.cpp)
#set_target_properties(exception PROPERTIES LINKER_LANGUAGE CXX) ### uncomment when no cpp file is in the library

add_library(wrapper-with-mutex STATIC sources/mutex-wrappers/WrapperWithMutex.cpp sources/mutex-wrappers/WrapperWithMutex.hpp sources/mutex-wrappers/WrapperWithGivenMutex.hpp)
add_library(guarded-object STATIC sources/mutex-wrappers/GuardedObject.cpp sources/mutex-wrappers/GuardedObject.hpp)
add_library(logger-single-thread STATIC sources/loggers/LoggerSingleThread.hpp sources/loggers/LoggerSingleThread.cpp sources/loggers/SeverityLevel.hpp sources/loggers/LoggerFunctions.hpp)
add_library(logger-multi-thread STATIC sources/loggers/LoggerMultiThread.cpp sources/loggers/LoggerMultiThread.hpp sources/loggers/SeverityLevel.hpp sources/loggers/LoggerFunctions.hpp)

add_subdirectory(external-libraries/google-tests)
include_directories(external-libraries/google-tests/googletest/googletest/include)
include_directories(external-libraries/google-tests/googletest/googlemock/include)