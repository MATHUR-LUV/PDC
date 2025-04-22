// #include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define NUMBER_OF_TESTS 10 // For more reliable average results

int main(int argc, char *argv[])
{
    double *buf;
    int rank, numprocs;
    int n;
    double t1, t2;
    int j, k, nloop;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (numprocs != 2)
    {
        printf("The number of processes must be two!\n");
        MPI_Finalize();
        return 0;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("\tn\tTime [sec]\tRate [Mb/sec]\n");
    }

    for (n = 1; n < 100000000; n *= 2)
    { // Message length doubles
        nloop = 1000000 / n;
        if (nloop < 1)
            nloop = 1; // Just a single loop for long messages

        buf = (double *)malloc(n * sizeof(double));
        if (!buf)
        {
            printf("Could not allocate message buffer of size %d\n", n);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for (k = 0; k < NUMBER_OF_TESTS; k++)
        {
            if (rank == 0)
            {
                t1 = MPI_Wtime();
                for (j = 0; j < nloop; j++)
                {
                    MPI_Send(buf, n, MPI_DOUBLE, 1, k, MPI_COMM_WORLD);
                }
                t2 = (MPI_Wtime() - t1) / nloop;
            }
            else if (rank == 1)
            {
                for (j = 0; j < nloop; j++)
                {
                    MPI_Recv(buf, n, MPI_DOUBLE, 0, k, MPI_COMM_WORLD, &status);
                }
            }
        }

        if (rank == 0)
        {
            double bandwidth;
            bandwidth = n * sizeof(double) * 1.0e-6 * 8 / t2; // in Mb/sec
            printf("\t%10d\t%10.8f\t%8.2f\n", n, t2, bandwidth);
        }

        free(buf);
    }

    MPI_Finalize();
    return 0;
}
