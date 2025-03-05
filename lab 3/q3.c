#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int main() {
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread_id = omp_get_thread_num();
        int counter = 0;

        for (int i = 0; i < 10; i++) {
            counter += thread_id;
        }

        printf("Thread %d: counter = %d\n", thread_id, counter);
    }

    return 0;
}
