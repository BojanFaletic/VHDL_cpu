# Simple CPU written in VHDL #
Main purpose is to configure external peripherals without need for real CPU

# CPU features
* Read and write to IO
* IF states
* FOR loops
* FUNCTIONS


## Instruction List ##
IO operations:
LOAD <address>
STORE <address>

Arithmetic operations:
ADD <address>
SUB <address>

Logic operations:
AND <address>
OR <address>
SHIFT-L <address>
SHIFT-R <address>

Comparison:
JMP-EQ <address>
JMP-NEQ <address>

Compares value in accumulator (from previous instruction or return )
CMP-EQ <address>
CMP-LT <address>
CMP-GT <address>

Jumping instructions:
JMP <address>

Stack operations:
POP <to_register>
PUSH

## ToDo
* add immediate instructions
* fetch decode cycle

## Register list ##

R0 general register
R1 return value register

## sections in CPU ##
* ALU
* ROM
* RAM
* STACK
* IO-LINE

