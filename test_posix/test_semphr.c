#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "semaphore.h"

void *task_1(void *arg);
void *task_2(void *arg);
sem_t sem1;
sem_t sem2;

int main() {
    int check;
    pthread_t thread1, thread2;
    void *thread_result1, *thread_result2;

    printf("Initialize semaphore\n");
    check = sem_init(&sem1, 0, 0); 
    assert(check == 0);
    check = sem_init(&sem2, 0, 0); 
    assert(check == 0);


    int count = 0;
    check = pthread_create(&thread1, NULL, task_1, (void *)&count);
    assert(check == 0);

    check = pthread_create(&thread2, NULL, task_2, (void *)&count);
    assert(check == 0);

    printf("Waiting for thread finish\n");

    /* Join the thread */
    check = pthread_join(thread1, &thread_result1);
    assert(check == 0);

    check = pthread_join(thread2, &thread_result2);
    assert(check == 0);

    printf("Join result1: %s\n", (char *)thread_result1);
    printf("Join result2: %s\n", (char *)thread_result2);
    

}

void *task_1(void *arg) {
    int *count = (int *)arg;
    sem_post(&sem1);
    while(true) {
        sem_wait(&sem2);
        (*count)++;
        printf("1: %d\n", *count);
        sem_post(&sem1);
        if(*count >= 10) {
            break;
        }
    }

    pthread_exit("Exit task1");
}

void *task_2(void *arg) {
    int *count = (int *)arg;

    while(true) {
        sem_wait(&sem1);
        (*count)++;
        printf("2: %d\n", *count);
        sem_post(&sem2);
        if(*count >= 10) {
            break;
        }
    }

    pthread_exit("Exit task2");
}


