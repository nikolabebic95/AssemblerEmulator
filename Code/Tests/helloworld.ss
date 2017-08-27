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

.end 
