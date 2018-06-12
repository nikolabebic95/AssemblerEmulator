org 0x0
.rodata.0
    dd stack - 4
    dd 4 dup dummy
    dd keyboard_interrupt
    dd 26 dup dummy

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
    jmp _start

print_string:
    loadub r1, [r0]
    jz r1, skip
    store r1, out
    load r1, #1
    add r0, r0, r1
    jmp print_string
skip:
    ret;

keyboard_interrupt:
    loadub r2, in
    loadub r3, quit_char
    sub r4, r2, r3
    jz r4, end
    load r0, #keyboard_hit_string
    call print_string
    storeb r2, out
    load r0, #crlf_string
    call print_string
    ret
end:
    load r0, #0
    int r0

.rodata.1
keyboard_hit_string:
    DB 'H'
    DB 'i' 
    DB 't' 
    DB ':' 
    DB ' ' 
    DB 0

crlf_string:
    DB 10
    DB 13
    DB 0

quit_char:
    DB 'q'