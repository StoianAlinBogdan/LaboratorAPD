#include <mpi.h>
#include <stdio.h>

//MPI_Cart_shift(MPI_Comm, d, deplasare, &src, &dest)
// pentru a afla vecinii: MPI_Cart_shift(cart, 1, 1, &stanga, &dreapta) 
// la fel si pentru veecinul de sus si de jos :MPI_Cart_shift(cart, 0, 1, &sus, &jos)
// 16 procese, cate 4 pe dimensiunea, periodicitate pe ambele: periods[2] = {1, 1}
// executare neaparat cu 16 procese




int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int count, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &count);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int A[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {0, 0, 1, 2},
        {1, 2, 0, 0}
    };
    int B[4][4] = {
        {1, 2, 0, 0},
        {0, 1, 0 ,0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    int periods[2] = {1, 1};
    int dims[2] = {4, 4};
    MPI_Comm cart;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart);
    
    int myCoords[2];
    MPI_Cart_coords(cart, rank, 2, myCoords);
    int vstg, vdrt, vsus, vjos;
    MPI_Cart_shift(cart, 1, 1, &vstg, &vdrt);
    MPI_Cart_shift(cart, 0, 1, &vsus, &vjos);
    //printf("Rank curent: %d, rank vecin sus: %d, rank vecin jos: %d, rank stanga: %d, rank dreapta: %d\n", rank, vsus, vjos, vstg, vdrt);
    //Aliniere initiala
    if(myCoords[0] != 0) // la stanga
    {
        for(int i = 1; i < myCoords[1]; i++)
        {
            MPI_Send(A[myCoords[0]][myCoords[1]], 1, MPI_INT, vstg, 99, cart);
            MPI_Status status;
            MPI_Recv(A[myCoords[0]][myCoords[1]], 1, MPI_INT, vdrt, 99, cart, &status);
        }
    }
    if(myCoords[1] != 0) // in sus
    {
        for(int i = 1; i < myCoords[0]; i++)
        {
            MPI_Send(B[myCoords[0]][myCoords[1]], 1, MPI_INT, vsus, 99, cart);
            MPI_Status status;
            MPI_Recv(B[myCoords[0]][myCoords[1]], 1, MPI_INT, vjos, 99, cart, &status);
        }
    }

    MPI_Comm_free(&cart);
    MPI_Finalize();
    return 0;

}