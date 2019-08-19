#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* This structure stores all of the
 * variables that are shared between
 * the two threads. Handle with care. */
typedef struct {
	int          idx;  /* index of this thread */
	long long *a, *b;  /* vectors to dot product */
	int          dim;  /* dimensionality of vectors */
	long long   psum;  /* partial dot product */
} thread_data;

/* This is the function each thread will call
 * to do the work of computing the partial dot
 * product. */
void* worker(void* arg) {
	thread_data* dat;
	int     idx, dim;
	long long *a, *b;
	
	/* Get thread arguments */
	dat = (thread_data*) arg;
	idx = dat->idx;
	a = dat->a;
	b = dat->b;
	dim = dat->dim;
	
	/* TODO compute partial dot product 
	 * and safely exit the thread... */

	long long psum;
	psum = dat -> psum;

	int start, end;
	switch(idx){
	case 1 : 
	  start = 0;
	  end = (dim/2) -1;
	  break;
	case 2 :
	  start = (dim/2);
	  end = dim-1;
	  break;
	}
	//switch to handle which thread does what work
	//thread 1 works on the first half of a and back half of b
	//thread 2 works on the opposite

	int i;
	for(i = start; i <= end; i++){
	  dat->psum += a[i]*b[dim-i-1];
	}
	//for loop from the respective start to finishes
	
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	
	int dim;
	
	/* Parse program arguments */
	if(argc != 2) {
		printf("usage: ./dot <dimensionality>\n");
		exit(2);
	}
	dim = atoi(argv[1]);
	printf("dim = %d\n", dim);
	/* TODO initialize thread data structure,
	 * create threads, wait for them to terminate,
	 * add the partial sums together, then print! */

	long long * arya = (long long *)malloc(sizeof(long long)*dim);
	long long * aryb = (long long *)malloc(sizeof(long long)*dim);

	thread_data * thd1 = (thread_data*)malloc(sizeof(thread_data));  //init thread data 1
	thread_data * thd2 = (thread_data*)malloc(sizeof(thread_data));  //init thread data 2
	
	//malloc for long arrays a and b
	//and thread data structs

	long i;
	
	for(i = 0; i <= dim-1; i++){
	  arya[i] = (long long)i + 1;
	  aryb[i] = (long long)i + 1;
	}
	//fill arrays from 1 to dim

	thd1 -> idx =(int) 1;
	thd2 -> idx =(int) 2;
	
	thd1 -> a = arya;
	thd2 -> a = arya;
	
	thd1 -> b = aryb;
	thd2 -> b = aryb;

	thd1 -> psum = 0;
	thd2 -> psum = 0;

	thd1 -> dim = dim;
	thd2 -> dim = dim;
	//set struct variables respectively
	
	pthread_t th1, th2;
	//pthread id's
	
	pthread_create(&th1, NULL,(void*) worker,(void*) thd1);
	pthread_create(&th2, NULL,(void*) worker,(void*) thd2);
	//calling create, void casts of each threads work function and respective structure

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	//joining threads to wait
	
	long long finalsum = thd1 -> psum + thd2 -> psum;
	//produce final sum
	
	printf("Dot %llu\n", finalsum);
	//print final sum
	
	/* Done! */
	return 0;
}
