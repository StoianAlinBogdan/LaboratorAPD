#include <omp.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    omp_set_num_threads(16);
    int A[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    int k, j;

    for(k = 2; k != 0; --k)
    {
        #pragma omp parallel for shared(A)
        for(j = (1<<k); j < (1<< (k+1)); ++j)
        {
            A[j] = A[2 * j] + A[2*j + 1];
        }
    }

    A[1] = A[2] + A[3]; //nu inteleg de ce nu face algoritmul asta

    for(int i = 0; i < 16; i++)
    {
        printf("%d ", A[i]);
    }

    int B[16] = {0};
    B[1] = A[1];
    for(k = 1; k <= 2; k++)
    {
        #pragma parralel for shared(A, B)
        for(j = 1 << k; j < (1 << (k+1)); j++ )
        {
            if((j & 1) == 1)
            {
                B[j] = B[(j-1) / 2];
            }
            else
            {
                B[j] = B[j/2] + (-A[j+1]);
            }
        }
    }
    printf("\n");
    for(int i = 0; i < 16; i++)
    {
        printf("%d ", B[i]);
    }


    return 0;
}
//pentru mpi: for-urile nu trebuie sa fie for-uri explicite;
// if(rank == root) compun else if(rank == frunza) send else receive (toate blocante)