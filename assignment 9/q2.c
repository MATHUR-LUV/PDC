#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int numprocs, rank, tag = 100, msg_size = 64;
    char *buf;
    MPI_Status status;

    MPI_Init(&argc, &argv); // Initialize MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); // Get number of processes

    if (numprocs != 2)
    {
        printf("The number of processes must be two!\n");
        MPI_Finalize();
        return 0;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process rank
    printf("MPI process %d started...\n", rank);
    fflush(stdout);

    while (msg_size < 10000000)
    {
        msg_size = msg_size * 2; // Double message size each iteration
        buf = (char *)malloc(msg_size * sizeof(char)); // Allocate message buffer

        if (rank == 0)
        {
            MPI_Send(buf, msg_size, MPI_BYTE, rank + 1, tag, MPI_COMM_WORLD);
            printf("Sent message of length %d to process %d\n", msg_size, rank + 1);
            fflush(stdout);

            MPI_Recv(buf, msg_size, MPI_BYTE, rank + 1, tag, MPI_COMM_WORLD, &status);
        }

        if (rank == 1)
        {
            MPI_Recv(buf, msg_size, MPI_BYTE, rank - 1, tag, MPI_COMM_WORLD, &status);
            MPI_Send(buf, msg_size, MPI_BYTE, rank - 1, tag, MPI_COMM_WORLD);
            printf("Sent message of length %d to process %d\n", msg_size, rank - 1);
            fflush(stdout);
        }

        free(buf); // Deallocate buffer memory
    }

    MPI_Finalize(); // Finalize MPI environment
    return 0;
}
