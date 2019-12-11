/**
 * Memory assert tests.
 */

#include <cpu_lib/memory.hpp>
#include "gtest/gtest.h"

using namespace cpu_lib;

TEST(MemoryUnitTest, valid_get_and_set)
{
    Memory<uint32_t, 256> memory;
    memory.set(0x00, 0x12);
    EXPECT_EQ(static_cast<uint32_t>(0x12), memory.get(0x00));
}

TEST(MemoryUnitTest, invalid_set)
{
    Memory<uint32_t, 256> memory;
    try {
        memory.set(256, 0x00);
        FAIL() << "Expected std::out_of_range.";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Memory::set() : address is out of range."));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range.";
    }
}

TEST(MemoryUnitTest, invalid_get)
{
    Memory<uint32_t, 256> memory;
    try {
        auto tempVal = memory.get(256);
        FAIL() << "Expected std::out_of_range.";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Memory::get() : address it out of range."));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range.";
    }
}


