#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000  // Maximum message size

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        if (rank == 0) {
            printf("This program requires exactly 3 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int next = (rank + 1) % size;
    int prev = (rank + size - 1) % size;
    int message_size = 1;

    while (message_size <= MAX_SIZE) {
        char *buffer = (char *)malloc(message_size * sizeof(char));
        if (buffer == NULL) {
            printf("Memory allocation failed at rank %d\n", rank);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        if (rank == 0) {
            // Process 0 initiates the message passing
            MPI_Send(buffer, message_size, MPI_CHAR, next, 0, MPI_COMM_WORLD);
            MPI_Recv(buffer, message_size, MPI_CHAR, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Iteration with message size %d completed at rank 0\n", message_size);
        } else {
            // Intermediate processes
            MPI_Recv(buffer, message_size, MPI_CHAR, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(buffer, message_size, MPI_CHAR, next, 0, MPI_COMM_WORLD);
        }

        free(buffer);
        message_size *= 2;  // Double the message size
    }

    MPI_Finalize();
    return 0;
}