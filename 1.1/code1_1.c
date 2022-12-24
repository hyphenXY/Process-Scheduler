#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define n pow(2, 32)
#define loop(n) for (long long int i = 1; i <= n; i++)

void *countA(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        struct sched_param x;
        x.sched_priority = i;
        pthread_setschedparam(pthread_self(), SCHED_OTHER, &x);
        long long int a = n;
        loop(a);

        clock_gettime(CLOCK_MONOTONIC, &end);

        double total_time;
        total_time = (end.tv_sec - start.tv_sec) * 1e9;
        total_time = (total_time + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        printf("A %d = %lf\n", i, total_time);
        fprintf((FILE *)arg, "%d %lf\n", i, total_time);
    }
}

void *countB(void *arg)
{
    for (int i = 1; i < 11; i++)
    {
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        struct sched_param x;
        x.sched_priority = i;
        pthread_setschedparam(pthread_self(), SCHED_RR, &x);
        long long int a = n;
        loop(a);

        clock_gettime(CLOCK_MONOTONIC, &end);

        double total_time;
        total_time = (end.tv_sec - start.tv_sec) * 1e9;
        total_time = (total_time + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        printf("B %d = %lf\n", i, total_time);
        fprintf((FILE *)arg, "%d %lf\n", i, total_time);
    }
}

void *countC(void *arg)
{
    for (int i = 1; i < 11; i++)
    {
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        struct sched_param x;
        x.sched_priority = i;
        pthread_setschedparam(pthread_self(), SCHED_FIFO, &x);
        long long int a = n;
        loop(a);

        clock_gettime(CLOCK_MONOTONIC, &end);

        double total_time;
        total_time = (end.tv_sec - start.tv_sec) * 1e9;
        total_time = (total_time + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        printf("C %d = %lf\n", i, total_time);
        fprintf((FILE *)arg, "%d %lf\n", i, total_time);
    }
}

int main()
{
    FILE *f1, *f2, *f3;
    f1 = fopen("HistogramA.data", "w");
    fprintf(f1, "#Priorities Time_taken\n");

    f2 = fopen("HistogramB.data", "w");
    fprintf(f2, "#Priorities Time_taken\n");

    f3 = fopen("HistogramC.data", "w");
    fprintf(f3, "#Priorities Time_taken\n");

    pthread_t Thr1, Thr2, Thr3;
    pthread_create(&Thr1, NULL, &countA, (void *)f1);
    pthread_create(&Thr2, NULL, &countB, (void *)f2);
    pthread_create(&Thr3, NULL, &countC, (void *)f3);

    pthread_join(Thr1, NULL);
    pthread_join(Thr2, NULL);
    pthread_join(Thr3, NULL);

    fclose(f1);
    fclose(f2);
    fclose(f3);

    char *args1[] = {"set style data histograms",
                     "set style fill solid",
                     "plot 'HistogramA.data' using 2:xtic(1) linecolor 'black' title 'A'",
                     "exit"};

    FILE *h1 = popen("gnuplot -persistent", "w");
    for (int i = 0; i < 4; i++)
    {
        fprintf(h1, "%s\n", args1[i]);
    }
    pclose(h1);

    char *args2[] = {"set style data histograms",
                     "set style fill solid",
                     "plot 'HistogramB.data' using 2:xtic(1) linecolor 'black' title 'B'",
                     "exit"};

    FILE *h2 = popen("gnuplot -persistent", "w");
    for (int i = 0; i < 4; i++)
    {
        fprintf(h2, "%s\n", args2[i]);
    }
    pclose(h2);

    char *args3[] = {"set style data histograms",
                     "set style fill solid",
                     "plot 'HistogramC.data' using 2:xtic(1) linecolor 'black' title 'C'",
                     "exit"};

    FILE *h3 = popen("gnuplot -persistent", "w");
    for (int i = 0; i < 4; i++)
    {
        fprintf(h3, "%s\n", args3[i]);
    }
    pclose(h3);
}
