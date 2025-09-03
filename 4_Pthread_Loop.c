///Thread Created using Loop

#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mut;

void* routine(void *args) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mut);
        mails++;
        pthread_mutex_unlock(&mut);
    }
}

int main() {
    pthread_t th[8];  // instead of declaring 8 thread variables, just declare an array of 8 threads, and create and join them from a loop.
    int i;
    pthread_mutex_init(&mut, NULL);
    for (i = 0; i < 8; i++) {
        pthread_create(&th[i], NULL, &routine, NULL);
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 8; i++) {
        pthread_join(th[i], NULL);
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mut);
    printf("Number of mails: %d\n", mails);
    return 0;
}

// if we create and join thread in the same loop, all the threads will run sequentially
// one after the other, instead of running concurrently.
