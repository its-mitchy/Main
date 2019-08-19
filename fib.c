#include <stdio.h>

int isprime(int test){
  int i, n;
  n = test;
  if(n <= 1)
    {
      return 0;
    }
  if(n <= 3)
	{
	  return 1;
	}
  if(n % 2 == 0 || n % 3 == 0)
	{
	  return 0;
	}
  i = 5;
  while(i*i <= n)
    {
      if(n % i == 0 || n % (i+2) == 0)
	{
	  return 0;
	}
      i+=i;
    }
  return 1;
}

int main(int argc, char* argv[]){
  int lim = atoi(argv[1]);
  int prev = 0; /* fib at i -1 */
  int curfib = 1; /* current fib */
  int nextfib = 0; /* next fib number, use cur and prev to calc */
  int i = 1;  /* index */ 
  int oddsum = 0; /* current oddsum */
  int primesum = 0; /* current primesum */
  
  while(curfib < lim){
    printf("Is prime result for i = %d, %d\n", i, isprime(i));
    if(isprime(i) == 1){
      primesum = primesum + curfib;
    }
    if(curfib % 2 != 0){
      oddsum = oddsum + curfib;
    }
    printf("Current i = %d\n", i);
    printf("Current Fib = %d\n", curfib);
    printf("Prev Fib = %d\n", prev);

    printf("Oddsum = %d\n", oddsum);
    printf("Primesum = %d\n", primesum);

    i = i + 1;
    nextfib = curfib + prev;
    prev = curfib;
    curfib = nextfib;
  }
  printf("Final Oddsum = %d\n", oddsum);
  printf("Final Primesum = %d\n", primesum);
}
