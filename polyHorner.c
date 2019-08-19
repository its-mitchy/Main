#include <stdio.h>
#include <stdlib.h>

int exponential(double base, int power){
  int i;
  for(i = 1; i < power; i++){
    base = base * base;
  }
  return base;
}


// array coefs has (n+1) elements
double poly(double x, int n, double coefs[n+1])  //x degree coef
{
    double ttl = 0;
    // TODO
    int i;
    for(i=0; i <= n; i++){
      double temp = coefs[i];
      if(i==0)
	{
	  ttl = ttl + temp;
	}
      else
	{
	  ttl = ttl + temp * exponential(x,i); 
	}
    }
    return ttl;
}

// read n+1 doubles into coefs. 
// remember array coefs has (n+1) elements
// read the doulbe into a temporary variable first.
void readPoly(int degree, double coefs[degree+1])
{
    double c;
    int i;
    for(i=0; i <= degree; i++){
      scanf("%lf", &c);
      coefs[i] = c;
    }
    // Write a loop that reads a double (into c) and copies 
    // c into array coefs[0], coefs[1], and so on.
    // Study the code in main() to learn how to read a double.
    // TODO

}

int main(int argc,char* argv[])
{
    int degree = 0;
    int readOK;

    readOK = scanf("%d", &degree);
    while (readOK && degree >= 0) {
        double coefs[degree+1];    
        readPoly(degree, coefs);
	
	double x;
	printf("x = ");
	readOK = scanf("%lf", &x);
	
    
    
	if (readOK) {
	  double value = poly(x, degree, coefs);
	  printf("P(%lf)=%lf\n", x, value);
	  readOK = scanf("%d", &degree);
	}
    }
    return 0;
}
