#ifndef __3100_BARRIERS_H_
#define __3100_BARRIERS_H_

#include <pthread.h>

typedef struct
{
  // TODO implement me!
  pthread_cond_t *bcond;
  pthread_mutex_t *bmutex;
  int size, waiting, currentGEN;

} barrier;

/* Initializes the barrier and all of its fields. 
 * sz - number of threads that can wait on this barrier. */
int barrier_init(barrier* b, int sz);

/* Destroys the barrier and frees memory, if necessary. */
int barrier_destroy(barrier* b);

/* Blocks current thread until all other threads have reached the barrier. */
int barrier_wait(barrier* b);

#endif
