#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>

// #define SCHED_OTHER 0
// #define SCHED_FIFO 1
// #define SCHED_RR 2

int main()
{
    double time1, time2, time3;
    pid_t t1, t2, t3;

    struct timespec start1, end1;
    clock_gettime(CLOCK_MONOTONIC, &start1);
    t1 = fork();
    if (t1 == 0)
    {
        struct sched_param x;
        x.sched_priority = 0;
        sched_setscheduler(t1, SCHED_OTHER, &x);

        execvp("./BashScript_1.sh", NULL);
    }

    t2 = fork();
    struct timespec start2, end2;
    clock_gettime(CLOCK_MONOTONIC, &start2);
    if (t2 == 0)
    {
        struct sched_param y;
        y.sched_priority = 0;
        sched_setscheduler(t2, SCHED_RR, &y);

        execvp("./BashScript_2.sh", NULL);
    }

    t3 = fork();
    struct timespec start3, end3;
    clock_gettime(CLOCK_MONOTONIC, &start3);
    if (t3 == 0)
    {
        struct sched_param z;
        z.sched_priority = 0;
        sched_setscheduler(t3, SCHED_FIFO, &z);

        execvp("./BashScript_3.sh", NULL);
    }

    pid_t res1, res2, res3;
    res1 = waitpid(-1, NULL, 0);
    res2 = waitpid(-1, NULL, 0);
    res3 = waitpid(-1, NULL, 0);

    if (res1 == t1)
    {
        clock_gettime(CLOCK_MONOTONIC, &end1);
        time1 = (end1.tv_sec - start1.tv_sec) + (double)(end1.tv_nsec - start1.tv_nsec) / (double)1000000000;
    }
    else if (res1 == t2)
    {
        clock_gettime(CLOCK_MONOTONIC, &end2);
        time2 = (end2.tv_sec - start2.tv_sec) + (double)(end2.tv_nsec - start2.tv_nsec) / (double)1000000000;
    }
    else if (res1 == t3)
    {
        clock_gettime(CLOCK_MONOTONIC, &end3);
        time3 = (end3.tv_sec - start3.tv_sec) + (double)(end3.tv_nsec - start3.tv_nsec) / (double)1000000000;
    }

    if (res2 == t1)
    {
        clock_gettime(CLOCK_MONOTONIC, &end1);
        time1 = (end1.tv_sec - start1.tv_sec) + (double)(end1.tv_nsec - start1.tv_nsec) / (double)1000000000;
    }
    else if (res2 == t2)
    {
        clock_gettime(CLOCK_MONOTONIC, &end2);
        time2 = (end2.tv_sec - start2.tv_sec) + (double)(end2.tv_nsec - start2.tv_nsec) / (double)1000000000;
    }
    else if (res2 == t3)
    {
        clock_gettime(CLOCK_MONOTONIC, &end3);
        time3 = (end3.tv_sec - start3.tv_sec) + (double)(end3.tv_nsec - start3.tv_nsec) / (double)1000000000;
    }

    if (res3 == t1)
    {
        clock_gettime(CLOCK_MONOTONIC, &end1);
        time1 = (end1.tv_sec - start1.tv_sec) + (double)(end1.tv_nsec - start1.tv_nsec) / (double)1000000000;
    }
    else if (res3 == t2)
    {
        clock_gettime(CLOCK_MONOTONIC, &end2);
        time2 = (end2.tv_sec - start2.tv_sec) + (double)(end2.tv_nsec - start2.tv_nsec) / (double)1000000000;
    }
    else if (res3 == t3)
    {
        clock_gettime(CLOCK_MONOTONIC, &end3);
        time3 = (end3.tv_sec - start3.tv_sec) + (double)(end3.tv_nsec - start3.tv_nsec) / (double)1000000000;
    }

    printf("%lf\n", time1);
    printf("%lf\n", time2);
    printf("%lf\n", time3);
}