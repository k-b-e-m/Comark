//  iclude’ is a keyword in C. Here, it loads the
// "dio.h" library so we can use the functions defined
// there. In this code e use the ’printf’ function that’s
// defined there.
#include <stdio.h>
// The main function will be executed when we run the program

void main(){
  char c=1;
  short s=1;
  int i=1;
  long l=1;
  long long ll=1;
  char* cp = &c;
  int* ip = &i;
  long* lp = &l;
  long long * llp = &ll;
  printf("Size of a char type is %lu byte or %lu bits.\n,Size of a int  type is %lu byte or %lu bits.\n,Size of a long type is %lu byte or %lu bits.\nSize of a longlong type is %lu byte or %lu bits.\n",sizeof(c),sizeof(c)*8,sizeof(i),sizeof(i)*8,sizeof(l),sizeof(l)*8,sizeof(ll),sizeof(ll)*8);
  printf("Size of a char* type is %lu byte or %lu bits.\n,Size of a int*  type is %lu byte or %lu bits.\n,Size of a long* type is %lu byte or %lu bits.\nSize of a longlong* type is %lu byte or %lu bits.\n",sizeof(cp),sizeof(cp)*8,sizeof(ip),sizeof(ip)*8,sizeof(lp),sizeof(lp)*8,sizeof(llp),sizeof(llp)*8);
  

  printf("i value before is %i\n",i);
  *ip=*ip+1;
  printf("i value after is %i\n",i);
}
