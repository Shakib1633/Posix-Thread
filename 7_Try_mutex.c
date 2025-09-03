#include <stdio.h>
#include <pthread.h>
#include<windows.h>


int mails[5];
pthread_mutex_t mux[5];

void* routine(void *args) {
    for (int i = 0; i < 100000; i++) {
        for (int j = 0; j < 5; j++) {
            if (pthread_mutex_trylock(&mux[j])==0){
                    ///Critical Region
                    mails[j]++;
                    pthread_mutex_unlock(&mux[j]);
                    break;
            }
            if (j==4) j=0;
        }
    }
}

int main(int argc, char* argv[]) {
    pthread_t p[5];

    for (int i=0; i<5; i++){
        pthread_mutex_init(&mux[i], NULL);
    }

    for (int i=0; i<5; i++){
        pthread_create(&p[i], NULL, routine,  NULL);
    }

    for (int i=0; i<5; i++){
        pthread_join(p[i], NULL);
    }

    for (int i=0; i<5; i++){
        printf("Number of mails: %d\n", mails[i]);
    }
    for (int i=0; i<5; i++){
        pthread_mutex_destroy(&mux[i]);
    }

    printf("%d",mails[0]+mails[1]+mails[2]+mails[3]+mails[4]);
    return 0;
}
