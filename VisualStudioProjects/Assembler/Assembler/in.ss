org 0x0
.rodata.0
    dd stack - 4
    dd 31 dup dummy

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

org 0x500
.text.1
.global _start
_start:
    load r0, #0
    load r1, #buffer
    call $number_to_string
    load r0, #buffer
    call $print_string
    load r0, #crlf_string
    call $print_string
    load r0, #0
    int r0

// R0 contains the number that should be converted
// R1 contains the destination
number_to_string:
    load r5, r1
    load r2, #10
    load r4, #1
    load r6, #'0'
loop_number_to_string:
    mod r3, r0, r2
    add r3, r3, r6
    storeb r3, [r5]
    add r5, r5, r4 ; r1++
    div r0, r0, r2
    jnz r0, $loop_number_to_string
    load r3, #0
    storeb r3, [r5]
    load r0, r1
    sub r1, r5, r1
    call $reverse
    ret

// R0 contains the address
// R1 contains the length
reverse:
    add r1, r0, r1
    load r2, #1
    sub r1, r1, r2
loop_reverse:
    loadub r3, [r0]
    loadub r4, [r1]
    storeb r3, [r1]
    storeb r4, [r0]
    add r0, r0, r2
    sub r1, r1, r2
    sub r3, r1, r0
    jgz r3, $loop_reverse
    ret

print_string:
    load r2, #1
loop_print_string:
    loadub r1, [r0]
    jz r1, $skip_print_string
    store r1, out
    add r0, r0, r2
    jmp $loop_print_string
skip_print_string:
    ret


.bss.1
buffer:
    db 0x10 dup ?

.rodata.1
crlf_string:
    db 13
    db 10
    db 0
