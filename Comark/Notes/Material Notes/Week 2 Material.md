# Fundamentals of digital logic
*Digital Computer* refers to a device that performs computational steps on data items that have discrete values.

*analog computer* alternative to digital computer. It operates on values that vary continuosly over time. Only used in a few special cases.


## The transistor

a *transistor* is a semiconductor used to control the flow of the electrical current. At the lowest level all 
digital systems are composed of transistors. Digital circuits use Metal Oxide Semiconductor Transistor (MOSFET) aka FET. These are constructed with layers of silicon, a insulating silicon oxide layer (a kind of glass) and some metal wires that connects the transistor to the rest of the circuit.

A *transistor* functions as an on/off switch that is operated electronically instead of mechanically. That means they "open" and "close" based on the voltage applied.
![[two types of transistors.png]]

Here positive is when the voltage is above the gates threshold, then it is activated. And negative is when it is below the gates threshold it is activated.

## Logic gates
Since transistors have two possible states. Either current is flowing or not, we can then perceive them as booleans. This enables us to perform boolean algebra. Meaning using the *and*, *or* and *not* operators.
Below are the following outputs:
![[boolean algebra.png]]
![[Table for nand, nor and xor.png]]

## Implementation of a nand logic gate using transistors
![[Example of implementation of a nand logic gate.png]]
## Symbols used for logic gates
![[Symbols of the logic gates.png]]
## Circuits that maintain state
*sequential circuits* are circuits that are interconneted such that they can maintain a state.

A *latch* is one of the most basic of these kind of circuits. A latch has an input and output line. However they also contain an enable line. When the enable line is activated, meaning it is logically one, the latch outputs the same as the input. However when the enable line changes to logical 0, the output freezes at its current value. Meaning that the latch "remembers" the value that it had when the enable line was set to 0.
![[Example of a one bit latch.png]]
![[how we can remember multiple bits.png]]
![[Example of how we can construct a 4 bit register.png]]
Above here we see that the 1 bit latch, can be put together to store more bits.
![[A register is.png]]

## Propagation Delay
![[invert it self.png]]
This figure is an example of something that is mathematically not possible. Since it states:
output = not(output)
Which is a mathematical contradiction. However when working with circuits, there is a delay, even though it is something near less than a microsecond. However this delay enables this circuit to run. It is said that this circuit *oscillates* because it produces an output that goes back and forth between 0 and 1. This is also known as *square wave*.

## Flip-flops
A flip flop is a switch that remembers and acts on previous input combined with new input. For example when the flip flop first recieves the input one, it turns on the output. However when it recieves the one next time, it turns the output off. Simular to how a power button works on a computer.

![[Flip flop example.png]]
 A flip flop is constructed using two latches.

## Binary Counters

A counter is constructed of of several flip-flops. Howevever the counter have multople output lines to count the number of impulses that the counter has encountered.
![[Example of a counter.png]]


## Binary addition
![[A half adder.png]]
The *half adder* circuit computes the low order bit of the sum. 
![[Fulladder circuit.png]]
The *full adder* accepts 3 inputs, 2 inputs, as the half adder, but also a "carry in".  A *full adder* consists of 2 halfadders and an extra gate.
![[full affer with drawing.png]]
Here is a sketch of where the half adders are in the full adder.

## Clocks and Sequences
A clock is a an electronic circuit that oscillate. However they are not constructed using the invert as seen earlier. They are typically built with quartz crystal, which oscilates naturally and provides a signal at a precise frequency. The clock aplifies the signal and changes it from sine wave to a square wave.
The speed of a clock is measured in Hertz(Hz). Most clocks operates between 100 MHz and several GHz. A typical clock used by a processer operates at around 3 GHz.



![[Example of using a clock for starting up a pc.png]]
Above is an example of a clock used to start up a pc. A decoder is a circuit that "maps" outputs to certain things.



## Feedback
![[Example of feedback implemented in the clock example.png]]
## Clockless logic
![[Clockless logic with 2 signals.png]]

## Circuit size and Moore's law
![[Classification scheme for integrated circuits.png]]

the 7400 family of circuits is SSI. ANd Binary counter and Flip-Flop is MSI.
