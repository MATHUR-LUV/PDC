#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 5


omp_lock_t mylock;
int shared_variable = 0;

void function(int thread_id){
    printf("%d", thread_id);
    shared_variable += thread_id;
}
int main(){
    omp_init_lock(&mylock);

    #pragma omp parallel num_threads(NUM_THREADS)   
    {
        int mytid = omp_get_thread_num();

        omp_set_lock(&mylock);
        function(mytid);
        printf("%d, %d", mytid, shared_variable);
        omp_unset_lock(&mylock);
    }

    omp_destroy_lock(&mylock);
    printf("%d", shared_variable);

    return 0;
}