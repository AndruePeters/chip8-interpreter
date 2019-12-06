#ifndef _CHIP8_CPU_H_
#define _CHIP8_CPU_H_

#include <array>
#include <stack>
#include <cstdint>


namespace chip8 {

template <RegisterWidth W, RegisterSize S>
class Register {

};

template <MemoryWidth W, MemorySize S>
class Memory {

};

template <StackWidth W, StackSize S>
class Stack {

};

enum class OPCodeMask: uint16_t {
    CLS = 0x00E0,
    RET = 00EE,
    GOTO = 0x1000,
    JMP_I = 0x2000,
    EQ_C = 0x3000,
    NEQ_C = 0x4000,
    EQ = 0x5000,
    SET_I = 0x6000,
    ADD_I = 0x7000,
    SET = 0x8000,
    OR = 0x8001,
    AND = 0x8002,
    XOR = 0x8003,
    ADD = 0x8004,
    SUB = 0x8005,
    SRL = 0x8006,
    SUB_R = 0x8007,
    SLL = 0x800E,

};

template <Reg R, Mem M, Stack S>
class cpu {

    std::array<uint8_t, 4096> ram_;
    std::array<uint8_t, 16> registers_;
    uint16_t address_register_;
    std::stack<uint16_t> call_stack_;



};





} // end namespace chip8
#endif