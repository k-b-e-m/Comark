#include <stdio.h>  // Include stdio.h for printf function
#include <stdlib.h> // Include stdlib.h for malloc function

int main() {
    // Allocate memory for an array of 10 shorts
    short *S = malloc(sizeof(short) * 10);
    
    short *B;
    B = S;

    short *C = &S[2];
    
    // Print the memory address of the allocated memory
    printf("pointer: %p\n", S);
    int i = 0;
    for (i=0;i<10;i++) {
       S[i] =i; 
    }
    

    printf("S first three digits are: %i %i %i",S[0],S[1],S[2]);
    printf("\nB digits are: %i %i %i %i %i",B[0],B[1],B[2],B[3],B[4]);

    printf("\nC first three digits are: %i %i %i",C[0],C[1],C[2]);
    C[0] = C[0]+10;
    
    printf("\nS first three digits are: %i %i %i %i, %i",S[0],S[1],S[2],S[3],S[4]);

  // access by iterating over short *
  for (short *p = S; p < S+10 ; p = p + 1) {
  printf("%hd \n", *p);
  }
  
  // access by iterating over unsigned char *
  // needs extra arithmetic
  for (unsigned char *p = (unsigned char *)S;
  p < (unsigned char *)S+10*sizeof(short);
  p = p + sizeof(short)) {
  printf("%hd \n", *(short *)p);
  }

  // access by iterating over void *
  // needs extra arithmetic
  // (only in GNU C)
  for (void *p = S; p < (void *)S+10*sizeof(short); p = p + sizeof(short)) {
  printf("%hd \n", *(short *)p);
  }
  free(B);
  free(S);


    printf("S first three digits are: %i %i %i",S[0],S[1],S[2]);
    printf("\nB digits are: %i %i %i %i %i",B[0],B[1],B[2],B[3],B[4]);
    return 0; // Exit program successfully
}
