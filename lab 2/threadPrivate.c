#include <stdio.h>
#include <omp.h>

int my_var = 0; 

#pragma omp threadprivate(my_var) 

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();


        my_var = thread_id;


        printf("Thread %d has my_var = %d\n", thread_id, my_var);
    }
    return 0;
}
