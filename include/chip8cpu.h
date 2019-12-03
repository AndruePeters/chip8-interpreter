#ifndef _CHIP8_CPU_H_
#define _CHIP8_CPU_H_

#include <array>
#include <stack>
#include <cstdint>


namespace CHiP8 {


class cpu {

    std::array<uint8_t, 4096> ram_;
    std::array<uint8_t, 16> registers_;
    uint16_t address_register_;
    std::stack<uint16_t> call_stack_;



};





}
#endif