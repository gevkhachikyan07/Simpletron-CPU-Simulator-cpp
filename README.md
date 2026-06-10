# Simpletron CPU Simulator (C++)

A low-level CPU and memory simulator written in C++.  
This project emulates a simplified computer system that executes machine-like instructions, similar to a real CPU architecture.

---

##  Project Overview

Simpletron is a virtual machine that simulates:
- Memory (1000 integer cells)
- CPU registers (Accumulator, Instruction Counter, Instruction Register)
- Instruction decoding (Opcode + Operand)
- Program execution cycle (Fetch → Decode → Execute)

It supports arithmetic, control flow, input/output, and string operations.

---

##  Features

###  Core CPU Simulation
- Instruction Counter (program flow control)
- Instruction Register (current instruction)
- Accumulator (arithmetic operations)
- Memory (1000-word storage system)

###  Supported Instructions
- Input / Output operations
- Load / Store
- Add / Subtract / Multiply / Divide
- Remainder / Exponentiation
- Branching (unconditional, negative, zero)
- Program halt

###  String Handling
- Reads strings into memory
- Encodes characters into integer memory format
- Decodes and prints stored strings

###  Memory Visualization
- Full memory dump table
- Register state display
- Debug-friendly output format

---

##  Example Execution Flow

1. Program is loaded into memory
2. Instructions are decoded into:
   - Opcode (operation type)
   - Operand (memory address)
3. CPU executes instructions step-by-step
4. Program halts on `HALT` instruction

---

##  Tech Stack

- C++
- Standard Library (`iostream`, `array`, `format`, `cmath`, `limits`)

---

##  How to Run

### Compile:
```bash
g++ main.cpp -o simpletron
