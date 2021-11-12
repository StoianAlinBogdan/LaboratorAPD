#include <stdio.h>
#include <mpi.h>


int main(int argc, char* argv[])
{
    int rank, size, data;
    int A[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    int B[16] = {0};

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);



    MPI_Finalize();
    return 0;
}