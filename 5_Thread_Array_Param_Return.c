#include<stdio.h>
#include<pthread.h>

// 4 threads will calculate the sum of each part of the array simultaneously, and then
// all the thread sums will be added at the end of the program.

//         t[0]         t[1]       t[2]         t[3]
// index     0-----|     3-----|     6-----|      9--------|
int arr[12]={1, 2, 3,    4, 5, 6,    7, 8, 9,     10, 11, 12};

// No need for mutex, eventhough the array is a shared resource. As, there will be no overlap of accessing values between threads.

void* fn(void* args){
    int a = *(int *) args;

    int * sum = (int *) malloc(sizeof(int));  // the value that will be returned, must use a pointer that will be dynamically allocated, or else it will lead to dangling pointer after the variable goes out of scope.
    *sum=0;

    for (int i=a; i<a+3; i++){
        *sum = *sum + arr[i];
    }
    return (void*)sum;
}

int main()
{
    pthread_t p[4];
    for (int i=0; i<4; i++)
    {
        int * a = (int *) malloc(sizeof(int));
        *a = (12/4)*i;
        pthread_create(&p[i], NULL, fn, (void *) a);

        //Or, int a = 3*i; /// 0 3 6 9
        //    pthread_create(&p[i], NULL, fn, (void *) &a);
    }

    int total=0;
    int *Thread_sum;
    for (int i=0; i<4; i++)
    {
        pthread_join(p[i],  (void **)&Thread_sum);
        printf("%d th thread's sum = %d \n",i,*Thread_sum);
        total = total + (*Thread_sum);
    }
    printf("Total Array Sum: %d",total);

}
