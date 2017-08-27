org 0x0
.rodata.0
    dd stack - 4
    dd 2 dup dummy
    dd error_interrupt
    dd 28 dup dummy

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
    load r0, #0
    store r0, illegal_write

print_string:
    loadub r1, [r0]
    jz r1, skip
    store r1, out
    load r1, #1
    add r0, r0, r1
    jmp print_string
skip:
    ret;

error_interrupt:
    load r0, #error_string
    call print_string
    load r0, #0
    int r0

.rodata.1
error_string:
    DB 'E'
    DB 'r'
    DB 'r'
    DB 'o'
    DB 'r'
    DB ' '
    DB 'i'
    DB 'n'
    DB 't'
    DB 'e'
    DB 'r'
    DB 'r'
    DB 'u'
    DB 'p'
    DB 't'
    DB ' '
    DB 'r'
    DB 'o'
    DB 'u'
    DB 't'
    DB 'i'
    DB 'n'
    DB 'e'
    DB 13
    DB 10
    DB 0

.rodata.2
illegal_write:
    dd 0
