# Introduction
## What is an Operating System
*Operating system* is software that uses the hardware resources of a computer system to provide support for the execution of programs. Provide the following services:
- Allows multiple computations concurrently on the same system and everything to achieve this.
- Controls interactions between concurrent computations. enforces rules such as forbidding computations from modifying data structures or gives the programs isolated memory.
- Provides file system so programs can read files from other programs. This is optional.
- provides support for controlled interaction among different computers by using networking.

The sum total of features a OS makes available is called:
*"API"* - Application programming interface.  
One of these is for example the ability to run other programs.

*Desktop environments* are the programs that handles the graphical part of a OS. For example Gnome or KDE.

*Middleware* is software occupying a middle position between application programs and operating systems. Used to support other software. The difference between OS and Middleware is that OS uses the underlying hardware and Middleware uses the underlying OS to function. Middleware is for example a relational database.
![[Middleware.png]]

**Difference between process and thread**
- *Thread*
	A thread is a fundemental unit of concurrency. A sequence of programmed actions is a thread. A program can make multiple threads, if multiple independent sequences of actions run concurrently.
- *Process*
	Process is a container that holds the threads and ensures threads from different programs doesn't interfere with each other.

Control over thread's timing is called *Synchronization*. Synchronization can force threads to wait or other threads. When a Thread waits for another it is known as a *"deadlock"* 

*Transaction* is a unit of computational work for which no intermediate state from the middle of the computation is never visible.

*Messaging system* is a system where an application program requests the delivery of a message.

*Remote Procedure call (RPC)* is another system in which communication between client and server is made to look like an ordinary programming language procedure call.

Regarding Security of a OS there are some common objectives for owner to fall into is 
- confidentiality
	prevent inappropriate disclosure of information.
- integrity
	prevent inappropriate modification or destruction of information.
- availability
	if it prevent inappropriate interference with legitimate usage.
- accountability.
	Provides a way to check how authorized users have exercises their authority.


# Threads
*Thread* is a step of instructions that are strung together.
![[Difference between program and thread.png]]![[Difference between program and thread.png]]
Concurrent threads serve two goals:
**Responsiveness:** A program can have a thread to respond to external input, while another thread can perform another process.
**Resource utilization**: Keeping most of the hardware's resources busy of the time.
![[Pasted image 20240411173614.png]]



