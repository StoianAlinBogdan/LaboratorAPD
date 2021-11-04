#include <iostream>
#include <mpi.h>
#include <vector>
#include "lab5.h"


int main(int argc, char* argv[])
{

    std::vector<int> adiacenta[NODES] = {{4}, {6}, {4, 7, 8}, {4, 6},{0, 2, 3}, {6}, {1, 3, 5}, {2}, {2}};
    char mesaj[] = "Hello World!";
    int id, count, nrVecini, root = 4;
    int* index = getIndex(adiacenta), *edges = getEdges(adiacenta), *vecini;
    MPI_Comm graph;

    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &count);
    MPI_Graph_create(MPI_COMM_WORLD, NODES, index, edges, false, &graph);
    MPI_Graph_neighbors_count(graph, id, &nrVecini);

    vecini = new int[nrVecini];

    MPI_Graph_neighbors(graph, id, nrVecini, vecini);
    //Algoritm 1:
    if(id == root)
    {
        for(int i = 0; i < nrVecini; i++)
        {
            MPI_Send(mesaj, strlen(mesaj) + 1, MPI_CHAR, vecini[i], 99, graph);
            std::cout<<"Radacina["<<id<<"] a trimis mesajul "<<mesaj<<" catre "<<vecini[i]<<"\n";
        }
    }
    else
    {
        MPI_Recv(mesaj, strlen(mesaj) + 1, MPI_CHAR, MPI_ANY_SOURCE, 99, graph, &status);
        if(nrVecini > 1)
        {
            for(int i = 0; i < nrVecini; i++)
            {
                if(vecini[i] != status.MPI_SOURCE)
                {
                    MPI_Send(mesaj, strlen(mesaj) + 1, MPI_CHAR, vecini[i], 99, graph);
                    std::cout<<"\nNodul["<<id<<"] a trimis mesajul "<<mesaj<<" catre "<<vecini[i]<<"\n";
                }
            }
        }
    }

    


    MPI_Comm_free(&graph);
    MPI_Finalize();
    return 0;
}