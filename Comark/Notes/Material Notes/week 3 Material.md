# Processor Types and instruction Sets
## Operations for a processor
![[operations for a harddrive.png]]
Here operations are things like addition, multiplication, subtraction and division.
## Opcodes, Operands and result
*Opcode*: Short for operation code. Refers to the exact operation. Represented as a number. For example addition might have opcode 5 and subtraction opcode 12.
*Operands*: The values which will be affected by the operation.
*Result*: Specifications on where the result should be placed.

## General-Purpose Registers
*General-purpose register:* A register that are used to temporarily store values. A processor usually has a small number of these, For example 32.

## Floating Point Register
If A processor works with floating points. It is normal to have certain registers specified to contain the floating points.

## Programming with registers'
Example of programming with registers, where one want to add X and Y:
![[Example of programming with registers.png]]

## Register banks
![[Example of register bank.png]]
*Register bank*: Some architectures dive registers into multiple "banks". These allows the hardware to work faster, because each bank has its own access mechanism, and these mechanisms can work simultaneously. And example of this is shown in the picture above.

*Register Conflict*: A register conflict occurs when values/variables from the same register is in the same bank. In this case, we cannot take the multiple values at the same time. An example of this is below:
![[Example of register conflict.png]]
Here X and Y must be in two separate banks, due to the first action, lets say X is in a and Y is in b. Next leads us to that Z must be in b, since X is in a. 
Next leads us to Z must be in a, since Y is in b.
This leads to a conflict, which can be solved if we before the last operation, copied Z from b to a.

## Cisc and Risc
![[Cisc and Risc.png]]
### Risc
These processors performs one instruction per clock cycle.
![[risc fetch execute cycle.png]]
above is the typical fetch-execute cycle for the risc processors.
![[The pipeline of risc.png]]
Above is the pipeline for the Risc processors. Whenever the clock ticks, all stages pass the instruction to the right. Risc processors are fast, because each of these stages can work simultaneously.
![[Example of a working risc pipeline.png]]
above is an example of the pipeline being used.
![[risc can be fast.png]]
#### Pipeline stalls
![[example of pipeline stall.png]]
Above is an example of a pipeline stall. Instruction k+1 needs C which instruction K produces. This means that instruction K+1 cannot proceed before instruction K is finished. This results in a stall and the programmer have now introduced an ineffeciency. Below is the example in a process:
![[pipeline stall example.png]]
The "gap" of operations performed is called a "bubble" passing through the pipeline.

Other reasons for stalls could be:
- Acceses external storage.
- Invokes a coprocessor
- Branches to a new location
- Calls a subroutine

There is different more advanced ways to avoid stalls in these cases. For example to have two copies of pipelines.
##### Optimized code for stalls
![[Example of optimized code.png]]
Here we see that b is an optimized version of a, since the stall have been taken in to considaration.![[reaaringing code sequences is optimizing.png]]
Most compilers handle the optimisation the compiling from a higher level language.

##### No-Op
![[A noOp.png]]

##### Forwarding
Some hardware has a technique known as forwarding. Which detects dependencies and can forward results directly in to the dependent calculation.
![[example of pipeline stall.png]]
Here C can for example be passed in directly to K+1 when the result is available, instead of waiting for the pipeline to finish instruction k.

## Types of Operations:
Here are the different catogories for the type of operations:
![[catogories of operations.png]]

## Instruction set
![[Example of instruction set.png]]
![[Instructions 2.png]]

Above is a table of instructions for the MIPS processor, which is a Risc processor.

## Orthogonality
![[Orthogonality definition.png]]

# Data paths and Instruction Execution
![[Cheat Sheet For Assembly.png]]
Above is a cheat sheet for assembly.

![[Binary representation for 4 different instructions.png]]

## Moving to the next instruction.
*Instruction Pointer*: Consists of a register that holds the memory address of the next instruction to execute. 

To execute instructions the hardware repeats the following three steps:
- Use the instruction pointer as a memory address and fetch an instruction.
- Use bits in the instruction to control hardware that performs the operation.
- Move the instruction pointer to the next instruction.
