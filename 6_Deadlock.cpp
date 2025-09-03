#include<bits/stdc++.h>
#include<pthread.h>
#include<windows.h>
using namespace std;

int a, b;
pthread_mutex_t mx_a, mx_b;

void* fn1 (void* args)
{
    pthread_mutex_lock(&mx_a);
    cout<<"Accessing variable a"<<endl;

    cout<<"Waiting for variable b"<<endl;
    Sleep(5); //thread switching occurs, once the current thread goes to sleep.

    pthread_mutex_lock(&mx_b);
    cout<<"Accessing variable b"<<endl;

    pthread_mutex_unlock(&mx_a);
    pthread_mutex_unlock(&mx_b);

    return NULL;
}

void* fn2 (void* args)
{
    pthread_mutex_lock(&mx_b);
    cout<<"Accessing variable b"<<endl;

    cout<<"Waiting for variable a"<<endl;
    Sleep(5);

    pthread_mutex_lock(&mx_a);
    cout<<"Accessing variable a"<<endl;

    pthread_mutex_unlock(&mx_b);
    pthread_mutex_unlock(&mx_a);

    return NULL;
}

int main()
{
    pthread_mutex_init(&mx_a, NULL);
    pthread_mutex_init(&mx_b, NULL);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, fn1, NULL);
    pthread_create(&t2, NULL, fn2, NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&mx_a);
    pthread_mutex_destroy(&mx_b);
}
