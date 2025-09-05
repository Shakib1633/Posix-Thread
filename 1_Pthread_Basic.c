#include <stdio.h>
#include <pthread.h>

// A void pointer is a pointer in C and C++ that does not have an associated data type.
// This means it can point to any type of data and store the memory address of any variable, regardless of its data type.

void* computation(void* add) //Must provide argument as void* and return type as void*, for a thread function.
{
  int* add_num = (int *) add;
  //Or, int val = * (int *) add;

  int sum=0;
  for (int i = 0; i < 1000000000; i++)
    sum += *add_num;
    //Or, sum += val

  printf("%d\n",sum);

  return NULL;  // Must return either NULL or something else
}

int main()
{
// pthread_t will be used to uniquely identify, create, and manage KERNEL-LEVEL threads
  pthread_t thread1;
  pthread_t thread2;

  int value1 = 1;
  int value2 = 2;

  // every thread takes a function on which it will execute.
  // arg-1 thread's address.                    arg-2 thread related attributes.
  // arg-3 function name/function's address.    arg-4 void* typecasted function parameters.
  pthread_create(&thread1, NULL, computation, (void*) &value1); // two threads run computation function with values 1 and 2.
  pthread_create(&thread2, NULL, computation, (void*) &value2);

  // arg-1 thread name.
  // arg-2 void** typecasted function's return type. this argument expects the address of the function's return value. And the return value itself is void pointer.
  pthread_join(thread1, NULL); // threads join to the main thread after execution is over.
  pthread_join(thread2, NULL); // join function waits for that thread to complete execution.

  return 0;
}




/// Same code if pthread was not used. Performance time would be almost double than the thread implemented code.
/**

void computation(int add)
  int sum=0;
  for (int i = 0; i < 1000000000; i++)
    sum += add;

  printf("%d\n",sum);

  return NULL;
}

int main()
{
  computation(value1);
  computation(value2);
  return 0;
}

**/








/// Question-- Difference between
///
/// pthread_create t1
/// pthread_create t2
/// pthread_join t1
/// pthread_join t2
///
/// and
///
/// pthread_create t1
/// pthread_join t1
/// pthread_create t2
/// pthread_join t2
///
/// ?







/// Visualizations of single-threaded vs. multi-threaded execution.
///
///
///             Single-Threaded Program
///
///          |   int x;
///          |   x = 20;
///          |   int y;
///  Time    |   y = 50;
///          |   int sum;
///          |   sum = x + y;
///
///
///
///
///              Multi-Threaded Program
///
///          |   int x;                 |  int a;
///          |   x = 20;                |  a = 3;
///          |   int y;                 |  int b;
///  Time    |   y = 50;                |  b = 5;
///          |   int sum;               |  int product;
///          |   sum = x + y;           |  product = a * b;
///
///
///          Parallel Execution
///
///
///
///              Multi-Threaded Program
///
///          |   int x;                 |
///          |                          |  int a;
///          |                          |  a = 3;
///          |   x = 20;                |
///          |   int y;                 |
///          |                          |  int b;
///  Time    |   y = 50;                |
///          |                          |  b = 5;
///          |                          |  int product;
///          |   int sum;               |
///          |   sum = x + y;           |
///          |                          |  product = a * b;
///
///
///          Concurrent But Not Parallel Execution
///
///
///
///              Multi-Threaded Program
///
///          |                             pthread
///          |
///          |   sum = x + y;
///          |   pthread_create --------   function()
///          |   ...                    |  int a = 5;
///          |   printf("%d", sum);     |  int b = 3;
///  Time    |   ...                    |  int result = x + y;
///          |   pthread_join   --------
///          |   ...       \
///          |   ...        \
///                          \
///                           \
///                     execution PAUSES here until thread done
///
///

