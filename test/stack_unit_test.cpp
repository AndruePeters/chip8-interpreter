/**
 * Memory assert tests.
 */

#include <cpu_lib/stack.hpp>
#include <iostream>
#include "gtest/gtest.h"

using namespace cpu_lib;

/**
 * @brief Stack kind of has to have all of these 
 */
TEST(StackUnitTest, stack_push_pop_peek_size)
{
    const unsigned stackLimit = 5;
    Stack<unsigned, stackLimit> stack1;
    
    // make sure defaults are correct
    ASSERT_EQ(0, stack1.sizeUsed());
    ASSERT_EQ(stackLimit, stack1.sizeLimit());

    // now add 1 element
    stack1.push(0);
    ASSERT_EQ(1, stack1.sizeUsed());
    ASSERT_EQ(stackLimit, stack1.sizeLimit());

    // now push all the way up to the lmit
    for (unsigned i = 1; i < stackLimit; ++i)
    {
        stack1.push(i);
        ASSERT_EQ(stackLimit, stack1.sizeLimit());
        ASSERT_EQ(i+1, stack1.sizeUsed());
    }

    // now check sizes
    ASSERT_EQ(stackLimit, stack1.sizeLimit());
    ASSERT_EQ(stackLimit, stack1.sizeUsed());

    // now pop all elements
    for (unsigned i = stackLimit; i > 0 ; --i)
    {
        ASSERT_EQ(stackLimit, stack1.sizeLimit());
        ASSERT_EQ(i, stack1.sizeUsed());
        stack1.pop();
    }

    
}

/**
 * @brief Force stack to throw when popping after stack is empty
 */
TEST(StackUnitTest, pop_throw)
{
    const int stackLimit = 500;
    Stack<int, stackLimit> stack;
    try {
        // push a lot
        for (int i = 0; i < stackLimit; ++i) {
            stack.push(i);
        }

        // pop a lot
        for (int i = 0; i < stackLimit; ++i) {
            stack.pop();
        }

        // this pop should throw the exception
        stack.pop();
    } catch(std::out_of_range const& err) {
        ASSERT_EQ(err.what(), std::string("Stack::pop() : stack is empty. Cannot pop stack."));
        
        // make sure the sizes are correct
        ASSERT_EQ(0, stack.sizeUsed());
        ASSERT_EQ(stackLimit, stack.sizeLimit());
    } catch(...) {
        FAIL() << "Expected std::out_of_range.";
    }
}

/**
 * @brief Force stack to throw exception when pushing more than allotted
 */
TEST(StackUnitTest, push_throw)
{
    const int stackLimit = 500;
    Stack<uint32_t, stackLimit> stack;
    try {
        // push up until the breaking point
        for (unsigned i = 0; i < stackLimit; ++i) {
            stack.push(i);
        }
        stack.push(stackLimit); /// < this should cause it to throw
    } catch (std::out_of_range const& err) {
        ASSERT_EQ(err.what(), std::string("Stack::push() : pushed more than SizeLimit."));

        // make sure the sizes are correct
        ASSERT_EQ(stackLimit, stack.sizeUsed());
        ASSERT_EQ(stackLimit, stack.sizeLimit());
    } catch (...) {
        FAIL() << "Expected std::out_of_range.";
    }
}


/**
 * @brief Force stack to throw when popping after stack is empty
 */
TEST(StackUnitTest, top_throw)
{
    const int stackLimit = 500;
    Stack<int, stackLimit> stack;
    try {
        // push a lot
        for (int i = 0; i < stackLimit; ++i) {
            stack.push(i);
        }

        // pop a lot
        for (int i = 0; i < stackLimit; ++i) {
            [[maybe_unused]] auto top = stack.top();
        }

        // make sure it didn't throw earlier
        ASSERT_EQ("Hasn't thrown yet.", "Hasn't thrown yet.");
        
        // this pop should throw the exception
        [[maybe_unused]] auto top = stack.top();
    } catch(std::out_of_range const& err) {
        ASSERT_EQ(err.what(), std::string("Stack::top() : stack is empty. Cannot get top."));
        
        // make sure the sizes are correct
        ASSERT_EQ(0, stack.sizeUsed());
        ASSERT_EQ(stackLimit, stack.sizeLimit());
    } catch(...) {
        FAIL() << "Expected std::out_of_range.";
    }
}