#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/kernel.h>

#define SYS_memcpy_2d 451
#define _GNU_SOURCE

int main()
{
    double matrix1[3][3] = {{11, 12, 13}, {21, 22, 23}, {31, 32, 33}};
    double matrix2[3][3];

    long int x = syscall(SYS_memcpy_2d, matrix1, matrix2);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%lf ", matrix2[i][j]);
        }
        printf("\n");
    }
    return 0;
}
