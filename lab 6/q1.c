#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define INF 99999999 

void floydWarshall(int **dist, int V) {
   
    #pragma omp parallel
    {
        for (int k = 0; k < V; k++) {
           
            #pragma omp for
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    
                    #pragma omp task
                    dist[i][j] = (dist[i][j] < dist[i][k] + dist[k][j]) ? dist[i][j] : dist[i][k] + dist[k][j];
                }
            }

           
            #pragma omp taskwait
        }
    }
}
int main(){
    int V ;
    printf("enter no. of vertices : ");
    scanf("%d\n", &V);
     int **dist = (int **)malloc(V * sizeof(int *));
    
    for (int i = 0; i < V; i++) {
        dist[i] = (int *)malloc(V * sizeof(int));
    }
    
    for(int i=0; i<V;i++){
    	for(int j=0;j<V;j++){
    		int temp ;
    		scanf("%d", &temp);
    		dist[i][j] = temp;
    	}
    }
     printf("Initial distance matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

  
    floydWarshall(dist, V);

    printf("\nFinal distance matrix after Floyd-Warshall:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

 
    for (int i = 0; i < V; i++) {
        free(dist[i]);
    }
    free(dist);
    
    return 0;
}

// gcc -fopenmp q1.c