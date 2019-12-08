#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <algorithm>
#include <array>


namespace cpu_lib {
template <class MemType, std::size_t s>
class Memory {
public:
    [[nodiscard]] constexpr auto get(const MemType address) const ;
    void constexpr set(MemType address, MemType val);
    [[nodiscard]] auto constexpr size() const { return memory.size(); }

protected:
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