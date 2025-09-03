///Due to thread switching the shared variable shows some problem

#include <stdio.h>
#include <pthread.h>

int mails = 0; // shared variable, so make it global. Multiple threads might access this variable at the same time.

void* routine(void* args) {

    for (int i = 0; i < 1000000; i++)
    {
        mails++;  // this is not an atomic instruction.
    }
        // 1- read mails value into register      MOV AX, mails
        // 2- increment register value            INC AX
        // 3- write register value into mails     MOV mails, AX

// What if the scheduler decided to switch between threads in the middle of reading the mails value?
    return NULL;
}

int main() {
    pthread_t t1,t2;
    pthread_create(&t1,NULL,routine,NULL);
    pthread_create(&t2,NULL,routine,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("Number of mails: %d\n", mails); // mails value supposed to be 2000000. but it is not.
    return 0;
}



///  What is a race condition?
///
///  A race condition occurs when a program depends on the
///  timing of one or more events to function correctly.
///
///  A race condition typically occurs when multiple threads
///  access a shared variable (or state) at the same time.
///
///
///  Visualization of the above program's execution.  When the two
///  functions run at the same time, the execution of statements over time
///  may interleave, causing a race condition to occur when they access the same shared state.
///  See how both threads access "mails", update "mails", and write
///  "mails" in such a way as to result in an incorrect value finally!
///
///
///  Thread #1             Thread #2                  mails
///
///  MOV AX, mails  <----------------------------------- 0
///  AX = 0
///                        MOV AX, mails  <------------- 0
///                        AX = 0
///
///  INC AX
///  AX = 1
///                        INC AX
///                        AX = 1
///
///  MOV mails, AX  -----------------------------------> 1
///  mails = 1
///                        MOV mails, AX  -------------> 1
///                        mails = 1






///  Supposed to be
///
///  Thread #1             Thread #2                  mails
///
///  MOV AX, mails  <----------------------------------- 0
///  AX = 0
///
///  INC AX
///  AX = 1
///
///  MOV mails, AX  -----------------------------------> 1
///  mails = 1
///
///
///
///
///                        MOV AX, mails  <------------- 1
///                        AX = 1
///
///                        INC AX
///                        AX = 2
///
///                        MOV mails, AX  -------------> 2
///                        mails = 2
///
///  Solution? Use MUTEX
