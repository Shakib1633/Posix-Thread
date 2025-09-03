///Due to Mutex, the shared variable will not show a problem

#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mut; // # of mutexes = # of shared resources. Mutexes must be decaled globally.

void* routine(void *args) {
    printf("In threads");
    printf("\n");
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mut); // lock the critical section
           mails++;
        pthread_mutex_unlock(&mut); // lock the critical section
    }
}  // Now, even if thread switching occurs, value cannot be updated by the switched thread, it must wait for the other thread to leave the critical section and unlock it.

int main() {
    pthread_t p1, p2, p3, p4;  // 4 threads simultaneously will try to increment "mails"
    pthread_mutex_init(&mut, NULL); // initialise mails with default attributes of mutex.

    pthread_create(&p1, NULL, routine, NULL);
    pthread_create(&p2, NULL, &routine, NULL);
    pthread_create(&p3, NULL, routine, NULL);
    pthread_create(&p4, NULL, &routine, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    pthread_mutex_destroy(&mut);  // destroy mutex variable once work is done.

    printf("Number of mails: %d\n", mails);
    return 0;
}

/// there is ownership associated with a mutex, and only the owner can release the lock (mutex).
/// A mutex (mutual exclusion) is a synchronization tool that acts as a lock to protect shared resources from concurrent access by multiple threads,
/// ensuring only one thread can acquire the lock and enter the "critical section" (the part of the code that accesses the resource) at a time.
/// By preventing simultaneous access, mutexes prevent race conditions and guarantee the consistency of shared data.
