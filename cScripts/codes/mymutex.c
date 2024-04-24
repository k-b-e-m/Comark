#include "mymutex.h"

void init_my_mutex(my_mutex_t *mutex)
{
    (*mutex) = UNLOCKED;
}

void lock_my_mutex(my_mutex_t *mutex)
{
    // FILL HERE!
    // YOU CAN USE A COMBINATION OF C AND EXTENDED ASSEMBLY.
}

void unlock_my_mutex(my_mutex_t *mutex)
{
    (*mutex) = UNLOCKED;
}
