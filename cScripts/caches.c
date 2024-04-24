#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) // Time measurement for Windows
#include <sys/timeb.h>
struct _timeb startt,endt;
void startTimer() {
    _ftime_s(&startt);
}
long long stopTimer() {
    _ftime_s(&endt);
    return (endt.time-startt.time)*1000+(endt.millitm-startt.millitm);
}
#elif defined(__unix__) || defined(__APPLE__) // Time measurement for Unix and MacOS
struct timespec pTime,cTime;
#define CLOCK CLOCK_REALTIME
long long stopTimer() {
    clock_gettime(CLOCK,&cTime);
    return (cTime.tv_sec - pTime.tv_sec)*1000 + (cTime.tv_nsec - pTime.tv_nsec)/1000000;
}
void startTimer() {
    clock_gettime(CLOCK,&pTime);
}
#elif   // Unknown system, we don't support it for now!
#error "Unrecognized system. Add functions for time measurement to the code"
#endif

int main(int argn,char **argv){
    if (argn != 3){
        printf("Enter two parameters, size and val.\n");
        return -1;
    }
    int size=atol(argv[1]); 
    int val=atol(argv[2]); 
    int dummyResult=0;
    // Your code starts here ...
    int *A;
    A = (int*) malloc(size*sizeof(int));
  long power = 27; 
  long accesses = 1<<power;
  startTimer();
    for(long j = 0;j<accesses/size;j++){
      for(long i = 0;i<size;i++){
      A[i] = i+val;
        if(i%16==0){
          dummyResult += A[i];
        }
      } 
    }
  long long time= stopTimer();
  int sizeOfA = size*sizeof(int);
  printf("sizeOfA %d\n",sizeOfA);

  printf("Time to Run %lli\n",time);
    free(A);
    return dummyResult;
}
