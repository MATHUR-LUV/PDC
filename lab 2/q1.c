#include <stdio.h>
#include <omp.h>
#define SIZE 1000000
int main()
{
    int arr[SIZE];
    long long sum = 0;
    for (int i = 0; i < SIZE; i++)
        arr[i] = i + 1;

    double start_time = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < SIZE; i++)
    {
        sum += arr[i];
    }
    double end_time = omp_get_wtime();
    printf("Sum: %lld\n", sum);
    printf("Time taken: %f seconds\n", end_time - start_time);
    return 0;
}