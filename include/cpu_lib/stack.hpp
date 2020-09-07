#ifndef _STACK_H_
#define _STACK_H_

#include <algorithm>
#include <array>
#include <stack>
#include <stdexcept>

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
 * @tparam Size            Depth of stack. If it's 16 bytes, then you'd use 16 for s and uint8_t for StackType.
 */
template <class StackType, std::size_t SizeLimit>
class Stack {
public:
    /**
     * SizeLimit can neber be 0 or less.
     */
    static_assert(SizeLimit > 0, "In class Stack, template-parameter SizeLimit must be greater than 0.");
    
    /**
     * @brief Removes the top element of the stack.
     */
    void pop();

    /**
     * @return Top element of stack without removing it.
     */
    [[nodiscard]] auto top() const;

    /**
     * @brief Pushes \p val to stack.
     */
    void push(const StackType val);

    /**
     * @return Size of stack, template parameter SizeLimit
     */
    [[nodiscard]] auto sizeLimit() const { return SizeLimit; }

    /**
     * @return Size of the underlying stack container.
     */ 
    [[nodiscard]] auto sizeUsed() const { return stack.size(); }

protected:
    /**
     * Stack
     */
    std::stack<StackType> stack;
}; // end class Stack

template <class StackType, std::size_t SizeLimit>
void Stack<StackType, SizeLimit>::pop()
{
    if ( this->sizeUsed() == 0) {
        throw std::out_of_range("Stack::pop() : stack is empty. Cannot pop stack.");
    }
    stack.pop();
}

template <class StackType, std::size_t SizeLimit>
auto Stack<StackType, SizeLimit>::top() const
{
    if (this->sizeUsed() == 0) {
        throw std::out_of_range("Stack::top() : stack is empty. Cannot get top.");
    }
    return stack.top();
}

template <class StackType, std::size_t SizeLimit>
void Stack<StackType, SizeLimit>::push(const StackType val)
{
    if (( this->sizeUsed() + 1) > SizeLimit) {
        throw std::out_of_range("Stack::push() : pushed more than SizeLimit.");
    }
    stack.push(val);
}
} // end namespace cpu_lib
#endif