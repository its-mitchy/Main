
#include <pthread.h>
#include "barrier.h"
#include <stdlib.h>

// TODO implement barrier functions here!

/* Initializes the barrier and all of its fields.                                                                                                                                   
 * sz - number of threads that can wait on this barrier. */

int barrier_init(barrier* b, int sz)
{
  b -> bmutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
  b -> bcond = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));

  pthread_mutex_init(b->bmutex,NULL);
  pthread_cond_init(b->bcond,NULL);

  b->size = sz;
  b->waiting = 0;
  b->currentGEN = 0;

  return 0;  
}

/* Destroys the barrier and frees memory, if necessary. */
int barrier_destroy(barrier* b)
{
  free(b->bmutex);
  free(b->bcond);
  
  return 0;
}
/* Blocks current thread until all other threads have reached the barrier. */
int barrier_wait(barrier* b)
{
  pthread_mutex_lock(b->bmutex);  //grab mutex
  ++b->waiting;   //one more waiting
  
  int localGEN = b->currentGEN;  //keep track of current generation in local var
  
  if(b->waiting == b->size)    //if this thread is last to arrive
    {
      b->waiting = 0;   //reset wait
      ++b->currentGEN;  //increment global counter
      pthread_cond_broadcast(b->bcond);   //wake threads
    }
  else
    { 
      while(localGEN == b->currentGEN)    //while the thread is in the correct generation
	{
	  pthread_cond_wait(b->bcond,b->bmutex);   //wait until signal
	}
    }
  
  pthread_mutex_unlock(b->bmutex);  //release the mutex
  return 0;
}
