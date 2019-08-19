#include <stdio.h>
#include <stdlib.h>

void readPerm(int perm[], int len);
int  checkPerm(const int perm[], int len);

int main() 
{
    int length;
    int readOK;

    readOK = scanf("%d", &length);
    while (readOK && (length > 0)) {
        int perm[length+1];
        readPerm(perm, length);    

        int isSuper = checkPerm(perm, length); 
        printf("%ssuper\n", (isSuper ? "" : "not ")); 

        readOK = scanf("%d", &length);
    }
    return 0;
}

/*
    Read len integers, and save them to perm[1], perm[2], and so on.

    perm has (len + 1) elements. 0, 1, ..., len.
    perm[0] is not used. It is safe to write to perm[len].
*/
void readPerm(int perm[], int len)
{
  
  int i;
  int readint;
  for(i=1; i<=len; i++){
    scanf("%d", &readint);
    perm[i] = readint;
  }

    // Write a loop to read len integers.
    // In each iteration, use scanf to read an integer into 
    // a temporary variable, and then copy it to the right 
    // element in the array. 
    // Remember to start with perm[1].
    // TODO
}

// return 1 for superpermutations, 0 otherwise.
// remember 
//  1. perm has (len + 1) elements. perm[0] is not used. 
//  2. check if the value is between 1 and len.
int  checkPerm(const int perm[], int len)
{
    // TODO
    int isSuper = 1;
    int i;
    for(i=1; i <= len; i++){
      if(perm[i] > len)      //testing if 1 < perm[i] < len
	{
	  return isSuper = 0;
	}
      if(perm[perm[i]] == i) //perm test case
	{ 
	  isSuper = 1;
	  continue;
	}
      else
	{
	  isSuper = 0;        //else not super perm
	}
    }
    return isSuper;
}
