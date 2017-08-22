# AssemblerEmulator

**System software**

**School of Electrical Engineering**

**University of Belgrade**

**Copyright © 2017 Nikola Bebić**

## Quick Start

This is a school project for the system software class. The purpose of the project is to write the assembler for the MicroRISC language and the emulator which would execute the programs produced by the assembler.

## Installation

Just run the `build.sh` script and everything should be ready to go

## Usage

Run the `run.sh` script with the -f option with the name of the `.ss` input file. The script will run the assembler with the input file, generate the output file, and run the emulator with that output file.

Example:

`run.sh -f helloworld.ss`

Input file:
```
org 0x0
.rodata.0
    dd stack - 4
    dd print_string_interrupt
    dd 30 dup dummy

org 128
.data.0
out: 
    dd 0
in: 
    dd 0 

.bss
stack: 
    DW 0x100 DUP ?

.text
dummy: ret

.global _start
_start:
    call hello
    load r0, #0
    int r0

PRINT_STRING_INTERRUPT def 1

hello:
    load r0, #hello_string
    load r15, #PRINT_STRING_INTERRUPT
    int r15 ; calls print_string_interrupt
    ret

print_string:
    loadub r1, [r0]
    jz r1, skip
    store r1, out
    load r1, #1
    add r0, r0, r1
    jmp print_string
skip:
    ret;

print_string_interrupt:
    call print_string
    ret 

.rodata.1
hello_string:
    DB 'H'
    DB 'e' 
    DB 'l' 
    DB 'l' 
    DB 'o' 
    DB ',' 
    DB ' ' 
    DB 'W' 
    DB 'o' 
    DB 'r' 
    DB 'l' 
    DB 'd' 
    DB '!' 
    DB 10 ; CR
    DB 13 ; LF
    DB 0  ; end of string

```

Output:
```
Hello, World!
```

## MicroRISC Specification

### Architecture

32-bit RISC processor

32-bit virtual address space, addressable unit - byte, little-endian

No floating point arithmetic

### Registers

16 32-bit general purpose registers, `R0` - `R15`

32-bit program counter: `PC`

32-bit stack pointer: `SP`. Stack grows towards higher addresses, stack pointer points to the word at the top of the stack

### Constant terms

Constant terms can containt the following:
* Literals
* Arithmetic operators (+, -, *, /)
* Subexpressions with parentheses

Literals are signed decimal, binary or hexadecimal integers, or ASCII characters, as well as named constants or labels

Labels can can contain letters, digits, and symbol `_`, and can not start with a letter

There is a predefined symbol `$`, which represents the address of the current instruction

### Address modes

* Immediate: ```#constant_term```
* Register direct: ```Ri```
* Register indirect: ```[Ri]```
* Register indirect with offset: ```[Ri + offset]```. ```offset``` is a constant term
* PC relative: ```$constant_term```. This is treated as register indirect with offset. Constant term must contain at least one label

### Instructions

Instruction format:

`[label:] instruction [operand0, operand1, operand2] [; comment]`

#### Flow control instructions

<table>
    <tr>
        <td><i><b>Instruction</b></i></td>
        <td><i><b>Address modes</b></i></td>
        <td><i><b>Comment</b></i></td>
    </tr>
    <tr>
        <td><code>INT op</code></td>
        <td>Register direct</td>
        <td>Generates a software interrupt. Interrupt entry is in the register</td>
    </tr>
    <tr>
        <td><code>JMP op</code></td>
        <td>Memory direct, register indirect, register indirect with offset</td>
        <td>Jumps to given address</td>
    </tr>
    <tr>
        <td><code>CALL op</code></td>
        <td>Memory direct, register indirect, register indirect with offset</td>
        <td>Calls a subroutine. <code>PC</code> is pushed to the stack</td>
    </tr>
    <tr>
        <td><code>RET</code></td>
        <td>None</td>
        <td>Returns from subroutine</td>
    </tr>
    <tr>
        <td><code>JZ reg, op</code></td>
        <td><code>reg</code>: Register direct, <code>op</code>: Memory direct, register indirect, register indirect with offset</td>
        <td>Jumps to <code>op</code> if <code>reg == 0</code></td>
    </tr>
    <tr>
        <td><code>JNZ reg, op</code></td>
        <td><code>reg</code>: Register direct, <code>op</code>: Memory direct, register indirect, register indirect with offset</td>
        <td>Jumps to <code>op</code> if <code>reg != 0</code></td>
    </tr>
    <tr>
        <td><code>JGZ reg, op</code></td>
        <td><code>reg</code>: Register direct, <code>op</code>: Memory direct, register indirect, register indirect with offset</td>
        <td>Jumps to <code>op</code> if <code>reg > 0</code></td>
    </tr>
    <tr>
        <td><code>JGEZ reg, op</code></td>
        <td><code>reg</code>: Register direct, <code>op</code>: Memory direct, register indirect, register indirect with offset</td>
        <td>Jumps to <code>op</code> if <code>reg >= 0</code></td>
    </tr>
    <tr>
        <td><code>JLZ reg, op</code></td>
        <td><code>reg</code>: Register direct, <code>op</code>: Memory direct, register indirect, register indirect with offset</td>
        <td>Jumps to <code>op</code> if <code>reg < 0</code></td>
    </tr>
    <tr>
        <td><code>JLEZ reg, op</code></td>
        <td><code>reg</code>: Register direct, <code>op</code>: Memory direct, register indirect, register indirect with offset</td>
        <td>Jumps to <code>op</code> if <code>reg < 0</code></td>
    </tr>
</table>

### Load/Store instructions

Load, sizes of operands:
* Unsigned byte, suffix: `UB`
* Signed byte, suffix: `SB`
* Unsigned word, suffix: `UW`
* Signed word, suffix: `SW`
* Double word, no suffix

Store, sizes of the operands:
* Byte, suffix: `B`
* Word, suffix: `W`
* Double word, no suffix

Size of word is 2 bytes, and size of double word is 2 words

<table>
    <tr>
        <td><i><b>Instruction</b></i></td>
        <td><i><b>Address modes</b></i></td>
        <td><i><b>Comment</b></i></td>
    </tr>
    <tr>
        <td><code>LOAD reg, op</code></td>
        <td><code>reg</code>: Register direct, <code>op</code>: All</td>
        <td>Loads the data into the register</td>
    </tr>
    <tr>
        <td><code>STORE reg, op</code></td>
        <td><code>reg</code>: Register direct, <code>op</code>: All except Immediate</td>
        <td>Stores the data from the register</td>
    </tr>
</table>

### Stack instructions

* 32-bit double word is always pushed to the stack, and popped from the stack

<table>
    <tr>
        <td><i><b>Instruction</b></i></td>
        <td><i><b>Address modes</b></i></td>
        <td><i><b>Comment</b></i></td>
    </tr>
    <tr>
        <td><code>PUSH reg</code></td>
        <td>Register direct</td>
        <td>Pushes the register to the stack</td>
    </tr>
    <tr>
        <td><code>STORE reg, op</code></td>
        <td>Register direct</td>
        <td>Pops the register from the stack</td>
    </tr>
</table>

### ALU instructions

* Work only on 32-bit operands
* Signed arithmetic

<table>
    <tr>
        <td><i><b>Instruction</b></i></td>
        <td><i><b>Address modes</b></i></td>
        <td><i><b>Comment</b></i></td>
    </tr>
    <tr>
        <td><code>ADD reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 + reg2</code></td>
    </tr>
    <tr>
        <td><code>SUB reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 - reg2</code></td>
    </tr>
    <tr>
        <td><code>MUL reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 * reg2</code></td>
    </tr>
    <tr>
        <td><code>DIV reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 / reg2</code></td>
    </tr>
    <tr>
        <td><code>MOD reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 % reg2</code></td>
    </tr>
    <tr>
        <td><code>AND reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 & reg2</code></td>
    </tr>
    <tr>
        <td><code>OR reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 | reg2</code></td>
    </tr>
    <tr>
        <td><code>XOR reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 ^ reg2</code></td>
    </tr>
    <tr>
        <td><code>NOT reg0, reg1</code></td>
        <td>Register direct</td>
        <td><code>reg0 = ~reg1</code></td>
    </tr>
    <tr>
        <td><code>ASL reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 << reg2</code></td>
    </tr>
    <tr>
        <td><code>ASR reg0, reg1, reg2</code></td>
        <td>Register direct</td>
        <td><code>reg0 = reg1 >> reg2</code></td>
    </tr>
</table>

### Data definition

Format:

`[label:] definition data_specifier [, ...] [; comment]`

Possible definitions:
* `DB` - defines a byte
* `DW` - defines a word
* `DD` - defines a double word

Data specifiers:

`constant_term [ DUP constant_term | ? ]`

* `DUP` - First constant term denotes how many times the second constant term will occur
* `?` - Undefined value

### Directives:

Named constant definition:

` symbol DEF constant_expression [; comment]`

Origin directive:

` ORG constant_expression [; comment]`

### Segments

* `.text[.number]` - section containing the program code
* `.data[.number]` - section containing initialized data
* `.rodata[.number]` - section containing read only data
* `.bss[.number]` - section containing uninitialized data

### Interrupts:

* IV table starts at the address 0 and has 32 entries
* During the interrupt execution, no hardware interrupt can happen
* Executing `INT 0` will end the program
* Entry 0 in the IVT contains the starting value of the stack pointer
* Entry 3 in the IVT contains the address of the error interrupt routine
* Entry 4 in the IVT contains the address of the timer interrupt routine. This routine is called every `0,1s`
* Entry 5 in the IVT contains the address of the keyboard interrupt routine. This routine is called every time a key is pressed

Two registers are mapped in the address space, right after the IV table. 

The first register is mapped to the address `128` and is the `stdout` register. Every time a value is written to this register, it will be written on the standard output stream

The second register is mapped to the address `132` and is the `stdin` register. Every time a keyboard interrupt happens, this register will contain the ASCII code of the hit character. The value can be read more than once. New interrupts will not happen until the value is read at least once

## Licence

MIT License

Copyright (c) 2017 Nikola Bebic

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
