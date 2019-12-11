/**
 * Memory assert tests.
 */

#include <cpu_lib/memory.hpp>
#include "gtest/gtest.h"

using namespace cpu_lib;

/**
 * @brief Simple test for verifying get and set work properly.
 */
TEST(MemoryUnitTest, valid_get_and_set)
{
    Memory<uint32_t, 256> memory;
    memory.set(0x00, 0x12);
    ASSERT_EQ(static_cast<uint32_t>(0x12), memory.get(0x00));
}

/**
 * @brief Test designed to throw std::out_of_range("Memory::set() : address is out of range.") in order to pass.
 */
TEST(MemoryUnitTest, invalid_set)
{
    Memory<uint32_t, 256> memory;
    try {
        memory.set(256, 0x00);
        FAIL() << "Expected std::out_of_range.";
    }
    catch(std::out_of_range const & err) {
        ASSERT_EQ(err.what(),std::string("Memory::set() : address is out of range."));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range.";
    }
}

/**
 * @brief Test designed to throw std::out_of_range("Memory::get() : address it out of range.") in order to pass.
 */
TEST(MemoryUnitTest, invalid_get)
{
    Memory<uint32_t, 256> memory;
    try {
        auto tempVal = memory.get(256);
        FAIL() << "Expected std::out_of_range.";
    }
    catch(std::out_of_range const & err) {
        ASSERT_EQ(err.what(),std::string("Memory::get() : address it out of range."));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range.";
    }
}

TEST(MemoryUnitTest, size)
{
    Memory<uint32_t, 256> mem1;
    Memory<uint8_t, 128> mem2;
    Memory<unsigned , 1000> mem3;
    ASSERT_EQ(256, mem1.size())     << "Expected mem1.size() to be 256.";
    ASSERT_EQ(128, mem2.size())     << "Expected mem2.size() to be 128.";
    ASSERT_EQ(1000, mem3.size())    << "Expected mem3.size() to be 1000.";

    // uncomment this line to test static_assert. Program should fail to compile. 
    //Memory<unsigned, 0> mem4;
}


