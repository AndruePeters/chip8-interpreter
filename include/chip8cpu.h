#ifndef _CHIP8_CPU_H_
#define _CHIP8_CPU_H_

#include <array>
#include <cstdint>
#include <stack>

namespace chip8 {
    enum class OPCodeMask : uint16_t {
        CLS = 0x00E0,
        RET = 0x00EE,
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
        NEQ = 0x9000,
        SET_SP = 0xA000,
        JMP = 0xB000,
        RAND = 0xC000,
        DRAW = 0xD000,
        KEY_EQ = 0xE09E,
        KEY_NEQ = 0xE0A1,
        TMR_GET = 0xF007,
        KEY_GET = 0xF00A,
        TMR_SET = 0xF015,
        STMR_SET = 0xF018,
        PC_INC = 0xF01E,
        DRW_CHAR = 0xF029,
        BCD = 0xF033,
        MEM1 = 0xF055,
        MEM2 = 0xF065
    };


    class cpu {
        std::array<uint8_t, 4096> ram_;
        std::array<uint8_t, 16> registers_;
        uint16_t address_register_;
        std::stack <uint16_t> call_stack_;
    };
} // end namespace chip8
#endif