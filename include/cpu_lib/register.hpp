#ifndef _REGISTER_HPP_
#define _REGISTER_HPP_

#include <algorithm>
#include <array>

namespace cpu_lib {

template <class RegType, std::size_t s>
class Register {
public:
    [[nodiscard]] constexpr auto get(const RegType regNum) const;
    constexpr void set(const RegType regNum, const RegType val);
    [[nodiscard]] constexpr auto size() const { return s; }
protected:
    std::array<RegType, s> reg;
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