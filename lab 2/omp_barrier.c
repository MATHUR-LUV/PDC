#include<omp.h>
#include<stdio.h>

int main(){
	#pragma omp parallel
	{
		// int num_threads =  omp_get_num_threads();
		// printf("Num threads : %d \n", num_threads);
		printf("Before barrier : Thread %d \n", omp_get_thread_num());
		#pragma omp barrier
		printf("After barrier : Thread %d \n", omp_get_thread_num());
	}
	
	return 0;
}