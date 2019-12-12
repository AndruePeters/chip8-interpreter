
/** @file register.hpp
 * 
 * @author Andrue Peters
 * @date 10/08/19
 * @brief Register template for use within a CPU.
 * 
 * This defines class Register which emulates a CPU register.
 */

#ifndef _REGISTER_HPP_
#define _REGISTER_HPP_

#include <algorithm>
#include <array>

namespace cpu_lib {

/**
 * @class Register
 * 
 * @brief Emulates an internal register for a computer. 
 * 
 * @tparam  RegType Should be an unsigned integral type representing
 *          the bitwidth for the register. For example, if the register 
 *          is 8-bits wide then use uint8_t. If it's 32 bits wide, then use uint32_t.
 *          Will be enforced with concepts in the future.
 * 
 * @tparam  Size   The number of registers. If this register needs 16 registers, then this would be 16.
 * 
 * Size of memory is sizeof(MemType) * s

 * 
 */
template <class RegType, std::size_t Size>
class Register {
public:
    /**
     * Size can never be 0 or less.
     */
    static_assert(Size > 0, "In class Memory, template-parameter Size must be greater than 0.");
    
    /**
     * @brief Returns the value stored in register regNum.
     * @return Returns value stored in \p regNum
     * 
     * @param regNum register to lookup.
     * 
     * @throw std::out_of_range() if \p regNum is greater than or equal to template-parameter \p s
     */
    [[nodiscard]] constexpr auto get(const RegType regNum) const;

    /**
     * @brief Sets the register \p regNum to \p val . 
     * 
     * @param regNum register to lookup
     * @param val Values to store in \p regNum
     * 
     * @throw std::out_of_range() if regNum is greater than or equal to template-parameter \p s
     */
    constexpr void set(const RegType regNum, const RegType val);

    /**
     * @return Returns the given size from \p s.
     */
    [[nodiscard]] constexpr auto size() const { return Size; }
    
protected:

    /**
     * Represents the internal register.
     */
    std::array<RegType, Size> reg;
}; // end class Register

template <class RegType, std::size_t s>
constexpr auto Register<RegType, s>::get(const RegType regNum) const
{
    if (regNum >= this->size()) { throw std::out_of_range("Register::get() : register does not exist."); }
    return reg[regNum];
}

template <class RegType, std::size_t s>
constexpr void Register<RegType, s>::set(const RegType regNum, const RegType val)
{
    if (regNum >= this->size()) { throw std::out_of_range("Register::set() : register does not exist."); }
    reg[regNum] = val;
}

} // end namespace cpu_lib
#endif