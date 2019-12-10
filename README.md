[![Build Status](https://travis-ci.org/AndruePeters/chip8-interpreter.svg?branch=master)](https://travis-ci.org/AndruePeters/chip8-interpreter)

# chip8-interpreter
Interpreter for Chip 8. First emulator using this resource: http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/

# Architecture
## Memory
    * 4096 (0x1000) 8-bit memory locations
    * Typically CHIP interpreter occupies the top 512 bytes
    * Uppermost 256 bytes (0xF00-0xFFF) are reserved for display refresh
    * (0xEA0-0xEFF) reserved for call stack.

## Regsiters
    * 16 8-bit registers named V0-VF.
    * VF is the carry flag in addition, no borrow flag in subtraction, draw instruction for pixel collision.
    * Address register, I, is 16-bits wide

## Stack
    * Only used to store return addresses when subroutines are called.
    * Original 1802 had 48 bytes for up to 24 levels of nesting

## Timers
    * Two timers that count down at 60 Hz
        * Delay Timer: Intended to be used for timing events of the games. Can be set and read.
        * Sound Timer: Used for sound effects. When value is nonzero, a beeping sound is made.

## Input
    * Hex Keyboard with 16 keys ranging from 0 to F.
    * '8', '4', '6', and '2' are typically used for directional input

## Audio and Graphics
    * Resolution: 64 * 32 monochrome
    * Sprites are 8 pixels wide and 1-15 pixels heigh
    * Sprite pixels are XOR'd with corresponding screen pixels.
    * VF is set if any screen pixels are flipped from set to unset when a sprite is drawn for collision detection.
    * Beeping sound is played when value of soudn timer is nonzero.

## Opcode Table
    * 35 two-byte opcodes stored in big-endian
    * NNN: address
    * NN: 8-bit constant
    * N: 4-bit constant
    * X and Y: 4-bit register identifier
    * PC: program counter
    * I: 16-bit register (for memory address)
    * VN: One of 16 available variables. N may be 0 to F.

| Opcode   | Type   | C Pseudo             | Explanation  |
|----------|--------|----------------------|---|
| 0NNN     | Call   |                      | Calls RCA 1802 program at address NNN. Not necessary for most ROMS.   |
| 00E0     | Disp   | disp_clear()         | Clears the screen.  |
| 00EE     | Flow   | return;              | Returns from a subroutine  |
| 1NNN     | Flow   | goto NNN;            | Jumps to address NNN.  |
| 2NNN     | Flow   | *(0xNNN)()           | Calls subroutine at NNN.  |
| 3XNN     | Cond   | if (VX == NN)        | Skips the next instructions if VX equal NN.  |
| 4XNN     | Cond   | if (VX != NN)        | Skips the next instruction if VX doesn't equal NN.  |
| 5XY0     | Cond   | if (VX == VY)        | Skips the next instruction iv VX equals VY.  |
| 6XNN     | Const  | VX = NN              | Sets VX to NN.  |
| 7XNN     | Const  | VX += NN             | Adds NN to VX. (Carry flag is not changed)  |
| 8XY0     | Assign | VX = VY              | Sets VX to the value of VY.  |
| 8XY1     | BitOp  | VX = VX \| VY        | Sets VX to VX OR VY.  |
| 8XY2     | BitOp  | VX = VX & VY         | Sets VX to VX AND VY.  |
| 8XY3     | BitOp  | VX = VX ^ VY         | Sets VS to VX XOR VY.  |
| 8XY4     | Math   | VX += VY             | Adds VY to VX. VF is set to 1 when there's a carry, 0 otherwise.  |
| 8XY5     | Math   | VX -= VY             | VY is subtracted from VX. VF is 0 when there's a borrow. 1 otherwise.  |
| 8XY6     | BitOp  | VX >> = 1            | Stores the LSB of VX in VF and then shifts VX right by 1.  |
| 8XY7     | Math   | VX = VY - VX         | Sets VS to VY - VX. VF is 0 when there's a borrow. 0 otherwise.  |
| 8XYE     | BitOp  | VX << = 1            | Stores MSB of VX in VF and then shifts VX left by 1.  |
| 9XY0     | Cond   | if (VX != VY)        | Skips next instruction if VX doesn't equal VY.  |
| ANNN     | MEM    | I = NNN              | Sets I to the address NNN.  |
| BNNN     | Flow   | PC = V0 + NNN        | Jumps to the address NNN plus V0.  |
| CXNN     | Rand   | VX = rand() & NN;    | Sets VX to result of a bitwise AND operation on a random number (0 to 255).   |
| DXYN     | Disp   | draw (VX, VY, N)     | Draws a sprite at coordinate (VX, VY) with width of 9 pixels an dheight of N pixels. Each row of 8 pixels is read a bit-coded starting from memory location I. I value doesn't changer after the execution of this instrucitons. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn and 0 if that doesn't happen.  |
| EX9E     | KeyOp  | if (key() == VX)     | Skips the next instruction if the key stored in VX is pressed.  |
| EXA1     | KeyOp  | if (key() != VX)     | Skips the next instruction if the key storedin VX isn't pressed.  |
| FX07     | Timer  | VX = get_delay()     | Sets VX to the value of the delay timer.  |
| FX0A     | KeyOp  | VX = get_key()       | A key press is awaited, and then stored in VX. (blocking operation. All instructions halted until next key event).  |
| FX15     | Timer  | delay_timer(VX)      | Sets the delay timer to VX.  |
| FX18     | Sound  | sound_timer(VX)      | Sets the sound timer to VX.  |
| FX1E     | MEM    | I += VX              | Adds VX to I.  |
| FX29     | MEM    | I = sprite_addr[VX]  | Sets I to the location of the sprite for the character in VX. Characters 0-F are represented by 4x5 font.  |
| FX33     | BCD    | set_BCD(VX)          | Stores BCD representation of VX. For number 123, 1 is stored at I, 2 is stored at I+1, and 3 is stored at I+2. |
| FX55     | MEM    | reg_dump(VX, &I)     | Stores V0 to VX in memory starting address I. Offset from I is incrased by 1 for each value written, but I itself is not modified.  |
| FX65     | MEM    | reg_load(VX, &I)     | Fills V0 to VX with values from memory starting at address I. The offset from I is incrased by 1 for each value written, but I itself is not modified.  |
