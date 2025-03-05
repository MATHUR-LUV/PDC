#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000

int main() {
    srand(time(NULL));

    int *array = (int*)malloc(N * sizeof(int));
    int max_value = 0;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        array[thread_id] = (rand() % 100) + 1;

        #pragma omp barrier

        if (thread_id == 0) {
            max_value = array[0];
            for (int i = 1; i < N; i++) {
                if (array[i] > max_value) {
                    max_value = array[i];
                }
            }
        }
    }

    printf("Generated random numbers:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("Maximum value: %d\n", max_value);

    free(array);
    return 0;
}
