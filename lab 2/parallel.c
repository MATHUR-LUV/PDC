#include <stdio.h>
#include <omp.h>

int main() {
   
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("First parallel region: Thread %d\n", thread_id);
    }


    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Second parallel region: Thread %d\n", thread_id);
    }

    return 0;
}
