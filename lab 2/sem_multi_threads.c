#include <stdio.h>
#include <omp.h>
#define SIZE 100000

int main() {
    int arr[SIZE];
    long long sum = 0;


    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }


    for (int num_threads = 2; num_threads <= 8; num_threads += 2) {
        sum = 0; 
        omp_set_num_threads(num_threads); 
        
        double start_time = omp_get_wtime();

 
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < SIZE; i++) {
            sum += arr[i];
        }

        double end_time = omp_get_wtime(); 


        printf("Number of threads: %d\n", num_threads);
        printf("Sum: %lld\n", sum);
        printf("Time taken: %f seconds\n\n", end_time - start_time);
    }

    return 0;
}