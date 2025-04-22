#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUMBER_OF_TESTS 1000

void run_latency_test(int rank, int size, int message_size) {
    double *message = (double *)malloc(sizeof(double) * message_size);
    MPI_Status status;
    double start_time, end_time, total_time = 0.0;

    for (int test = 0; test < NUMBER_OF_TESTS; test++) {
        if (rank == 0) {
 
            start_time = MPI_Wtime();
            MPI_Send(message, message_size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(message, message_size, MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD, &status);
            end_time = MPI_Wtime();
            total_time += (end_time - start_time);
        } else {
      
            MPI_Recv(message, message_size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &status);
            MPI_Send(message, message_size, MPI_DOUBLE, (rank + 1) % size, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        double avg_latency_ms = (total_time / NUMBER_OF_TESTS) * 1000.0;
        printf("%-20d %.6f\n", message_size, avg_latency_ms);
    }

    free(message);
}

int main(int argc, char **argv) {
    int rank, size;
    int message_sizes[] = {1, 10, 100, 1000};
    int num_sizes = sizeof(message_sizes) / sizeof(message_sizes[0]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Message Size (doubles) Avg. Latency per round-trip [ms]\n");
    }

    for (int i = 0; i < num_sizes; i++) {
        MPI_Barrier(MPI_COMM_WORLD);     
        run_latency_test(rank, size, message_sizes[i]);
    }

    MPI_Finalize();
    return 0;
}
