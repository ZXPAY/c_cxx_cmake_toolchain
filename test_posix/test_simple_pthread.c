#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "semaphore.h"

void *task_1(void *arg);

int main() {
    int check;
    pthread_t thread1;
    void *thread_result;

    int count1 = 0;
    check = pthread_create(&thread1, NULL, task_1, (void *)&count1);
    assert(check == 0);

    printf("Waiting for thread finish\n");

    /* Join the thread */
    check = pthread_join(thread1, &thread_result);
    printf("%d\n", check);
    assert(check == 0);

    printf("Join result: %s\n", (char *)thread_result);
    

    printf("value is now %d\n", count1);

}

void *task_1(void *arg) {
    int *count = (int *)arg;
    *count = 100;
    pthread_exit("Change the count value");
}

