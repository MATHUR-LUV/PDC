#include<stdio.h>
#include<omp.h>
#define SIZE 100000

int main(){
	int arr[SIZE];
	long long sum = 0;
	for(int i=0;i<SIZE;i++) arr[i] = i+1;
	int num_threads = omp_get_num_threads();
	printf("total threads : %d \n", num_threads);
	double start_time = omp_get_wtime();
	
	#pragma omp parallel for reduction(+:sum)
	for(int i=0;i<SIZE;i++){
		sum += arr[i];
	}
	
	double end_time = omp_get_wtime();
	
	printf("Sum : %lld \n", sum);
	printf("Time taken : %f seconds \n", end_time - start_time);
	return 0;
}