
# What is a computer?
Seans definition:
A computer is an automatic, programmable information treatment system. A program in machine code (in a machine language) instructs a computer how to treat the information.

![[Definition of what a computer is.png]]

**Flow Control**
flow control is stuff like if/else or jumps.

# Motivation for learning computer architecture
![[Examples of motivation for computer architecture.png]]



# Terminology
![[Terminology week 1.png]]


- Hardware architecture
	How it looks from the outside. Abstracts the details of the components.
-  Micro-architectural design
	Tells how components are grouped or how power is distributed. 
- Implementation
	all details necessary to build a system. These is like wiring, chassis, layout of components and so on.


# Fetch-decode-execute cycle
The cycle is executed in a loop. or in multiple loops at the same time. 
**Fetch**
Get the instructions from memory.
**Decode**
Decode the bits of the instructions. Figure out what instruction is fetched and its operands.
**Execute**
Perform the actions and save what needs to be saved. based on the instructions.

# Bits
Physics: Electrons on a wire.

Electrinics: Close to zero or close to 3.3 volt.

Binary: High and low $\rightsquigarrow$ Binary digit (bit)
	Typically interpreted as 1 and 0.

# Converting decimal to bits
![[converting decimal to bit.png]]
The method here is:
$$
\begin{align*}
\frac{1492}{2} &= 746 ||1492 \%2 = 0\\\\
\frac{746}{2}&= 373 || 746 \% 2 &= 0\\
\frac{373}{2}=186 || 373  \% 2 &= 1
\end{align*}
$$
In the end this computes the binary number.

# Overflow vs Carry
![[Example of Overflow vs Carry.png]]

