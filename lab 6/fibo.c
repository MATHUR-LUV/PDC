#include <stdio.h>
#include <omp.h>
#define MAX_N 50         // Maximum Fibonacci value to compute
int value[MAX_N] = {0};  // Store computed Fibonacci values
int done[MAX_N] = {0};   // Track if Fibonacci value is computed
omp_lock_t locks[MAX_N]; // Locks for synchronization
// Parallel Fibonacci function using OpenMP tasks
int fib(int n)
{
    if (n < 2)
        return 1; // Base case
    // Lock to prevent race conditions on shared array
    omp_set_lock(&locks[n]);
    if (!done[n])
    {
        int i, j;
#pragma omp task shared(i) firstprivate(n)
        i = fib(n - 1); // Compute fib(n-1) in parallel
#pragma omp task shared(j) firstprivate(n)
        j = fib(n - 2); // Compute fib(n-2) in parallel
#pragma omp taskwait    // Ensure both tasks finish before summing
        value[n] = i + j;
        done[n] = 1; // Mark as computed
    }
    omp_unset_lock(&locks[n]); // Unlock after updating value
    return value[n];
}
int main()
{
    int n = 20; // Change n for larger Fibonacci numbers
    // Initialize locks
    for (int i = 0; i < MAX_N; i++)
    {
        omp_init_lock(&locks[i]);
    }
    int result;
#pragma omp parallel
    {
#pragma omp single // Ensure only one thread starts the computation
        result = fib(n);
    }
    printf("Fibonacci(%d) = %d\n", n, result);
    // Destroy locks
    for (int i = 0; i < MAX_N; i++)
    {
        omp_destroy_lock(&locks[i]);
    }
    return 0;
}