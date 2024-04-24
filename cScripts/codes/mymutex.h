#ifndef MY_MUTEX_H
#define  MY_MUTEX_H

#define UNLOCKED 1
#define LOCKED 0

// Our mutex is very simple so it is either locked or unlocked and we don't
// keep any other information

// We define the type of our mutex, my_mutex_t as a volatile long integer. 
//
//      THE VOLATILE KEYWORD:
// The keyword volatile in C essentially tells the compiler that the contents
// of a my_mutex_t type variable can change by other threads. Without the
// volatile keyword, the compiler can optimize the cache-concious
// implementation of a spinlock as an infinite loop, because it includes a
// loop (refer to the book for full details):
//      while mutex is 0:
//          do nothing
// If the compiler treats the mutex as an ordinary variable, then it knows that
// when the mutex is 0, then we have an infinite loop. So it can check the
// condition once and if true, it can enter an infinite loop.  By placing the
// volatile keyword, we are forcing to compiler to constantly check the mutex
// instead of checking it once.
typedef volatile long my_mutex_t;

// Initializes a mutex to be unlocked
void init_my_mutex(my_mutex_t *mutex);

// Tries to grab a lock. The function only returns when the current thread
// holds the lock
void lock_my_mutex(my_mutex_t *mutex);

// Unlocks the mutex. You don't need to check to see if the current thread
// holds the lock
void unlock_my_mutex(my_mutex_t *mutex);

#endif
