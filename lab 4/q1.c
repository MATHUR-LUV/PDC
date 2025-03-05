#include <stdio.h>
#include <omp.h>

void subprogram() {

    printf("Subprogram: Outside parallel region (Thread %d)\n", omp_get_thread_num());


    #pragma omp parallel
    {
        printf("Subprogram: Inside parallel region (Thread %d)\n", omp_get_thread_num());
    }
}

int main() {
    omp_set_max_active_levels(2);
    printf("max active levels : %d\n", omp_get_max_active_levels());
    
    printf("main: outside parallel region. \n");
    
    #pragma omp parallel
    {
        printf("Main: Inside parallel region (Thread %d)\n", omp_get_thread_num());

        // Call the subprogram inside the parallel region
        subprogram();
    }

    // Call the subprogram outside the parallel region
    subprogram();

    return 0;
}