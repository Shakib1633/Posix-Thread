#include<bits/stdc++.h>
#include<pthread.h>
#include<windows.h>

using namespace std;

int fuel=0;
pthread_mutex_t mx;
pthread_cond_t cV;

void* fn1 (void* args){
    for (int i=0; i<25; i++) {
            pthread_mutex_lock(&mx);
            fuel+=2;
            cout<<"Filled fuel. Now containing "<< fuel<<" fuel"<<endl;
            pthread_mutex_unlock(&mx);
            pthread_cond_signal(&cV);
    }
}
void* fn2 (void* args){
    pthread_mutex_lock(&mx);
    while (fuel<30){
        /// conditional wait
        cout<<"Not sufficient fuel"<<endl;
        pthread_cond_wait(&cV, &mx);
        ///Unlock mx
        ///Wait for signal
    }
    fuel-=30;
    pthread_mutex_unlock(&mx);
}
int main(){
    pthread_t t1, t2;
    pthread_mutex_init(&mx, NULL);
    pthread_cond_init(&cV, NULL);

    pthread_create(&t1, NULL, fn1, NULL); /// Producer
    pthread_create(&t2, NULL, fn2, NULL); /// Consumer

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&mx);
    pthread_cond_destroy(&cV);
}
