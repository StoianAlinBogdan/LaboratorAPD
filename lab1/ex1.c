#include <stdio.h>
#include <omp.h>

int main()
{
    int tid;

#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("%d in regiunea 1 - cazul default\n", tid);
    }
    printf("\n\n");
    omp_set_num_threads(3);
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("%d in regiunea 2 - omp_set_num_threads(3)\n", tid);
    }
    printf("\n\n");

#pragma omp parallel private(tid) num_threads(8)
    {
        tid = omp_get_thread_num();
        printf("%d in regiunea 3 - clauza num_threads(8)\n", tid);
    }
    printf("\n\n");
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("%d in regiunea 4 - omp set_num_threads(3)\n", tid);
    }
    return 0;
}