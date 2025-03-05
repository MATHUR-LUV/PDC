#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define SIZE 1000


int privateVar;
#pragma omp threadprivate(privateVar)

int main() {
    int mat[SIZE][SIZE];        
    int vec[SIZE];           
    long long result[SIZE];     
    long long sum = 0;         
    long long max = LLONG_MIN;  

   
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        vec[i] = rand() % 100;  
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = rand() % 100; 
        }
    }

    double start_time_exec = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Starting execution...\n");
        }
    }
    double end_time_exec = omp_get_wtime();
    double start_time_parallel_sum = omp_get_wtime();
    
    #pragma omp parallel for
    for(int i=0;i<SIZE;i++){
    	result[i] = 0;
    	#pragma omp parallel reduction(+: result[i])
    	{
    		for(int j=0;j<SIZE;j++){
    			result[i] += mat[i][j] * vec[j];
    		}
    	}
    }
    
    double end_time_parallel_sum = omp_get_wtime();

    double start_time_section = omp_get_wtime();
    #pragma omp parallel sections reduction(+:sum) reduction(max: max)
    {
  
        #pragma omp section
        {
            long long localSum = 0;
            for (int i = 0; i < SIZE; i++) {
                localSum += result[i];
            }
            sum += localSum;
            
            printf("Section 1 is computed by thread %d \n", omp_get_thread_num());
        }

        #pragma omp section
        {
            long long localMax = result[0];
            for (int i = 1; i < SIZE; i++) {
                if (result[i] > localMax) {
                    localMax = result[i];
                }
            }
            if (localMax > max) {
                max = localMax;
            }
            
            printf("Section 2 is computed by thread %d \n", omp_get_thread_num());
        }
    }
    double end_time_section = omp_get_wtime();
    printf("Sum of result[]: %lld\n", sum);
    printf("Maximum value in result[]: %lld\n", max);
    
    printf("time for starting computation : %f\n", end_time_exec - start_time_exec);
    printf("time for section for sum ( result[] ) computation : %f\n", end_time_parallel_sum - start_time_parallel_sum);
    printf("time for sections computation : %f\n", end_time_section - start_time_section);

    return 0;
}