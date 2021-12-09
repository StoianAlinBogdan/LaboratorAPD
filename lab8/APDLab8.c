#include <stdio.h>
#include <mpi.h>

#define N 16

int ispower2(int arg)
{
    return (arg & (arg - 1)) == 0;
}

int mylog2(int arg)
{
    return (arg > 1) ? 1 + mylog2(arg / 2) : 0;
}



int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int A[N] = {10, 20, 5, 9, 3, 8, 12, 14, 90, 0, 60, 40, 23, 35, 95, 18};

    MPI_Status status;

    if(ispower2(size) && size == N)
    {
        int dims = mylog2(size);
        for(int faza = 1; faza < dims; faza++)
        {
            for(int com = faza - 1; com >= 0; com--)
            {
                int dest = rank ^ (1 << com);
                int reg;
                MPI_Send(&A[rank], 1, MPI_INT, dest, 99, MPI_COMM_WORLD);
                MPI_Recv(&reg, 1, MPI_INT, dest, 99, MPI_COMM_WORLD, &status);
                int rank_com = (rank >> com) % 2;
                int rank_faza = (rank >> faza) % 2;
                if(rank_com == rank_faza)
                {
                    if(A[rank] > reg)
                    {
                        A[rank] = reg;
                    }
                }
                else
                {
                    if(A[rank] < reg)
                    {
                        A[rank] = reg;
                    }
                }
            }
        }

        //Mai trebuie o etapa de procesare, ultima sortare

        if(rank == 0)
        {
            for(int i = 0; i < 16; i++)
            {
                printf("A[%d] = %d", i, A[i]);
            }
        }
    }
    else
    {
        printf("Trebuie o putere de 2 de procese!\n");
    }



    MPI_Finalize();
    return 0;

}