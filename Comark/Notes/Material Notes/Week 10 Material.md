# Scheduling
*Scheduler* makes decisions such that the systems user is happy. It decides which threads gets access to some hardware and when.

Threads can typically have 2 states. Waiting or ready. A scheduler handling multiple threads can have a *run queue* and a *wait queue* to make sure that only queues that do currently can do something useful with the processor gets access to the processor. They might not be the data structure queue, but could be a list sorted in a certain way.

![[wait run queue.png]]
![[Pasted image 20240412094156.png]]
Above we see cache coherence protocol

*Niceness* is a term for how nice a thread is. The nicer the more willing it is to wait to let others do their job.
![[Mechanism and goal.png]]

# Processes and Protection
## Posix API
Is used by linux and unix, including by Mac OS X. In this approach each process is identified by a process ID number.

