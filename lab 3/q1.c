#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000

void generate_random_values(int *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = (rand() % 100) + 1;
    }
}

int dot_product_single_threaded(int *v1, int *v2, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

int dot_product_parallel(int *v1, int *v2, int size) {
    int result = 0;
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < size; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

int main() {
    srand(time(NULL));

    int *v1 = (int*)malloc(N * sizeof(int));
    int *v2 = (int*)malloc(N * sizeof(int));

    generate_random_values(v1, N);
    generate_random_values(v2, N);

    double start_time = omp_get_wtime();
    int single_thread_result = dot_product_single_threaded(v1, v2, N);
    double end_time = omp_get_wtime();
    double single_thread_time = end_time - start_time;
    printf("Single-threaded dot product result: %d\n", single_thread_result);
    printf("Single-threaded execution time: %f seconds\n", single_thread_time);

    start_time = omp_get_wtime();
    int parallel_result = dot_product_parallel(v1, v2, N);
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    printf("Parallel dot product result: %d\n", parallel_result);
    printf("Parallel execution time: %f seconds\n", parallel_time);

    free(v1);
    free(v2);

    return 0;
}