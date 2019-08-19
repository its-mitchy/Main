/* This program should take read a single integer via standard input then
 * compute its factorial. For example, if I enter 5, the program should
 * output 120 because 1*2*3*4*5=120. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int factorial(int n) {
  assert(n>=0);
  int result;
  if(n == 0)
    {
      return result = 1;
    }
  result = n  * factorial(n-1);
  return result;
}

int main(int argc, char *argv[]) {
	int n, result;
	if(argc != 2) 
	  {
		fprintf(stderr, "usage: factorial n, n >=0\n");
		return 1;
	  }
	n = atoi(argv[1]);
	result = factorial(n);
	printf("%d\n", result);
	return 0;
}

