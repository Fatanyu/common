#include <gtest/gtest.h>
#include <exceptions/Exception.hpp>

TEST(Exception, Constructor)
{
    try
    {
        fatanyu::Exception customException("Somethings is wrong");
    }
    catch (std::exception &exception)
    {
        FAIL();
    }
}
TEST(Exception, RaiseException)
{
    try
    {
        throw fatanyu::Exception("Somethings is wrong");
    }
    catch (std::exception &exception)
    {
        std::string errorMessage(exception.what());
        EXPECT_FALSE(errorMessage.empty());
    }
}
