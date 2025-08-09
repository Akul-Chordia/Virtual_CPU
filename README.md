# Simple Logic-Gate-Based CPU Simulator

This project is a custom CPU simulator built entirely from logic gates (`AND`, `NOT`), progressing through registers, an ALU, memory, and control logic. It includes a CLI interface for instruction execution and debugging. The CPU uses a custom instruction set and simulates hardware behavior like register write delays, clock edges, and flag setting.

## Features

- Instruction set with arithmetic, logic, memory, and jump operations
- Boolean logic implementation from scratch using only `AND` and `NOT` gates
- Custom-built:
  - ALU (add, subtract, AND, OR, XOR, NOT, increment, decrement)
  - Register array with PC, A/B/C/D, MAR, Temp
  - Memory with primary and extended banks
  - Clocked flip-flops and D-latches for register simulation
- Debug/step execution support with full state inspection
- Simple command-line shell for loading and running programs

## Instruction Set

Supports over 30 operations like:

- Arithmetic: `ADD`, `SUB`, `INC`, `DEC`, `NEG`
- Logic: `AND`, `OR`, `XOR`, `NOT`
- Data movement: `MOV`, `LOAD`, `STORE`
- Control: `JMP`, `JZ`, `JNZ`, `JG`, `JE`, `HLT`

Full list: use the `help` command in the simulator

<img width="279" alt="image" src="https://github.com/user-attachments/assets/24a8163b-54fa-4843-aad4-e969ded7f91b" />


Example:  
`0x2005` → Load `5` into register A  
`0x3A64` → Store A into memory address `100`  


## Usage

### Build

Compile all `.h` files with the `main.cpp` driver.

```bash
g++ main.cpp -o cpu_sim
````

### Run

```bash
./cpu_sim
```

### CLI Commands

```
help         - Show help and instruction set
reset        - Clear memory and reset CPU
load <prog>  - Load hex-coded program (space-separated)
run          - Execute the entire program
step         - Execute one instruction
status       - Print all register values
example      - Load a demo program (5 + 3)
quit         - Exit simulator
```

### Example Program

```bash
> load 2005 2103 0100 FE00 FF00
> run
```
<img width="279" alt="image" src="https://github.com/user-attachments/assets/027b111b-f505-4cec-b87f-e4d4b0450af6" />


Step by step debugging mode:


<img width="298" alt="image" src="https://github.com/user-attachments/assets/3e017f2f-78f0-437f-968c-2f043e258cad" />


## File Structure

* `main.cpp` – Entry point and command interface
* `CPU.h` – Control unit and fetch-decode-execute loop
* `register_array.h` – A/B/C/D/PC/Temp/MAR/Flags
* `ALU.h` – 8-bit ALU from logic gates
* `registers.h` – D-latch, D-flip-flop, 8-bit register simulation
* `memory.h` – 512-byte code memory, 256-byte external memory, and read/write logic
* `logic gates.h` – AND, NOT base; derived XOR, OR, NAND
* `instructions.h` – CLI command documentation
* `test.h` – Testing for individual components
* `selectors.h` – Mux, Demux, Encodes and Decoders

## Requirements

* C++11 or later
* No external libraries

## Current Issues being worked on

* The clock signal isn't an external clock yet
* No labeling for jump instructions
* Need a better memory addressing system

## Credits

Designed and implemented by Akul as a low-level CPU simulation project using fundamental digital logic principles.

