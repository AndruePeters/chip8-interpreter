#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <algorithm>
#include <array>


namespace cpu_lib {

/**
 * @class Memory
 * @brief Represents random access memory for a CPU.
 * 
 * @tparam  MemType  Represents the bitwidth of the memory. If it's 8-bits then use uint8_t.
 *                  Also determines arguments for parameters.
 * 
 * @param   s Size of memory to be made.
 * 
 * Size of memory is sizeof(MemType) * s
 */
template <class MemType, std::size_t s>
class Memory {
public:

    /**
     * @brief Returns the value stored in address.
     * @return Returns value stored in \p address
     * 
     * @param address Memory address to lookup.
     * 
     * @throw std::out_of_range() if \p address is greater than or equal to template-parameter \p s
     */
    [[nodiscard]] constexpr auto get(const MemType address) const ;

    /**
     * @brief Sets the register \p address to \p val . 
     * 
     * @param address Memory address to lookup.
     * @param val Values to store in \p address
     * 
     * @throw std::out_of_range() if \p address is greater than or equal to template-parameter \p s
     */
    void constexpr set(MemType address, MemType val);

    /**
     * @return  The number of memory cells to create.
     */
    [[nodiscard]] auto constexpr size() const { return memory.size(); }

protected:

    /**
     * Represents internal memory.
     */
    std::array<MemType, s> memory;
};

template <class MemType, std::size_t s>
constexpr auto Memory<MemType, s>::get(const MemType address) const  {
    if (address >= this->size()) { throw std::out_of_range("Memory::get() : address it out of range."); }
    return memory[address];
}

template <class MemType, std::size_t s>
void constexpr Memory<MemType, s>::set(MemType address, MemType val){
    if (address >= this->size()) { throw std::out_of_range("Memory::set() : address is out of range"); }
    memory[address] = val;
}


} // end namespace cpu_lib

#endif