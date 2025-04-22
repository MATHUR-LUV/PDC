#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int n;
    int *data = NULL;     
    int *recvbuf;
    int *gathered = NULL;   

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        if (rank == 0)
            fprintf(stderr, "This program must be run with exactly 4 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        n = 2;
        data = (int*)malloc(sizeof(int) * size * n);
        for (int i = 0; i < size * n; i++)
            data[i] = i;

        printf("Process 0 initialized array:\n");
        for (int i = 0; i < size * n; i++)
            printf("%d ", data[i]);
        printf("\n");
    }


    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    recvbuf = (int*)malloc(sizeof(int) * n);


    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatter(data, n, MPI_INT, recvbuf, n, MPI_INT, 0, MPI_COMM_WORLD);


    printf("Process %d received:", rank);
    for (int i = 0; i < n; i++) {
        printf(" %d", recvbuf[i]);
        recvbuf[i] *= 2;  
    }
    printf("\n");


    if (rank == 0)
        gathered = (int*)malloc(sizeof(int) * size * n);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(recvbuf, n, MPI_INT, gathered, n, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Final gathered array in process 0:\n");
        for (int i = 0; i < size * n; i++)
            printf("%d ", gathered[i]);
        printf("\n");
    }

    free(recvbuf);
    if (data) free(data);
    if (gathered) free(gathered);

    MPI_Finalize();
    return 0;
}
