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
    
    
    for (int k = m - 1; k >= 0; --k) {
            for (int j = 1 << k; j < (1 << (k + 1)); ++j) {
                if (rank == j) {
                    MPI_Recv(&firstValue, 1, MPI_INT, 2 * j, 8, MPI_COMM_WORLD, &status);
                    std::cout << "<RECV> " << rank << " <----- " << 2 * j << ": " << A[2 * rank] << std::endl;
                    MPI_Recv(&secondValue, 1, MPI_INT, 2 * j + 1, 8, MPI_COMM_WORLD, &status);
                    std::cout << "<RECV> " << rank << " <----- " << 2 * j + 1 << ": " << A[2 * rank + 1] << std::endl;
                    data = firstValue > secondValue ? firstValue : secondValue;
                    if (rank != 1) {
                        MPI_Send(&data, 1, MPI_INT, rank / 2, 8, MPI_COMM_WORLD);
                        std::cout << "<SEND> " << rank << " -----> " << rank / 2 << ": " << A[rank] << std::endl;
			}
		}
	}


    MPI_Finalize();
    return 0;
}
