# Synchronization and Deadlocks
*mutual exclusion* is when some threads have the ability to lock certain data structures that it uses, in such a way that it excludes other threads from using that data structure. This is also called **"mutex"**

## Mutexes and monitors
![[mutex with multiple threads.png]]
![[4 different kind of mutex.png]]
Object that automatically follows the mutex rules is called a *monitor* these are found in some programming languages such as concurrent pascal.

a mutex that uses busy waiting, is called a *spinlock*. These are ineffecient for the same reasons that busy waiting is ineffeccient.

**Bounded Buffers** is a way to fix synchronization, by allowing the producers and consumers to work concurrently. the producers will however store their actions in a temporary buffer.

**Readers Writers lock** is like a mutex. Except that a thread can lock it to write or to read. When locking to write it gains the same as a mutex lock. However the read lock makes a shared lock, as known from the db course, such that all readers still can have access to it.

**Starvation** is when a thread is unfairly prevented from running on other threads.

**Barrier synchronization** here it is synchronization to have all threads run, but make them stop at the same time. This could be useful if the next step in the process depends on what the other threads have done. For example large calculations.

**Conditions** can be used to make certain threads only proceed if certain conditions is made. conditonal have 3 main functions. 
- **Waiting**
	a thread will wait until it gets notified/signalled to continue.
- **Signal/notift**
	Signal one thread waiting for the cond to proceed.
- **Broadcast/notify all**
	This sends a signal to all threads waiting for the cond to proceed.

**Semaphore** is an unsigned integer variable that can only take nonnegative integer values. only 3 operations is allowed on a semaphore:
![[three operations of semaphores.png]]
**Deadlock** is a situation that can occur if two threads each are waiting for something the other hold. see page 127 (147 in pdf) in OSM book for example.
![[Pasted image 20240417091541.png]]
The deadlock spaghetti example.

One technique to prevent deadlock is to ensure that two threads always gain the locks in the same order. Here meaning that locks have some sort of "ranking" on which locks they obtain first.