#ifndef _STACK_H_
#define _STAKE_H_

#include <algorithm>
#include <array>
#include <stack>

namespace cpu_lib {


/**
 * @class Stack
 * @brief Represents internal CPU stack. 
 * 
 * @tparam StackType    Should be unsigned integral type representing
 *                      the stack bitwidth. For example, if the stack consists
 *                      of slots 8-bits wide, then use uint8_t.
 *                      Will convert to a static size in the future.
 * 
 * @tparam s            Depth of stack. If it's 16 bytes, then you'd use 16 for s and uint8_t for StackType.
 */
template <class StackType, std::size_t s>
class Stack {
public:
    /**
     * @return Returns and removes top element of stack.
     */
    [[nodiscard]] constexpr auto pop();

    /**
     * @return Top element of stack without removing it.
     */
    [[nodiscard]] constexpr auto peek() const;

    /**
     * @brief Pushes \p val to stack.
     */
    void constexpr push(const StackType val);

    /**
     * @return Size of stack, template parameter s
     */
    [[nodiscard]] constexpr auto size() const {return s;}
    
protected:
    /**
     * Stack
     */
    std::stack<StackType> stack;
}; // end class Stack

template <class StackType, std::size_t s>
constexpr auto Stack<StackType, s>::pop()
{
    auto front = stack.front();
    stack.pop_front();
    return front;
}

template <class StackType, std::size_t s>
constexpr auto Stack<StackType, s>::peek() const
{
    return stack.front();
}

template <class StackType, std::size_t s>
constexpr void Stack<StackType, s>::push(const StackType val)
{
    stack.push_front(val);
}





} // end namespace cpu_lib
#endif