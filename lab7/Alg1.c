/* muller-preparata
#pragma omp parallel for
for(i...)
    for(j...)

*/
#define N 4

#include <omp.h>
#include <stdio.h>

void transpose(int A[][N], int B[][2*N])
{
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < 2*N; j++)
            B[i][j] = A[j][i];
}

void comprimare(int A[])
{
    int k, j;
    for(k = 1; k != 0; k--)
    {
        //#pragma omp parallel for shared(A)
        for(j = (1 << k); j < (1<<(k+1)-1); j++)
        {
            A[j] = A[2 * j] + A[2*j + 1];
        }
    }
}

int main(int argc, char* argv[])
{
    //omp_set_num_threads(4);
    int A[N] = {2, 6, 3, 8};
    int P[N] = {0};
    int R[2*N][N] = {0};
    int i, j;
    int tid;

    for(i = 0; i < N; i++)
    {
        #pragma omp parallel for default(none) private (tid) shared(A, R, i, j)
        for(j = 0; j < N; j++)
        {
            if(A[i] < A[j])
                R[i+N][j] = 1;
            else
                R[i+N][j] = 0;
        }
    }

    int M[N][2*N] = {0};
    //transpose(R, M); credeam ca-s destept dar nu-s


    #pragma omp parallel for default(none) private(tid) shared(M, P, j)
    for(j = N; j < 2*N; j++)
    {  
        printf("\n");
        comprimare(M[j]);
        P[j] = M[0][j];
    } 

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < 2*N; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }

    printf("\n");
    
    
    for(i = 0; i < 2*N; i++)
    {
        for(j = 0; j < N; j++)
            printf("%d ", R[i][j]);
        printf("\n");
    }

    printf("\n");

    for(i = 0; i < N; i++)
        printf("%d ", P[i]);
    
    return 0;
}