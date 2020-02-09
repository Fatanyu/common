cmake_minimum_required(VERSION 3.15)
project(common)


set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra")

include_directories(sources)

add_library(exception STATIC sources/exceptions/Exception.hpp sources/exceptions/Exception.cpp)
#set_target_properties(exception PROPERTIES LINKER_LANGUAGE CXX) ### uncomment when no cpp file is in the library
add_library(logger-single-thread STATIC sources/exceptions/Exception.hpp sources/loggers/LoggerSingleThread.cpp)

add_subdirectory(external-libraries/google-tests)
include_directories(external-libraries/google-tests/googletest/googletest/include)
include_directories(external-libraries/google-tests/googletest/googlemock/include)