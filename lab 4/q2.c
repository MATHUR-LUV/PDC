#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 1000


double dot_product_single_threaded(int *a, int *b, int n){
	double result = 0.0;
	for(int i=0;i<n;i++){
		result += a[i]*b[i];
	}
	
	return result;
}

int main(){
	int a[N], b[N];
	srand(time(0));
	
	for(int i=0;i<N;i++){
		a[i] = rand()% 100 + 1;
		b[i] = rand()% 100 + 1;

	}
	
	double start_time = omp_get_wtime();
	
	double dot_product_parallel = 0.0;
	#pragma omp parallel reduction (+:dot_product_parallel)
	{
		int id = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		
		int chunk_size = N/num_threads;
		int start = id * chunk_size;
		int end = ( id == num_threads - 1 ) ? N : (id + 1 ) * chunk_size;
		printf("id : %d \n", id);
		printf("num threads : %d \n", num_threads);
		printf("chunk_size %d\n", chunk_size);
		printf("start : %d \n", start);
		printf("end : %d \n", end);
		printf("\n");
		#pragma omp parallel for reduction (+:dot_product_parallel)
		for (int i=start;i<end;i++){
			dot_product_parallel += a[i] * b[i];
		}
	}
	double end_time = omp_get_wtime();
	printf("Time taken : %f seconds \n", end_time - start_time);
	double dot_product_serial = dot_product_single_threaded(a, b, N);
	
	printf("Dot Product (parallel): %f \n", dot_product_parallel);
	printf("Dot Product (serial): %f \n", dot_product_serial);
	
	if(dot_product_parallel == dot_product_serial){
		printf("result match !\n");
	}else{
		printf("Results does not match. \n");
	}
	
	return 0;
}