a# Data and Program Representation

## Bits and Bytes
### Bit 
"Bit" stands for binary digit and describes a digital entity that can have the two possible values. 
These values are assigned to mathematical names 0 and 1 for the two values. 
More bits can represent more complex data items, which is called bytes.
### Bytes
a byte is defined as the smallest data item larger than a bit that the hardware can manipulate.
The size of bytes varies from computer to computer, and the given size is chosen by the architect of the computer system.
Even though there is no standard, most systems define a byte as 8 bits.

![[Bits have no intrinsic meaning.png]]



### Binary Weighted Positional Representation
One of the most common abstractions to give meaning to bytes is by using a number system with base 2. Example of representations of this:

![[Example of binary representation weighted.png]]

![[How big a number eh?.png]]

![[digit comparrison for decimal vs base 2.png]]
Above here is an example of how many characters are used with power of 2 vs decimal("normal system").

## Hexadecimal Notation
![[HexaDecimal System.png]]
Example of numbers:

| Decimal Number | HexaDecimal | Binary |
| :--- | :--- | :--- |
| 15 | F | 1111 |
| 16 | 10 | 0001000 |
| 33 | 21 | 00100001 |
| 42 | 2A | 00101010 |
| 256 | 100 | 100000000 |

## Character Sets
![[Ascii character set.png]]
ASCII Stands for American Standard Code For Information Interchange. It is a standard that is set, so different hardware can agree what character a byte symbolises. Not that the ASCII Uses a Seven-bit array, even though most computers use 8 bytes. Sometimes the additional values are unused, used for different punctuation marks for other languages or other things. Depending on what the Computer Architecture designs.

## Unicode
Unicode is an extension of the ASCII and is used for languages where ASCII cant store enough information. For example Chinese.

## Unsigned Integers, overflow and underflow

Overflow can happen if the result of a calculation exceeds k bits. For example adding two numbers together.
Underflow happens when the result of the calculation is negative.

![[Example of Overflow.png]]
example of overflow


## Numbering Bits And Bytes
- little endian
	Systems that stores and transmits bytes of an integer from least significant to most significant (significant meaning size of number from bit)
-  big endian is systems that behave opposite of little endian.
- bit little endian
	systems that transfer bits within a byte from least significant to biggest.
- bit big endian is the opposite.
![[Example of little and big endian.png]]

## Signed Binary Intergers
- Sign Magnitude. One of the bits is a 1 if the number is negative and 0 if it is positive. The rest of the bits represent the absolute value of the number.
- One's complement. The positive numbers is represented as normal, however the negative number is the inverse of that number. Meaning that 0 become 1 and 1 become 0.
- Two's Complement. "Thus, positive integers have the same representation as in one’s complement. To form a negative number, start with a positive number, subtract one, and then invert each bit. As with one’s complement, the most significant bit tells the sign of the integer (1 for negative integers, 0 otherwise)."
![[Different Signed.png]]
![[Unsigned fact.png]]

## Floating Point
![[Floating points.png]]

# The variety of Processors and Computational Engines.
## The two basic architectural approaches
### Harvard Architecture
This architecture refers to a computer organization with 4 principal components. a Processor, an instruction memory, a data memory and I/O facilities.
![[Harvard Architecture.png]]
Benefits of the Harvard Architecture is that it can optimize memory to store programs and one optimized for storing data.

### Von Neumann Architecture
The Von Neumann uses the same components as the harvard architecture, however, the Von Neumann only uses one memory to hold both programs and data.
![[Von Neumann Architecture.png]]
This System offers complete flexibility at any time. Since the owner can change how much of the memory is devoted to programs and how much is for data. This have become widely adopted.
![[Von Neumann is highly adopted.png]]
A Von Neumann system is called a Stored Program Approach.

## Definition Of A processor
For an architect a processor refers to a digital device that can perform a computation involving multiple steps.

## The range of processors
### Fixed logic
A processor that performs a specific task. It can not be premodified to compute anything else. Examples of these are compute the function sin(x) or to perform a graphics operation needed in a video game.
### Selectable logic
Little more flexible that the fixed logic. A selectable can compute more than one thing depending on the input. For example compute either sin(x) or cos(x).
### Parameterised logic
Adds even more flexibility. Typically computes the same functions, however it is more flexible, since it can take more than one parameter.
### Programmable logic
These are the most flexible. These can change the sequence of steps each time the processor is used. It can run programs.

## CPU
![[CPU.png]]
A CPU contains multiple "engines"/components. That computes different stuff. 
## Structures of a conventional processor
![[Processor Components.png]]
### Controller
The controller is responsible for program execution. It coordinates the steps through the program to other hardware units.
### Arithmetic logic unit (ALU)
It performs one step computational tasks. like integer arithmetic, operations on bits and boolean logic operations. Performs the specific computation the controller asks it to.
### Local data storage
Holds local data values. like operands for arthemtic operations and the result. Usually takes form of hardware registers.
### Internal Interconnection(s)
a Processor contains one or more of these. Is used to move data and results around the processors hardware. For example between the ALU and the local data storage.
### External Interface(x) (I/O buses)
Handles all communication between the processor and the rest of the computer system.
 In particular, the external interface manages communication between the processor and external memory and I/O devices.

## Processor Categories and roles
### Coprocessors
A processor that works in conjunction or with and under the control of another processor.
Usually is a special purpose processor that performs a single task at high speed. For example a floating point accelerator.
### Microcontrollers
A microcontroller does trivial functions that does not need much traditional computation. Like controlling landing gear on an airplane, an engine in a automobile or and automatic door in a grocery store. It typically tests sensors and sends signals to control devices. 
![[Example of a microcontroller.png]]

### Embedded System Processors
Runs sophisticated electronic devices such as a wireless router or a smart phone. Is usually more powerful than the ones used for microcontrollers. It often has a protocol stack for communication.
### General-Purpose Processors
Most familiar. Examples of these are a CPU in a pc.


## Stored Programs
ROM stands for Read Only Memory
![[To a computer architect ... stored programs.png]]
## Fetch-execute Cycle
Used for access and perform steps of a program. 
![[algorithm 4.1.png]]
![[Fetch execute important.png]]
![[Summarize of how to use fetch-execute.png]]

## Program Translation
The process of translating a High Level Language (HHL) to a representation that the processor expects/can understand.
![[Process of program translation.png]]
## Clock Rate and Instruction Rate
![[Clock rate and instruction rate.png]]
