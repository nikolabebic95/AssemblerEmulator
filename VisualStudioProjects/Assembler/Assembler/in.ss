; ##########################################################
;
; Symbolic constants:
;
; ##########################################################

NUL def 0   ; String terminator
BS  def 8   ; Backspace
LF  def 10  ; Line feed
CR  def 13  ; Carriage return
DEL def 127 ; Delete

END_OF_PROGRAM def 0 ; End of program interrupt code

LEN def 50 ; Maximum possible length of the input string

; ##########################################################
;
; IV Table, mapped registers, stack:
;
; ##########################################################

; IV Table
; Starts at the address 0, has 32 entries
; Entry 0 contains the starting stack pointer
; Entry 3 contains the error interrupt routine
; Entry 4 contains the timer interrupt routine
; Entry 5 contains the keyboard interrupt routine
org 0
.rodata.0
    dd stack - 4            ; Initial value of the stack pointer.
                            ; Stack grows upwards. SP points to the top of the stack
    dd 2 dup dummy          ; Skip entries 1 and 2
    dd error_interrupt      ; Error interrupt routine
    dd timer_interrupt      ; Timer interrupt routine
    dd keyboard_interrupt   ; Keyboard interrupt routine
    dd 26 dup dummy         ; Skip the remaining 26 entries

; Output and input mapped registers
org 32 * 4
.data.0
out: 
    dd 0 ; Output register
in:
    dd 0 ; Input register

; Stack
.bss.0
stack: 
    DW 0x100 DUP ? ; Size of the stack is 0x100

; ##########################################################
;
; Code:
;
; ##########################################################

.text

; Main function
; Asks the user for the name, and outputs hello message
.global _start
_start:
    load r0, #input_message     ; Loads the input message address into R0 
    call $print_string          ; Calls print_string(input_message)
    load r0, #1                 ; Loads the true flag into R0
    store r0, active            ; Stores the active flag
loop:
    load r0, active             ; Loads the active
    jnz r0, $loop               ; Busy waits until flag is set to 0
    load r0, #hello_string      ; Loads hello_string address
    call $print_string          ; Calls print_string(hello_string)
    load r0, #input_string      ; Loads the input string address
    call $print_string          ; Calls print_string(input_string)
    load r0, #crlf_string       ; Loads the newline string 
    call $print_string          ; Calls print_string(crlf_string)
    call $print_time            ; Prints the duration of the program
    load r0, #0                 ; Loads the end flag
    int r0                      ; Ends the program

; Print string function
; String is terminated by NUL character
; R0 contains address of string
print_string:
    push r0                     ; Saves R0 for later use
    push r1                     ; Saves R1 for later use
    push r2                     ; Saves R2 for later use
    load r2, #1                 ; Loads increment into R2 
loop_print_string:
    loadub r1, [r0]             ; Loads the character into R1 
    jz r1, $skip_print_string   ; If the character is NUL, goes to end of function
    storeb r1, out              ; Outputs the character
    add r0, r0, r2              ; Increments the string address
    jmp $loop_print_string      ; Repeats everything with the next character
skip_print_string:
    pop r2                      ; Restores R2
    pop r1                      ; Restores R1
    pop r0                      ; Restores R0
    ret                         ; returns from function


; Prints the duration of the program up until this point
print_time:
    push r0                     ; Saves R0 for later use
    push r1                     ; Saves R1 for later use
    push r2                     ; Saves R2 for later use 
    push r3                     ; Saves R3 for later use

    load r2, ticks              ; Loads number of ticks to R2
    load r0, #duration_string   ; Loads duration_string into R0
    call $print_string          ; Calls print_string(duration_string)
    load r1, #time_string       ; Loads time string to R1
; Hours
    load r3, # 10 * 60 * 60     ; Loads number of ticks in hour into R3
    div r0, r2, r3              ; R0 becomes number of hours
    mod r2, r2, r3              ; R2 becomes number of ticks in current hour
    call $number_to_string      ; Calls number_to_string(hours, time_string)
    load r0, r1                 ; Loads time_string to R0
    call $print_string          ; Calls print_string(time_string)
    load r0, #hour_string       ; Loads hour_string to R0
    call $print_string          ; Calls print_string(hour_string)
; Minutes
    load r3, # 10 * 60          ; Loads number of ticks in minute into R3
    div r0, r2, r3              ; R0 becomes number of minutes
    mod r2, r2, r3              ; R2 becomes number of ticks in current minute
    call $number_to_string      ; Calls number_to_string(minutes, time_string)
    load r0, r1                 ; Loads time_string to R0
    call $print_string          ; Calls print_string(time_string)
    load r0, #minute_string     ; Loads minute_string to R0
    call $print_string          ; Calls print_string(minute_string)
; Seconds
    load r3, # 10               ; Loads number of ticks in second into R3
    div r0, r2, r3              ; R0 becomes number of seconds
    mod r2, r2, r3              ; R2 becomes number of ticks in current second
    call $number_to_string      ; Calls number_to_string(seconds, time_string)
    load r0, r1                 ; Loads time_string to R0
    call $print_string          ; Calls print_string(time_string)
    load r0, #second_string     ; Loads second_string to R0
    call $print_string          ; Calls print_string(second_string)
; Ticks
    load r0, r2                 ; R0 becomes number of ticks in current second
    call $number_to_string      ; Calls number_to_string(ticks, time_string)
    load r0, r1                 ; Loads time_string to R0
    call $print_string          ; Calls print_string(time_string)
    load r0, #millis_string     ; Loads millis_string to R0
    call $print_string          ; Calls print_string(millis_string)
    load r0, #crlf_string       ; Loads crlf_string into R0
    call $print_string          ; Calls print_string(crlf_string)

    pop r3                      ; Restores R3
    pop r2                      ; Restores R2
    pop r1                      ; Restores R1
    pop r0                      ; Restores R0
    ret                         ; Returns from function
    

; Number to string convert function
; R0 contains the number that should be converted
; R1 contains the destination
number_to_string:
    push r0                         ; Saves R0 for later use
    push r1                         ; Saves R1 for later use
    push r2                         ; Saves R2 for later use
    push r3                         ; Saves R3 for later use
    push r4                         ; Saves R4 for later use
    push r5                         ; Saves R5 for later use
    push r6                         ; Saves R6 for later use

    load r5, r1                     ; Copies the destination address into R5 for later use
    load r2, #10                    ; Loads 10 into R2 for later use
    load r4, #1                     ; Loads 1 into R4 for later use
    load r6, #'0'                   ; Loads ASCII '0' into R6 for later use
loop_number_to_string:
    mod r3, r0, r2                  ; R3 becomes last digit of the number
    add r3, r3, r6                  ; R3 becomes ascii value of the last digit
    storeb r3, [r5]                 ; Stores the last digit into 
    add r5, r5, r4                  ; Increments destination address
    div r0, r0, r2                  ; Divides the whole number by 10
    jnz r0, $loop_number_to_string  ; If the remaining number is not 0, do everything again

    load r3, #NUL                   ; Loads the null value into R3
    storeb r3, [r5]                 ; Stores the null value
    load r0, r1                     ; First parameter for reverse becomes the address
    sub r1, r5, r1                  ; Second parameter for reverse becomes the length
    call $reverse                   ; Calls reverse(address, lenght)

    pop r6                          ; Restores R6
    pop r5                          ; Restores R5
    pop r4                          ; Restores R4
    pop r3                          ; Restores R3
    pop r2                          ; Restores R2
    pop r1                          ; Restores R1
    pop r0                          ; Restores R0
    ret                             ; Returns from function

; String reverse function
; R0 contains the address
; R1 contains the length
reverse:
    push r0                 ; Saves R0 for later use
    push r1                 ; Saves R1 for later use
    push r2                 ; Saves R2 for later use
    push r3                 ; Saves R3 for later use
    push r4                 ; Saves R4 for later use

    add r1, r0, r1          ; R1 becomes address + length
    load r2, #1             ; Load decrement to R2
    sub r1, r1, r2          ; R1 becomes address of last element
loop_reverse:
    loadub r3, [r0]         ; Swap the front and back values using R3 and R4
    loadub r4, [r1]         ; ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    storeb r3, [r1]         ; ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    storeb r4, [r0]         ; ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    add r0, r0, r2          ; Increments front address
    sub r1, r1, r2          ; Decrements back address
    sub r3, r1, r0          ; R3 becomes <=0 if front>back
    jgz r3, $loop_reverse   ; If back > front do everything again

    pop r4                  ; Restores R4
    pop r3                  ; Restores R3
    pop r2                  ; Restores R2
    pop r1                  ; Restores R1
    pop r0                  ; Restores R0
    ret                     ; Returns from function


; ##########################################################
;
; Interrupt routines:
;
; ##########################################################

; Dummy interrupt routine 
dummy:
    ret

; Error interrupt routine
; Prints the error message and finishes the program
error_interrupt:
    load r0, #error_string      ; Loads the address of the error string to R0
    call $print_string           ; Calls print_string(error_string)
    load r0, #END_OF_PROGRAM    ; Loads the end_of_program flag to R0
    int r0                      ; Ends the program

; Timer interrupt routine
; Counts the number of ticks that happened during the execution of the program
timer_interrupt:
    push r0             ; Saves R0 for later use
    push r1             ; Saves R1 for later use
    load r0, ticks      ; Loads the number of ticks to R0 
    load r1, #1         ; Loads 1 to R1 
    add r0, r0, r1      ; Adds 1 to the number of ticks
    store r0, ticks     ; Stores the new number of ticks
    pop r1              ; Restores R1
    pop r0              ; Restores R0 
    ret                 ; Returns from routine

; Keyboard interrupt routine
; Scans the character into the input string if in scan mode, and also outputs that character
; Backspace deletes the last character
; Line feed submits the string
keyboard_interrupt:
    push r0                     ; Saves R0 for later use
    push r1                     ; Saves R1 for later use
    push r2                     ; Saves R2 for later use
    loadub r0, active           ; Loads the active flag
    jz r0, $skip_keyboard       ; If scanning not active, skip everything

    loadub r0, in               ; Load the input character into R0
    load r1, input_length       ; Load the current input length into R1
; Check for backspace
    load r2, #BS                ; Load the backspace character into R2 
    sub r2, r0, r2              ; R2 becomes 0 if input character is backspace
    jz r2, $backspace_pressed   ; If backspace is pressed, jump to that special case
    load r2, #DEL               ; Load the delete character into R2
    sub r2, r0, r2              ; R2 becomes 0 if input character is delete
    jz r2, $backspace_pressed   ; If delete is pressed, jump to that special case
; Check for line feed
    load r2, #LF                ; Load the line feed character into R2
    sub r2, r0, r2              ; R2 becomes 0 if line feed character is pressed
    jz r2, $line_feed_pressed   ; If line feed is pressed, jump to that special case
    load r2, #CR                ; Load the carriage return character into R2
    sub r2, r0, r2              ; R2 becomes 0 if carriage return character is pressed
    jz r2, $line_feed_pressed   ; If carriage return is pressed jump to that special case
; Check if too long
    load r2, # LEN - 1          ; Load LEN - 1 (leave 1 for NUL character)
    sub r2, r2, r1              ; R2 becomes <= 0 if the string would become too long
    jlez r2, $skip_keyboard     ; If string too long just skip this character
; Real work
    load r2, #input_string      ; Load the starting string address into r2
    add r2, r2, r1              ; R2 becomes address of current element
    storeb r0, [r2]             ; Stores the character into string
    storeb r0, out              ; Outputs the character
    load r2, #1                 ; Load increment to R2
    add r1, r1, r2              ; Increment input length
    store r1, input_length      ; Store the incremented value
skip_keyboard:
    pop r2                      ; Restores R2
    pop r1                      ; Restores R1 
    pop r0                      ; Restores R0 
    ret                         ; Returns from routine

backspace_pressed:
    jz r1, $skip_keyboard       ; If no characters are in string, do nothing
    load r0, #BS                ; Loads the backspace
    storeb r0, out              ; Outputs the backspace
    load r0, #' '               ; Loads the space
    storeb r0, out              ; Outputs the space
    load r0, #BS                ; Loads the backspace
    storeb r0, out              ; Outputs the backspace
    load r0, #1                 ; Loads decrement to R0 
    sub r1, r1, r0              ; Decrements the input string length
    store r1, input_length      ; Store the decremented value
    jmp $skip_keyboard          ; Jumps to end of routine

line_feed_pressed:
    load r0, #crlf_string       ; Loads crlf_string
    call $print_string          ; Prints crlf_string
    load r0, #input_string      ; Load the starting string address into R0
    add r0, r0, r1              ; R0 becomes the address after last element
    load r1, #NUL               ; Load the null character
    storeb r1, [r0]             ; Stores the null character into array
    store r1, active            ; Stores the same null value into active flag
    jmp $skip_keyboard          ; Jumps to end of routine

; ##########################################################
;
; Modifiable data:
;
; ##########################################################

.data.1

; Data for the timer
ticks:
    dd 0 ; Number of ticks from the start of the program

; Data for the keyboard interrupt
active:
    db 0 ; Flag indicating whether the keyboard interrupt is active
input_length:
    dd 0 ; Length of the input string

; ##########################################################
;
; Read only data: 
;
; ##########################################################

.rodata.1

; Input message for the start of the program
input_message:
    db 'W'
    db 'h'
    db 'a'
    db 't'
    db '''
    db 's'
    db ' '
    db 'y'
    db 'o'
    db 'u'
    db 'r'
    db ' '
    db 'n'
    db 'a'
    db 'm'
    db 'e'
    db '?'
    db CR
    db LF
    db NUL

; Hello string for the greeting
hello_string:
    db 'H'
    db 'e'
    db 'l'
    db 'l'
    db 'o'
    db ','
    db ' '
    db NUL

; Duration string for the time
duration_string:
    db 'D'
    db 'u'
    db 'r'
    db 'a'
    db 't'
    db 'i'
    db 'o'
    db 'n'
    db ':'
    db ' '
    db NUL

; New line
crlf_string:
    db CR
    db LF
    db NUL

; String to output in case of error
error_string:
    db 'E'
    db 'r'
    db 'r'
    db 'o'
    db 'r'
    db CR
    db LF
    db NUL

; Hours
hour_string:
    db 'h'
    db ' '
    db NUL

; Minutes
minute_string:
    db 'm'
    db ' '
    db NUL

; Seconds
second_string:
    db 's'
    db ' '
    db NUL

; Milliseconds
millis_string:
    db 'm'
    db 's'
    db NUL


; ##########################################################
;
; Uninitialized data:
;
; ##########################################################

.bss.1

; String which will be used to output the passed time
time_string:
    db 50 dup ? 

; String which the user will input
input_string:
    db LEN dup ? ; Maximum possible length is LEN
