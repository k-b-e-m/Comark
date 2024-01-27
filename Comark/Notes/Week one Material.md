# Data and Program Representation

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