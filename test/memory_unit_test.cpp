/**
 * Memory assert tests.
 */

#include <cpu_lib/memory.hpp>
#include "gtest/gtest.h"

using namespace cpu_lib;

TEST(MemoryUnitTest, valid_set_get)
{
    Memory<uint32_t, 256> memory;
    memory.set(0x00, 0x12);
    EXPECT_EQ(static_cast<uint32_t>(0x12), memory.get(0x00));
}