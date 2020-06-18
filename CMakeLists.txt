cmake_minimum_required(VERSION 3.15)
project(common)


set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra")

include_directories(sources)

add_library(exception STATIC sources/exceptions/Exception.hpp)
set_target_properties(exception PROPERTIES LINKER_LANGUAGE CXX) ### uncomment when no cpp file is in the library

add_library(wrapper-with-mutex STATIC sources/mutex-wrappers/WrapperWithMutex.hpp sources/mutex-wrappers/WrapperWithGivenMutex.hpp)
set_target_properties(wrapper-with-mutex  PROPERTIES LINKER_LANGUAGE CXX)

add_library(guarded-object STATIC sources/mutex-wrappers/GuardedObject.hpp)
set_target_properties(guarded-object PROPERTIES LINKER_LANGUAGE CXX)

add_library(logger-single-thread STATIC sources/loggers/LoggerSingleThread.hpp sources/loggers/SeverityLevel.hpp sources/loggers/LoggerFunctions.hpp sources/loggers/ILogger.hpp)
set_target_properties(logger-single-thread  PROPERTIES LINKER_LANGUAGE CXX)

add_library(logger-multi-thread STATIC sources/loggers/LoggerMultiThread.hpp sources/loggers/SeverityLevel.hpp sources/loggers/LoggerFunctions.hpp sources/loggers/ILogger.hpp)
set_target_properties(logger-multi-thread PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(external-libraries/google-tests)
include_directories(external-libraries/google-tests/googletest/googletest/include)
include_directories(external-libraries/google-tests/googletest/googlemock/include)