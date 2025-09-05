#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <pthread.h>

// int cnt=0;
// void* add(void* arg) {
//     cnt++;
//     return NULL;
// }

// int 
// main(int argc, char ** args)
// {

//     pthread_t thread;
//     // for(int i=0; i<=100; i++) {
//     while (1) {
//         pthread_create(&thread, NULL, add, NULL);
//         pthread_join(thread, NULL);

//         printf("%d\n", cnt);
//         if(cnt == 100) {
//             printf("%d\n", cnt);
//             break;
//         }
//     }
//     // }

//    return 0;
// }

// #include <stdio.h>
// #include <pthread.h>

// # define NC "\e[0m"
// # define YELLOW "\e[1;33m"

// // thread_routine is the function the thread invokes right after its
// // creation. The thread ends at the end of this function.
// void *thread_routine(void *data)
// {
//  pthread_t tid;

//  // The pthread_self() function provides
//  // this thread's own ID.
//  tid = pthread_self();
//  printf("%sThread [%ld]: The heaviest burden is to exist without living.%s\n",
//   YELLOW, tid, NC);
//  return (NULL); // The thread ends here.
// }

// int main(void)
// {
//  pthread_t tid1; // First thread's ID
//  pthread_t tid2; // Second thread's ID

//  // Creating the first thread that will go
//  // execute its thread_routine function.
//  pthread_create(&tid1, NULL, thread_routine, NULL);
//  printf("Main: Created first thread [%ld]\n", tid1);
//  // Creating the second thread that will also execute thread_routine.
//  pthread_create(&tid2, NULL, thread_routine, NULL);
//  printf("Main: Created second thread [%ld]\n", tid2);
//  // The main thread waits for the new threads to end
//  // with pthread_join.
//  pthread_join(tid1, NULL);
//  printf("Main: Joining first thread [%ld]\n", tid1);
//  pthread_join(tid2, NULL);
//  printf("Main: Joining second thread [%ld]\n", tid2);
//  return (0);
// }

// #include <stdio.h>
// #include <pthread.h>

// Each thread will count TIMES_TO_COUNT times
// #define TIMES_TO_COUNT 21000

// #define NC "\e[0m"
// #define YELLOW "\e[33m"
// #define BYELLOW "\e[1;33m"
// #define RED "\e[31m"
// #define GREEN "\e[32m"

// // This structure contains the count as well as the mutex
// // that will protect the access to the variable.
// typedef struct s_counter
// {
//  pthread_mutex_t count_mutex;
//  unsigned int count;
// } t_counter;

// void *thread_routine(void *data)
// {
//  // Each thread starts here
//  pthread_t tid;
//  t_counter *counter; // pointer to the structure in main
//  unsigned int i;

//  tid = pthread_self();
//  counter = (t_counter *)data;
//  // Print the count before this thread starts iterating.
//  // In order to read the value of count, we lock the mutex:
//  pthread_mutex_lock(&counter->count_mutex);
//  printf("%sThread [%ld]: Count at thread start = %u.%s\n",
//   YELLOW, tid, counter->count, NC);
//  pthread_mutex_unlock(&counter->count_mutex);
//  i = 0;
//  while (i < TIMES_TO_COUNT)
//  {
//   // Iterate TIMES_TO_COUNT times
//   // Increment the counter at each iteration
//   // Lock the mutex for the duration of the incrementation
//   pthread_mutex_lock(&counter->count_mutex);
//   counter->count++;
//   pthread_mutex_unlock(&counter->count_mutex);
//   i++;
//  }
//  // Print the final count when this thread finishes its
//  // own count, without forgetting to lock the mutex:
//  pthread_mutex_lock(&counter->count_mutex);
//  printf("%sThread [%ld]: Final count = %u.%s\n",
//   BYELLOW, tid, counter->count, NC);
//  pthread_mutex_unlock(&counter->count_mutex);
//  return (NULL); // Thread termine ici.
// }

// int main(void)
// {
//  pthread_t tid1;
//  pthread_t tid2;
//  // Structure containing the threads' total count:
//  t_counter counter;

//  // There is only on thread here (main thread), so we can safely
//  // initialize count without using the mutex.
//  counter.count = 0;
//  // Initialize the mutex :
//  pthread_mutex_init(&counter.count_mutex, NULL);
//  // Since each thread counts TIMES_TO_COUNT times and that
//  // we have 2 threads, we expect the final count to be
//  // 2 * TIMES_TO_COUNT:
//  printf("Main: Expected count is %s%u%s\n", GREEN,
//      2 * TIMES_TO_COUNT, NC);
//  // Thread creation:
//  pthread_create(&tid1, NULL, thread_routine, &counter);
//  printf("Main: Created first thread [%ld]\n", tid1);
//  pthread_create(&tid2, NULL, thread_routine, &counter);
//  printf("Main: Created second thread [%ld]\n", tid2);
//  // Thread joining:
//  pthread_join(tid1, NULL);
//  printf("Main: Joined first thread [%ld]\n", tid1);
//  pthread_join(tid2, NULL);
//  printf("Main: Joined second thread [%ld]\n", tid2);
//  // Final count evaluation:
//  // (Here we can read the count without worrying about
//  // the mutex because all threads have been joined and
//  // there can be no data race between threads)
//  if (counter.count != (2 * TIMES_TO_COUNT))
//   printf("%sMain: ERROR ! Total count is %u%s\n",
//      RED, counter.count, NC);
//  else
//   printf("%sMain: OK. Total count is %u%s\n",
//      GREEN, counter.count, NC);
//  // Destroy the mutex at the end of the program:
//  pthread_mutex_destroy(&counter.count_mutex);
//  return (0);
// }
//
int cnt = 0;
void *thread(void *data)
{
    // Each thread starts here
    pthread_t tid;
    pthread_mutex_t    mutex = *(pthread_mutex_t*)data;
    tid = pthread_self();
    pthread_mutex_lock(&mutex);
    cnt++;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
    pthread_t tid1;
    pthread_t tid2;

    pthread_mutex_t    mutex;
    pthread_mutex_init(&mutex, NULL);

    while(1){
        pthread_create(&tid1, NULL, thread, &mutex);
        pthread_create(&tid2, NULL, thread, &mutex);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
        printf("%d\n", cnt);
        if(cnt == 100) {
            break;
        }

    }

    // pthread_mutex_lock(&mutex);
    // pthread_mutex_unlock(&mutex);

    // pthread_mutex_destroy(&mutex);

    return 0;
}
