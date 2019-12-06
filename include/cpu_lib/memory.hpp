#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <algorithm>
#include <array>


namespace cpu_lib {

template <typename MemType, class MemCont  = std::array<W>>
class Memory {
public:
    auto get(const MemType address) const;
    void set(MemType address, auto const val);
    void dump() const;
protected:
    MemCont<MemType> memory;
}; // end class Memory

} // end namespace cpu_lib

#endif