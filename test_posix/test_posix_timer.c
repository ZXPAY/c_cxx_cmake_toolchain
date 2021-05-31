#ifdef __linux__

#include <time.h>
#include <signal.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

static void print_current_system_time() {
    time_t now;
    time(&now);

    printf("now: %s", ctime(&now));
}

void timer_handler(union sigval arg) {
    static int first_time_flag = 1;
    printf("========================================\n");
    if(first_time_flag) printf("after 3 second , one shot timer\n");
    else printf("1 second period timer\n");
    first_time_flag = 0;
    print_current_system_time();
    printf("========================================\n");
}

void init_my_timer(void) {
    int ret;
    // Initialize the signal event
    struct sigevent sigevt;
    char oneshot_para[] = "I am one shot timer";
    memset(&sigevt, 0, sizeof(struct sigevent));

    sigevt.sigev_value.sival_ptr = (char *)oneshot_para;
    sigevt.sigev_notify = SIGEV_THREAD;
    sigevt.sigev_notify_function = timer_handler;

    // Initialzie the timer
    timer_t timer;
    memset(&timer, 0, sizeof(timer_t));

    ret = timer_create(CLOCK_REALTIME, &sigevt, &timer);
    if(ret < 0) {
        printf("timer create fail, error code: %d\n", errno);
    }

    struct itimerspec ts;
    ts.it_value.tv_sec = 3;
    ts.it_value.tv_nsec = 0;
    ts.it_interval.tv_sec = 1;
    ts.it_interval.tv_nsec = 0;

    ret = timer_settime(timer, 0, &ts, NULL);
    if(ret < 0) {
        printf("timer setting fail, error code: %d\n", errno);
    }
    else {
        print_current_system_time();
        printf("\033[0;32m"); // green color
        printf("Timer alarm Successfully\n");
        printf("\033[0;37m"); // white color
    }
}

int main() {
    printf("Start\n");
    init_my_timer();

    pause();
    return 0;
}

#else

#include <stdio.h>
int main() {
    printf("Error, cannot find the linux system.\n");
}


#endif
