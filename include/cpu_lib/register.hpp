#ifndef _REGISTER_HPP_
#define _REGISTER_HPP_

#include <algorithm>
#include <array>

namespace cpu_lib {

template <typename RegType, class RegCont = std::array<W>>
class Register {
public:
    auto get(const W address) const;
    void set(W address, auto const val);
    void dump() const;
protected:
    RegCont<RegType> register;
}; // end class Register

} // end namespace cpu_lib
#endif