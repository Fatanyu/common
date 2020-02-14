#include <gtest/gtest.h>
#include <exceptions/Exception.hpp>

TEST(Exception, Constructor)
{
    EXPECT_NO_THROW(fatanyu::Exception customException("Somethings is wrong"));
    EXPECT_NO_THROW(fatanyu::Exception customException2("Somethings is wrong", {}));
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

    try
    {
        throw fatanyu::Exception("Somethings is wrong", {});
    }
    catch (std::exception &exception)
    {
        std::string errorMessage(exception.what());
        EXPECT_FALSE(errorMessage.empty());
    }
}

TEST(Exception, Message)
{
    const std::string errorMessage = "Here we have some error to solve.";
    try
    {
        throw fatanyu::Exception(errorMessage.c_str());
    }
    catch (std::exception &exception)
    {
        std::string raisedErrorMessage(exception.what());
        ASSERT_NE(raisedErrorMessage.find(errorMessage), std::string::npos);
    }
}
