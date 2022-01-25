#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "semaphore.h"


pthread_mutex_t test_mutex;

void *task_1(void *arg);
void *task_2(void *arg);

int main() {
    int check;
    pthread_t thread1, thread2;
    void *thread_result1, *thread_result2;

    check = pthread_mutex_init(&test_mutex, NULL);
    assert(check == 0);

    int count = 0;
    check = pthread_create(&thread1, NULL, task_1, &count);
    assert(check == 0);

    check = pthread_create(&thread2, NULL, task_2, &count);
    assert(check == 0);

    pthread_mutex_unlock(&test_mutex);


    check = pthread_join(thread1, &thread_result1);
    assert(check == 0);

    check = pthread_join(thread2, &thread_result2);
    assert(check == 0);

    printf("Join result1: %s\n", (char *)thread_result1);
    printf("Join result2: %s\n", (char *)thread_result2);

    return 0;
}

void *task_1(void *arg) {
    int *count = (int *)arg;
    for(int i=0;i<10;i++) {
        pthread_mutex_lock(&test_mutex);
        (*count)++;
        pthread_mutex_unlock(&test_mutex);
        printf("1: %d\n", *count);
    }
    printf("task1 done\n");
    pthread_exit("Exit task1");
}

void *task_2(void *arg) {
    int *count = (int *)arg;
    for(int i=0;i<10;i++) {
        pthread_mutex_lock(&test_mutex);
        (*count)++;
        pthread_mutex_unlock(&test_mutex);
        printf("2: %d\n", *count);
    }
    printf("task2 done\n");
    pthread_exit("Exit task2");
}
