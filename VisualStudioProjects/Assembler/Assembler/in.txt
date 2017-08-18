org 0x0
.rodata.0
    dd stack - 4
    dd 3 dup dummy
    dd timer_interrupt
    dd 27 dup dummy

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
    load r2, #0
loop:
    jmp loop

print_string:
    loadub r1, [r0]
    jz r1, skip
    store r1, out
    load r1, #1
    add r0, r0, r1
    jmp print_string
skip:
    ret;

timer_interrupt:
    load r3, #1
    add r2, r2, r3
    load r3, #10
    mod r3, r2, r3
    jnz r3, skip_2
    load r3, #100
    mod r3, r2, r3
    jz r3, end
    load r3, #1
    loadub r4, print_time
    add r4, r4, r3
    storeb r4, print_time
    load r0, #timer_string
    call print_string
    load r0, #print_time
    call print_string
skip_2:
    ret
end:
    load r0, #0
    int r0

.data.1
print_time:
    DB '0'
    DB 10
    DB 13
    DB 0
    DB 0

.rodata.1
timer_string:
    DB 'T'
    DB 'i'
    DB 'm'
    DB 'e'
    DB ':'
    DB ' '
    DB 0
