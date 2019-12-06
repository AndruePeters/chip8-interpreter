#ifndef _STACK_H_
#define _STAKE_H_

#include <algorithm>
#include <array>

namespace cpu_lib {

template <typename StackType, class StackCont = std::array<W>>
class Stack {
public:
    auto pop() const;
    auto peek() const;
    void push(auto const val);
    void dump() const;
protected:
    StackCont<StackType> stack;
}; // end class Stack

} // end namespace cpu_lib
#endif