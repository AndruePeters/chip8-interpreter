/**
 * Register assert tests.
 */

#include <cpu_lib/register.hpp>
#include "gtest/gtest.h"

using namespace cpu_lib;

/**
 * @brief Simple test for verifying get and set work properly.
 */
TEST(RegisterUnitTest, valid_get_and_set)
{
    Register<uint32_t, 256> reg;
    reg.set(0x00, 0x12);
    ASSERT_EQ(static_cast<uint32_t>(0x12), reg.get(0x00));
}

/**
 * @brief Test designed to throw std::out_of_range("Register::set() : register is out of range.") in order to pass.
 */
TEST(RegisterUnitTest, invalid_set)
{
    Register<uint32_t, 256> reg;
    try {
        reg.set(256, 0x00);
        FAIL() << "Expected std::out_of_range.";
    }
    catch(std::out_of_range const & err) {
        ASSERT_EQ(err.what(),std::string("Register::set() : register does not exist."));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range.";
    }
}

/**
 * @brief Test designed to throw std::out_of_range("Register::get() : register it out of range.") in order to pass.
 */
TEST(RegisterUnitTest, invalid_get)
{
    Register<uint32_t, 256> reg;
    try {
        [[maybe_unused]] auto tempVal = reg.get(256);
        FAIL() << "Expected std::out_of_range.";
    }
    catch(std::out_of_range const & err) {
        ASSERT_EQ(err.what(),std::string("Register::get() : register does not exist."));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range.";
    }
}


/**
 * @brief Tests that the size passed in is correct.
 * Uncomment the lines in the test to force a compile time error.
 */
TEST(RegisterUnitTest, size)
{
    Register<uint32_t, 256> reg1;
    Register<uint8_t, 128> reg2;
    Register<unsigned , 1000> reg3;
    ASSERT_EQ(256, reg1.size())     << "Expected reg1.size() to be 256.";
    ASSERT_EQ(128, reg2.size())     << "Expected reg2.size() to be 128.";
    ASSERT_EQ(1000, reg3.size())    << "Expected reg3.size() to be 1000.";

    // uncomment this line to test static_assert. Program should fail to compile. 
    //Register<unsigned, 0> reg4;
}


