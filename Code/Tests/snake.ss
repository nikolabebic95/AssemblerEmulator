; ##########################################################
;
; Symbolic constants:
;
; ##########################################################

NUL def 0   ; String terminator
BS  def 8   ; Backspace
LF  def 10  ; Line feed
CR  def 13  ; Carriage return
ESC def 27  ; Escape
SPC def 32  ; Space
DEL def 127 ; Delete

; Arrows are printed as three characters. All arrows have the same first two characters
ARROW_0 def 27 ; First arrow character
ARROW_1 def 91 ; Second arrow character

ARROW_UP    def 65 ; Arrow up 
ARROW_DOWN  def 66 ; Arrow down 
ARROW_RIGHT def 67 ; Arrow right 
ARROW_LEFT  def 68 ; Arrow left 

FRAME def '#' ; Character used for border
SPACE def SPC ; Character used for empty field

HEAD_1 def '1' ; First snake head
HEAD_2 def '2' ; Second snake head

WIDTH  def 64 ; Width of the map 
HEIGHT def 32 ; Height of the map

; Directions
UP    def 0
RIGHT def 1
DOWN  def 2
LEFT  def 3

; Keys

SNAKE_1_UP    def 'w'
SNAKE_1_DOWN  def 's'
SNAKE_1_LEFT  def 'a'
SNAKE_1_RIGHT def 'd'

SNAKE_2_UP    def 'i'
SNAKE_2_DOWN  def 'k'
SNAKE_2_LEFT  def 'j'
SNAKE_2_RIGHT def 'l'

; End flags
SNAKE_1_WON def 1
SNAKE_2_WON def 2
TIE         def 3

END_OF_PROGRAM def 0 ; End of program interrupt code

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
; Prints the frame, busy waits the end, and prints winner and time
.global _start
_start:
    call $print_frame
    load r0, snake_1_row
    load r1, snake_1_col
    call $move_to
loop:
    load r0, end
    jz r0, loop
    load r0, #HEIGHT
    load r1, #0
    call $move_to
    call $print_winner
    call $print_time
    load r0, #END_OF_PROGRAM
    int r0

; ##########################################################
;
; Arrows:
;
; ##########################################################

; Prints the first two arrow characters
print_arrow:
    push r0
    load r0, #ARROW_0
    storeb r0, out
    load r0, #ARROW_1
    storeb r0, out
    pop r0
    ret

; Prints the up arrow
print_arrow_up:
    push r0
    call $print_arrow
    load r0, #ARROW_UP
    storeb r0, out
    pop r0
    ret

; Prints the down arrow
print_arrow_down:
    push r0
    call $print_arrow
    load r0, #ARROW_DOWN
    storeb r0, out
    pop r0
    ret

; Prints the right arrow
print_arrow_right:
    push r0
    call $print_arrow
    load r0, #ARROW_RIGHT
    storeb r0, out
    pop r0
    ret

; Prints the left arrow
print_arrow_left:
    push r0
    call $print_arrow
    load r0, #ARROW_LEFT
    storeb r0, out
    pop r0
    ret

; Moves the cursor to the desired position
; R0 contains the row
; R1 contains the column
move_to:
    push r0
    push r1
    push r2
    push r3
    push r4
    push r5
    load r2, row
    load r3, col
    load r5, #1
move_to_loop:
    sub r4, r2, r0
    jlz r4, $move_down
    jgz r4, $move_up
    sub r4, r3, r1
    jlz r4, $move_right
    jgz r4, $move_left
    store r2, row
    store r3, col
    pop r5
    pop r4
    pop r3
    pop r2
    pop r1
    pop r0
    ret

move_up:
    call $print_arrow_up
    sub r2, r2, r5
    jmp $move_to_loop

move_down:
    call $print_arrow_down
    add r2, r2, r5
    jmp $move_to_loop

move_left:
    call $print_arrow_left
    sub r3, r3, r5
    jmp $move_to_loop

move_right:
    call $print_arrow_right
    add r3, r3, r5
    jmp $move_to_loop

; ##########################################################
;
; Snake 1
;
; ##########################################################

print_snake_1_head:
    push r0                     ; Saves R0 for later use
    load r0, #HEAD_1            ; Loads the head
    storeb r0, out              ; Outputs the space
    load r0, #BS                ; Loads the backspace
    storeb r0, out              ; Outputs the backspace
    pop r0                      ; Restores R0
    ret                         ; Returns from function

; Moves the first snake one spot towards the current direction
; If a collision occurs, sets the end flag
move_snake_1:
    push r0
    push r1
    push r2
    push r3
    load r2, #1

    load r0, snake_1_row
    load r1, snake_1_col

    jz r0, $end_game_1
    jz r1, $end_game_1
    load r3, #HEIGHT - 1
    sub r3, r3, r0
    jz r3, $end_game_1
    load r3, #WIDTH - 1
    sub r3, r3, r0
    jz r3, $end_game_1

    call $move_to
    call $print_snake_1_head

    load r3, #WIDTH
    mul r3, r3, r0
    add r3, r3, r1
    loadub r0, [r3 + matrix]
    jnz r0, end_game_1
    storeb r2, [r3 + matrix]

    load r0, snake_1_dir
    
    load r1, #UP
    sub r1, r1, r0
    jz r1, $move_snake_1_up
    
    load r1, #DOWN
    sub r1, r1, r0
    jz r1, $move_snake_1_down
    
    load r1, #LEFT
    sub r1, r1, r0
    jz r1, $move_snake_1_left
    
    load r1, #RIGHT
    sub r1, r1, r0
    jz r1, $move_snake_1_right

    jmp $move_snake_end

move_snake_1_up:
    push r0
    load r0, snake_1_row
    sub r0, r0, r2
    store r0, snake_1_row
    pop r0
    jmp $move_snake_end

move_snake_1_down:
    push r0
    load r0, snake_1_row
    add r0, r0, r2
    store r0, snake_1_row
    pop r0
    jmp $move_snake_end

move_snake_1_left:
    push r0
    load r0, snake_1_col
    sub r0, r0, r2
    store r0, snake_1_col
    pop r0
    jmp $move_snake_end

move_snake_1_right:
    push r0
    load r0, snake_1_col
    add r0, r0, r2
    store r0, snake_1_col
    pop r0
    jmp $move_snake_end

; Keyboard helpers

change_1_up:
    load r0, #UP
    store r0, snake_1_dir
    jmp $end_keyboard

change_1_down:
    load r0, #DOWN
    store r0, snake_1_dir
    jmp $end_keyboard

change_1_left:
    load r0, #LEFT
    store r0, snake_1_dir
    jmp $end_keyboard

change_1_right:
    load r0, #RIGHT
    store r0, snake_1_dir
    jmp $end_keyboard

; Ends game
end_game_1:
    load r0, #SNAKE_2_WON
    store r0, end
    jmp $move_snake_end

; ##########################################################
;
; Snake 2
;
; ##########################################################

print_snake_2_head:
    push r0                     ; Saves R0 for later use
    load r0, #HEAD_2            ; Loads the head
    storeb r0, out              ; Outputs the space
    load r0, #BS                ; Loads the backspace
    storeb r0, out              ; Outputs the backspace
    pop r0                      ; Restores R0
    ret                         ; Returns from function

; Moves the second snake one spot towards the current direction
; If a collision occurs, sets the end flag
move_snake_2:
    push r0
    push r1
    push r2
    push r3
    load r2, #1

    load r0, snake_2_row
    load r1, snake_2_col

    jz r0, $end_game_2
    jz r1, $end_game_2
    load r3, #HEIGHT - 1
    sub r3, r3, r0
    jz r3, $end_game_2
    load r3, #WIDTH - 1
    sub r3, r3, r0
    jz r3, $end_game_2

    call $move_to
    call $print_snake_2_head

    load r3, #WIDTH
    mul r3, r3, r0
    add r3, r3, r1
    loadub r0, [r3 + matrix]
    jnz r0, end_game_2
    storeb r2, [r3 + matrix]

    load r0, snake_2_dir
    
    load r1, #UP
    sub r1, r1, r0
    jz r1, $move_snake_2_up
    
    load r1, #DOWN
    sub r1, r1, r0
    jz r1, $move_snake_2_down
    
    load r1, #LEFT
    sub r1, r1, r0
    jz r1, $move_snake_2_left
    
    load r1, #RIGHT
    sub r1, r1, r0
    jz r1, $move_snake_2_right

    jmp $move_snake_end

move_snake_2_up:
    push r0
    load r0, snake_2_row
    sub r0, r0, r2
    store r0, snake_2_row
    pop r0
    jmp $move_snake_end

move_snake_2_down:
    push r0
    load r0, snake_2_row
    add r0, r0, r2
    store r0, snake_2_row
    pop r0
    jmp $move_snake_end

move_snake_2_left:
    push r0
    load r0, snake_2_col
    sub r0, r0, r2
    store r0, snake_2_col
    pop r0
    jmp $move_snake_end

move_snake_2_right:
    push r0
    load r0, snake_2_col
    add r0, r0, r2
    store r0, snake_2_col
    pop r0
    jmp $move_snake_end

; Keyboard helpers

change_2_up:
    load r0, #UP
    store r0, snake_2_dir
    jmp $end_keyboard

change_2_down:
    load r0, #DOWN
    store r0, snake_2_dir
    jmp $end_keyboard

change_2_left:
    load r0, #LEFT
    store r0, snake_2_dir
    jmp $end_keyboard

change_2_right:
    load r0, #RIGHT
    store r0, snake_2_dir
    jmp $end_keyboard

; Ends game
end_game_2:
    load r0, #SNAKE_1_WON
    store r0, end
    jmp $move_snake_end

; ##########################################################
;
; Snakes common:
;
; ##########################################################

; End of the move_snake functions
move_snake_end:
    pop r3
    pop r2
    pop r1
    pop r0
    ret

end_game:
    load r0, #TIE
    store r0, end
    jmp $move_snake_end

; Prints the winner
print_winner:
    push r0
    push r1
    load r0, end

    load r1, #SNAKE_1_WON
    sub r1, r1, r0
    jz r1, $print_1_won

    load r1, #SNAKE_2_WON
    sub r1, r1, r0
    jz r1, $print_2_won

    load r1, #TIE
    sub r1, r1, r0
    jz r1, $print_tie

end_print_winner:
    call $print_string
    pop r1
    pop r0
    ret

print_1_won:
    load r0, #winner_1
    jmp $end_print_winner

print_2_won:
    load r0, #winner_2
    jmp $end_print_winner

print_tie:
    load r0, #tie_string
    jmp $end_print_winner


; ##########################################################
;
; Frame
;
; ##########################################################

print_frame:
    push r0
    push r1
    push r2
    
    load r2, #1
    load r0, #filled_row
    call $print_string
    load r1, # HEIGHT - 2
    load r0, #empty_row
loop_print_frame:
    jz r1, end_print_frame
    sub r1, r1, r2
    call $print_string
    jmp loop_print_frame
end_print_frame:
    load r0, #filled_row
    call $print_string

    pop r2
    pop r1
    pop r0
    ret

; ##########################################################
;
; Helpers:
;
; ##########################################################

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
    call $print_string          ; Calls print_string(error_string)
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
    call $move_snake_1  ; Moves the first snake
    call $move_snake_2  ; Moves the second snake
    pop r1              ; Restores R1
    pop r0              ; Restores R0 
    ret                 ; Returns from routine

; Keyboard interrupt routine
; Picks up move characters, and updates the direction
; Picks up the exit character, and updates the flag
keyboard_interrupt:
    push r0
    push r1
    loadub r0, in
    
    load r1, #SNAKE_1_UP
    sub r1, r1, r0
    jz r1, $change_1_up

    load r1, #SNAKE_1_DOWN
    sub r1, r1, r0
    jz r1, $change_1_down

    load r1, #SNAKE_1_LEFT
    sub r1, r1, r0
    jz r1, $change_1_left

    load r1, #SNAKE_1_RIGHT
    sub r1, r1, r0
    jz r1, $change_1_right

    load r1, #SNAKE_2_UP
    sub r1, r1, r0
    jz r1, $change_2_up

    load r1, #SNAKE_2_DOWN
    sub r1, r1, r0
    jz r1, $change_2_down

    load r1, #SNAKE_2_LEFT
    sub r1, r1, r0
    jz r1, $change_2_left

    load r1, #SNAKE_2_RIGHT
    sub r1, r1, r0
    jz r1, $change_2_right

    load r1, #ESC
    sub r1, r1, r0
    jnz r1, $end_keyboard
    load r0, #TIE
    store r0, end

end_keyboard:
    pop r1
    pop r0
    ret

; ##########################################################
;
; Modifiable data:
;
; ##########################################################

.data.1

; Data for the timer
ticks:
    dd 0 ; Number of ticks from the start of the program

; Current row and column
row:
    dd HEIGHT
col:
    dd 0

; End flag
end:
    dd 0

; Snake 1
snake_1_dir:
    dd RIGHT

snake_1_row:
    dd 2

snake_1_col:
    dd 2

; Snake 2
snake_2_dir:
    dd LEFT

snake_2_row:
    dd HEIGHT - 3

snake_2_col:
    dd WIDTH - 3

; Map
matrix:
    db WIDTH * HEIGHT dup 0

; ##########################################################
;
; Read only data: 
;
; ##########################################################

.rodata.1

filled_row:
    db WIDTH dup FRAME
    db CR
    db LF
    db NUL

empty_row:
    db FRAME
    db (WIDTH - 2) dup SPACE
    db FRAME
    db CR
    db LF
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

winner_1:
    db 'W'
    db 'i'
    db 'n'
    db 'n'
    db 'e'
    db 'r'
    db ':'
    db ' '
    db 'S'
    db 'n'
    db 'a'
    db 'k'
    db 'e'
    db ' '
    db '1'
    db CR
    db LF
    db NUL

winner_2:
    db 'W'
    db 'i'
    db 'n'
    db 'n'
    db 'e'
    db 'r'
    db ':'
    db ' '
    db 'S'
    db 'n'
    db 'a'
    db 'k'
    db 'e'
    db ' '
    db '2'
    db CR
    db LF
    db NUL

tie_string:
    db 'I'
    db 't'
    db '''
    db 's'
    db ' '
    db 'a'
    db ' '
    db 't'
    db 'i'
    db 'e'
    db CR
    db LF
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
