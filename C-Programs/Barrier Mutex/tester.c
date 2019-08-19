#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "barrier.h"

#define MAX_WAIT 2

typedef struct
{
	int    idx;  /* thread index */
	barrier* b;  /* barrier to wait with */
} fooargs;

void foo(fooargs* args)
{
	int i;
	for(i = 0; i < 10; ++i) {
		printf("thread %d starting! (gen %d)\n", args->idx, i); fflush(stdout);
		unsigned int busytime = (double)random() / RAND_MAX * MAX_WAIT * 1000000;
		usleep(busytime);  /* use of deprecated function ¯\_(ツ)_/¯ */
		printf("thread %d waiting... (gen %d)\n", args->idx, i); fflush(stdout);
		barrier_wait(args->b);
	}
	printf("thread %d done!\n", args->idx);
}

int main(int argc, char* argv[])
{
	/* Optionally get number of threads from args. */
	int n = 4;
	if(argc > 1)
		n = atoi(argv[1]);
	
	int i, ret;
	pthread_t thrds[n];
	fooargs    args[n];
	barrier          b;
	
	/* Initialize barrier. */
	ret = barrier_init(&b, n);
	if(ret != 0) {
		fprintf(stderr, "failed to init barrier with error code %d\n", ret);
		exit(ret);
	}
	
	/* Initialize arguments to each thread. */
	for(i = 0; i < n; ++i) {
		args[i].idx = i;
		args[i].b = &b;
	}
	
	/* Create threads. */
	for(i = 0; i < n; ++i) {
		ret = pthread_create(&thrds[i], NULL, (void*(*)(void*))foo, &args[i]);
		if(ret != 0) {
			fprintf(stderr, "failed to create thread with error code %d\n", ret);
			exit(ret);
		}
	}
	
	/* Join threads as they terminate. */
	for(i = 0; i < n; ++i) {
		ret = pthread_join(thrds[i], NULL);
		if(ret != 0) {
			fprintf(stderr, "failed to join thread with error code %d\n", ret);
			exit(ret);
		}
	}
	
	/* Destroy barrier. */
	ret = barrier_destroy(&b);
	if(ret != 0) {
		fprintf(stderr, "failed to destroy barrier with error code %d\n", ret);
		exit(ret);
	}
	
	/* Done! */
	return 0;
}
