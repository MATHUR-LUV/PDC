#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int done = 0, n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double pi, h, sum, x, start, finish;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    while (!done) {
        if (myid == 0) {
            printf("Enter the number of intervals: (0 quits) ");
            fflush(stdout);
            scanf("%d", &n);  // Changed from scanf_s for portability
            start = MPI_Wtime();
        }

        // Broadcast 'n' to all processes
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (n == 0) {
            done = 1;
        } else {
            h = 1.0 / (double)n;
            sum = 0.0;

            for (i = myid + 1; i <= n; i += numprocs) {
                x = h * ((double)i - 0.5);
                sum += 4.0 * h * sqrt(1.0 - x * x);
            }

            // Reduce all local sums to a global sum on process 0
            MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (myid == 0) {
                finish = MPI_Wtime();
                printf("Pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
                printf("Elapsed time is %f seconds\n", finish - start);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
