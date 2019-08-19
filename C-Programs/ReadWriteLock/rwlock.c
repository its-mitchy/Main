#include <pthread.h>
#include "error.h"
#include "rwlock.h"

//i learned from searching around the web that in order to avoid starvation/ deadlocks you need to lock the mutex BEFORE you check any predicate value
int rwlock_rdlock(rwlock* lk) {
	// TODO implement me!
  pthread_mutex_lock(&lk->mutex);  //initally lock the mutex
  
  if((lk -> w_active != 0) && (lk -> w_wait != 0))   //if the conditions for a reader to have the lock are not met
    {
      pthread_mutex_unlock(&lk->mutex);   //then you need to unlock it
      ++lk->r_wait;        //and now theres one more reader waiting
    } 
  else 
    {
      ++lk->r_active;  //else the reader still has the lock and increment active readers
    }
  while(lk -> w_active != 0)   //assuming the reader has unlocked mutex it now waits for signal
    { 
      pthread_cond_wait(&lk->readcond, &lk->mutex);
      
    }
  return 0;
}

int rwlock_wrlock(rwlock* lk) {
  // TODO implement me!
  
  pthread_mutex_lock(&lk->mutex);   //same idea as above, lock mutex
  
  if(lk -> r_active != 0)   //then check neccessary conditions
    { 
      pthread_mutex_unlock(&lk->mutex);  //if they arent met we unlock
      ++lk -> w_wait;   //and waitlist the writer (lol like uconn enrollment)
    }
  else
    {
      ++lk->w_active;   //else the writer can have the mutex and do it work
    }
  while(lk -> r_active != 0)   //if the above all failed, writer waits on signal
     {
       pthread_cond_wait(&lk->writecond, &lk->mutex);
     } 
  return 0;
}

int rwlock_rdunlock(rwlock* lk) {
  // TODO implement me!
  
  pthread_mutex_unlock(&lk -> mutex);  //unlock mutex
  --lk -> r_active;                    //adjust active readers count
  pthread_cond_signal(&lk -> writecond); //signal writer it might be its turn
  
  return 0;
}

int rwlock_wrunlock(rwlock* lk) {
  // TODO implement me!
  
  pthread_mutex_unlock(&lk -> mutex);  //unlock mutex
  --lk -> w_active;                    //adjust active writers count
  pthread_cond_broadcast(&lk -> readcond);  //broadcast a signal to all readers since they can read at the same time
 
  return 0;
}

int rwlock_init(rwlock* lk) {
	int st;
	
	/* Initialize mutex, check for errors */
	st = pthread_mutex_init(&lk->mutex, NULL);
	if(st) {
		pthread_mutex_destroy(&lk->mutex);
		return st;
	}
	
	/* Initialize condition variables, check for errors */
	st = pthread_cond_init(&lk->readcond, NULL);
	if(st) {
		pthread_cond_destroy(&lk->readcond);
		return st;
	}
	st = pthread_cond_init(&lk->writecond, NULL);
	if(st) {
		pthread_cond_destroy(&lk->writecond);
		return st;
	}
	
	/* Initialize all other variables to zero */
	lk->r_active = lk->w_active = 0;
	lk->r_wait = lk->w_wait = 0;
	lk->is_dead = 0;
	
	/* Done! */
	return 0;
}

int rwlock_destroy(rwlock* lk) {
	int st,str,stw,stu;
	
	/* Make sure the lock hasn't already been destroyed */
	if(lk->is_dead) return ERROR_INVALID;
	
	st = pthread_mutex_lock(&lk->mutex);
	if(st) return st;
	
	/* Ensure no one is using this lock */
	if(lk->r_active > 0 || lk->w_active > 0) {
		pthread_mutex_unlock(&lk->mutex);
		return ERROR_BUSY;
	}
	
	/* Ensure no one is waiting to use this lock */
	if(lk->r_wait != 0 || lk->w_wait != 0) {
		pthread_mutex_unlock(&lk->mutex);
		return ERROR_BUSY;
	}
	
	/* Destroy all of the POSIX stuff */
	lk->is_dead = 1;
	str = pthread_cond_destroy(&lk->readcond);
	stw = pthread_cond_destroy(&lk->writecond);
	st = pthread_mutex_unlock(&lk->mutex);
	if(st) return st;
	st = pthread_mutex_destroy(&lk->mutex);
	return (st ? st : (str ? str : stw));
}
