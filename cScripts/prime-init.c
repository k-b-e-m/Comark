#include <stdio.h>
#include <stdlib.h>
// We define our own boolean:
// Here, we can also do:
// enum {false, true}
#define true 1
#define false 0
// We define a boolean to be of type 'short int'
typedef short bool;
// Set MAX to a number such that this program takes around 20 seconds to run
#define MAX 7654321 // Increase this number if you are not using a VM

// A rather slow way to test if a number if prime
// The slowness is on purpose
bool isPrime(long n) {
  if (n == 1)
    return false;
  long test = 2;
  while (test * test <= n) {
    if (n % test == 0)
      return false;
    test++;
  }
  return true;
}

// A test function to test for a few values.
// primes is an array bools. primes[n] is true if
// the program thinks "n" is a prime number
// isprime is the actual answer and it is looked up online
// and passed to the function.
void test(long n, bool *primes, bool isprime) {
  if (n >= MAX) {
    printf("The number %ld is too big, error! error!\n", n);
    return;
  }
  if (primes[n] == isprime) {
    // Our tests were correct!
    printf("I was right! ");
  } else {
    printf("I was totally wrong! ");
  }

  if (isprime) {
    printf("%ld is a prime number.\n", n);
  } else
    printf("%ld is not a prime number.\n", n);
}

int main() {
  // An array that says which numbers are primes.
  // if "i" is a prime, then we set primes[i] to true (1)
  // else we set primes[i] to false (0).
  bool *primes;
  primes = malloc(MAX * sizeof(bool));

  int i;
  // Initialize all the number to be 'not prime'
  for (i = 0; i < MAX; i++)
    primes[i] = false;

  // Next, we go through all the numbers, and we set primes[i] to
  // 1 if "i" is a prime number.
  for (i = 2; i < MAX; i = i + 1) {
    if (isPrime(i))
      primes[i] = true;
  }

  printf("Initialization complete.\n");

  // Now testing.
  printf("Now Testing a few values.\n");
  test(4, primes, false);       // No!
  test(5, primes, true);        // Yes!
  test(13, primes, true);       // Yes!
  test(213, primes, false);     // No!
  test(3113, primes, false);    // No!
  test(41113, primes, true);    // Yes!
  test(511113, primes, false);  // No!
  test(6111113, primes, false); // No!
}
