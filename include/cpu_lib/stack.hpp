#ifndef _STACK_H_
#define _STAKE_H_

#include <algorithm>
#include <array>
#include <stack>

namespace cpu_lib {

template <class StackType, std::size_t s>
class Stack {
public:
    [[nodiscard]] constexpr auto pop();
    [[nodiscard]] constexpr auto peek() const;
    void constexpr push(const StackType val);
    [[nodiscard]] constexpr auto size() const {return s;}
protected:
    std::stack<StackType> stack;
}; // end class Stack

template <class StackType, std::size_t s>
constexpr auto Stack<StackType, s>::pop()
{
    return stack.front();
}

template <class StackType, std::size_t s>
constexpr auto Stack<StackType, s>::peek() const
{
    auto x = stack.front();
    stack.pop_front();
    return x;
}

template <class StackType, std::size_t s>
constexpr void Stack<StackType, s>::push(const StackType val)
{
    stack.push_front(val);
}





} // end namespace cpu_lib
#endif