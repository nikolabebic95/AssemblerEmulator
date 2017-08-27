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

.global _start
_start:
    loadub r1, $x
    store r1, out
    jnz r1, $next
    store r1, out
    store r1, out
    jmp end
next:
    loadub r1, #'x'
    store r1, out
end:
    loadub r1, #10
    store r1, out
    loadub r1, #13
    store r1, out
    load r1, #0
    int r1

.rodata.1
    db '1'
    db '2'
    db '3'
    db '4'
x:
    db '5'
    db '6'
    db '7'
    db '8'
    db '9'
