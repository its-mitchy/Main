#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ITERATIONS 10
#define DEFAULT_NWRITEJOBS 10
#define DEFAULT_NREADJOBS 10

#define work() do {random_r(&buf, &random); usleep(random % 50000);} while (0)
#define usedisk() do {random_r(&buf, &random); usleep(random % 10000);} while (0)

typedef struct disk {
    int    numwritejobs;        // number of writejobs in the disk
    int    numreadjobs;         // number of readjobs in the disk
    pthread_mutex_t mutex;      // mutex to protect shared info
    pthread_cond_t  available;  // condition variable
} disk_t;

typedef struct thread_data {
    int id;
    disk_t* shared_info;
} thr_data;

void * writejob(void * arg_orig) 
{
    thr_data *arg = arg_orig;
    int i, id = arg->id;
    disk_t* shared_info = arg->shared_info;

    int32_t random;
    struct random_data buf;
    char state[64];
    initstate_r(id, state, sizeof(state), &buf);

    for(i=0; i<ITERATIONS; i++){
        work();

        pthread_mutex_lock(&shared_info->mutex);
        while(shared_info->numreadjobs > 0) {  // must wait
            printf("writejob #%2d waits\n", id);
            pthread_cond_wait(&shared_info->available, &shared_info->mutex);
        }
        shared_info->numwritejobs++;
        printf("writejob #%2d enters\n", id);
        pthread_mutex_unlock(&shared_info->mutex);

        usedisk();

        pthread_mutex_lock(&shared_info->mutex);
        shared_info->numwritejobs--;
        if(shared_info->numwritejobs==0)
            pthread_cond_broadcast(&shared_info->available);
        printf("writejob #%2d exits\n", id);
        pthread_mutex_unlock(&shared_info->mutex);
    }
    return NULL;
}

void* readjob(void * arg_orig) 
{
    thr_data *arg = arg_orig;
    int i, id = arg->id;
    disk_t* shared_info = arg->shared_info;

    int32_t random;
    struct random_data buf;
    char state[64];
    initstate_r(id, state, sizeof(state), &buf);

    for(i=0; i<ITERATIONS; i++){
        work();

        pthread_mutex_lock(&shared_info->mutex);
        while(shared_info->numwritejobs > 0) {  // must wait
            printf("readjob  #%2d waits\n", id);
            pthread_cond_wait(&shared_info->available, &shared_info->mutex);
        }
        shared_info->numreadjobs++;
        printf("readjob  #%2d enters\n", id);
        pthread_mutex_unlock(&shared_info->mutex);

        usedisk();

        pthread_mutex_lock(&shared_info->mutex);
        shared_info->numreadjobs--;
        if(shared_info->numreadjobs==0)
            pthread_cond_broadcast(&shared_info->available);
        printf("readjob  #%2d exits\n", id);
        pthread_mutex_unlock(&shared_info->mutex);
    }
    return NULL;
}


int main(int argc, char *argv[]) 
{
    int i, n, nwritejobs = DEFAULT_NWRITEJOBS, nreadjobs = DEFAULT_NREADJOBS;

    for(i = 1; i < argc; i++) {
        if(strncmp(argv[i], "-w", strlen("-w")) == 0) {
            nwritejobs = atoi(argv[++i]);
        }
        else if(strncmp(argv[i], "-r", strlen("-r")) == 0) {
            nreadjobs = atoi(argv[++i]);
        }
        else {
            fprintf(stderr, "Usage: %s [-w N|-writejobs N] [-r N|-readjobs N]\n", argv[0]);
            return 1;
        }
    }

    disk_t shared_info;
    shared_info.numwritejobs = shared_info.numreadjobs = 0;
    pthread_mutex_init(&shared_info.mutex, NULL);
    pthread_cond_init(&shared_info.available, NULL);

    n = nwritejobs + nreadjobs;      // number of threads to create
    pthread_t tid[n];
    thr_data  data[n];

    for(i = 0; i < nwritejobs; i++) {
        data[i] = (thr_data){i,&shared_info};
        pthread_create(&tid[i], NULL, writejob, &data[i]);
    }
    for(i = nwritejobs; i < n; i++) {
        data[i] = (thr_data){i-nwritejobs,&shared_info};
        pthread_create(&tid[i], NULL, readjob, &data[i]);
    }
    for(i = 0; i < n; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

