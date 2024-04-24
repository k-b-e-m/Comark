#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Code for time measurements. startTimer() starts the timer.
// stopTimer() returns the elapsed time from the last startTimer() call
// as a double (floating point) in milliseconds.
// Time measurement for Windows
#if defined(_WIN32)
#include <sys/timeb.h>
struct _timeb startt,endt;
void startTimer()
{
    _ftime_s(&startt);
}
double stopTimer()
{
    _ftime_s(&endt);
    return (double)(endt.time-startt.time)*1000+(endt.millitm-startt.millitm);
}

// Time measurement for Unix
#elif defined(__unix__)
struct timespec prevtime,curtime;

#define CLOCK CLOCK_REALTIME
// returns the difference in mili seconds. 
double stopTimer() {
    clock_gettime(CLOCK,&curtime);
    return (double)(curtime.tv_sec - prevtime.tv_sec)*1000 + ((double)(curtime.tv_nsec - prevtime.tv_nsec))/1000000;
}
void startTimer()
{
    clock_gettime(CLOCK,&prevtime);
}

// Time measurement for MacOS
#elif defined(__APPLE__)
struct timespec prevtime,curtime;
#define CLOCK CLOCK_REALTIME
// returns the difference in mili seconds. 
double stopTimer() {
    clock_gettime(CLOCK,&curtime);
    return (double)(curtime.tv_sec - prevtime.tv_sec)*1000 + ((double)(curtime.tv_nsec - prevtime.tv_nsec))/1000000;
}
void startTimer()
{
    clock_gettime(CLOCK,&prevtime);
}
#elif

#error "Unrecognized system. Add functions for time measurement to the code"
#endif

int size = 1024*1024*512; // big array!
int *A;

void test(int *B, int *C){
    int err=0;
    for (int i=0 ;i<20 ; i++){
        if  (B[i] % 2 == 1) {
            if (C[i] != -1) {
                printf("Error found: %d \t %d\n",B[i],C[i]);
                err = 1;
            }
        } else {
            if (C[i] != B[i]/2) {
                printf("Error found: %d \t %d\n",B[i],C[i]);
                err = 1;
            }
        }
    }
    if (err == 0) printf("All correct ...\n");
}

int slcompBST(int x, int slFactor){
    unsigned int left=0;
    unsigned int right=size;
    unsigned int mid=0;
    while (1) {
        mid = left + ((right-left)>>slFactor);
        if (x == A[mid]) return mid;
        if (right <= (left+1)) return -1;
        // Below we implement the following using assembly:
        // if (x < A[mid] ) {
        //     right = mid;
        // } else {
        //     left = mid+1;
        // }                               
        asm("cmp %[Amid],%[x]                 \n\t "
            "bgt Lgoleft%=						\n\t "
            "mov %[left],%[mid]				    \n\t "
            "add %[left],%[left],#1				\n\t "
            "b Lgofinish%=						\n\t "
            "Lgoleft%=: mov %[right],%[mid]		\n\t "
            "Lgofinish%=:						\n\t"
            : [left] "+r" (left), [right] "+r" (right)  /* output */   \
            : [mid] "r" (mid), [x] "r" (x), [Amid] "r" (A[mid])  /* inputs*/ \
            :  "cc");     /* we are changing the flags*/ 
    }
}

int compBST(int x){
    unsigned int left=0;
    unsigned int right=size;
    unsigned int mid=0;
    while (1) {
        mid = left + (right-left)/2;
        if (x == A[mid]) return mid;
        if (right <= (left+1)) return -1;
        // Below we implement the following using assembly:
        // if (x < A[mid] ) {
        //     right = mid;
        // } else {
        //     left = mid+1;
        // }                               
        asm("cmp %[Amid],%[x]                 \n\t"
            "bgt Lgoleft%=						\n\t"
            "mov %[left],%[mid]				    \n\t"
            "add %[left],%[left],#1				\n\t"
            "b Lgofinish%=						\n\t"
            "Lgoleft%=: mov %[right],%[mid]		\n\t"
            "Lgofinish%=:						\n\t"
            : [left] "+r" (left), [right] "+r" (right)  /* output */   \
            : [mid] "r" (mid), [x] "r" (x), [Amid] "r" (A[mid])  /* inputs*/ \
            :  "cc");     /* we are changing the flags*/ 
    }
}

int condBST(int x){
    unsigned int left=0;
    unsigned int right=size;
    unsigned int mid=0;
    while (1) {
        mid = left + (right-left)/2;
        if (x == A[mid]) return mid;
        if (right <= (left+1)) return -1;
        // Below we implement the following using assembly via conditional moves
        // if (x < A[mid] ) {
        //     right = mid;
        // } else {
        //     left = mid+1;
        // }                               
        asm("cmp %[Amid],%[x]                 \n\t"
             "csel %[right],%[mid],%[right],gt           \n\t"
             "csinc %[left],%[left],%[mid],gt          \n\t"
            : [left] "+r" (left), [right] "+r" (right)  /* output */   \
            : [mid] "r" (mid), [x] "r" (x), [Amid] "r" (A[mid])  /* inputs*/ \
            :  "cc");     /* we are changing the flags*/ 
    }
}

int main(int argn,char **argv){
    srand(time(NULL));
    if (argn != 2){
        printf("Enter the array size.\n");
        return -1;
    }

    size=atol(argv[1]);
    A = (int*)malloc(size*sizeof(int));

    for (int i=0 ; i<size ; i++){
        A[i]= 2*i;
    }

    double elapsed;
    int bSize = 1024*1024*8;
    int *B = (int *)malloc(bSize*sizeof(int));
    int *C = (int *)malloc(bSize*sizeof(int));

    for (int i=0 ; i<bSize ; i++) {
        B[i]= (rand()%(2*size));
    }

    printf("Conditional move based ...");
    startTimer();
    for (int i=0 ; i<bSize ; i++){
        C[i]=condBST(B[i]);
    }
    elapsed = stopTimer();
    printf(" %.3f milliseconds.\n",elapsed);
    test(B,C);

    printf("Normal comparison based ...");
    startTimer();
    for (int i=0 ; i<bSize ; i++){
        C[i]=compBST(B[i]);
    }
    elapsed = stopTimer();
    printf(" %.3f milliseconds.\n",elapsed);
    test(B,C);

	for (int j=1 ; j<5 ; j++) {
			printf("Slanted Comparison based with slant %d...",1<<j);
			startTimer();
			for (int i=0 ; i<bSize ; i++){
				C[i]=slcompBST(B[i],j);
			}
			elapsed = stopTimer();
			printf(" %.3f milliseconds.\n",elapsed);
			test(B,C);
	}

    return 0;
}
