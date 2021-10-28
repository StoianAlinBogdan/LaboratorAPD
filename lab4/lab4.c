#include <mpi.h>
#include <stdio.h>
#include <math.h>

int isPowerOfTwo(int x)
{
    return (x & (x-1)) == 0;
}


int main(int argc, char* argv[])
{
    // trebuie verificat daca se poate construi un cub valid, extragem logaritmul dinamic
    // daca lucrez pe 16 procese, aflam dimensiune 4 pentru rularea curenta, daca 13 -> eroare
    MPI_Init(&argc, &argv);

    int nr_procese;
    MPI_Comm_size(MPI_COMM_WORLD, &nr_procese);
    //printf("%d", nr_procese);
    if(isPowerOfTwo(nr_procese))
    {
        int d = log2(nr_procese); //rasfatat :)
        const char *mesaj = "Hello World!";
        char mesajPrimit[32];
        int s = 0;
        int id, idVirtual, sursaVirtuala, destinatieVirtuala, mask;
        MPI_Comm_rank(MPI_COMM_WORLD, &id);
        MPI_Status status;

        idVirtual = (id ^ s);
        mask = (1<<d) - 1;
        for(int k = d - 1; k >= 0; --k)
        {
            int nr = (1<<k);
            mask = mask ^ nr;
            if((idVirtual & mask) == 0)
            {
                if((idVirtual & nr) == 0)
                {
                    destinatieVirtuala = idVirtual ^ nr;
                    printf("%d - Am trimis mesajul catre: %d \n", id, destinatieVirtuala);
                    MPI_Send(mesaj, 32, MPI_CHAR, destinatieVirtuala ^ s, 99, MPI_COMM_WORLD);
                }
                else 
                {
                    sursaVirtuala = (idVirtual ^ nr);
                    printf("%d - Am primit mesajul de la: %d \n", id, sursaVirtuala);
                    MPI_Recv(mesajPrimit, 32, MPI_CHAR, sursaVirtuala ^ s, 99, MPI_COMM_WORLD, &status);
                }
            }
        }
    }
    else {
        printf("Nu e ok");
    }

    MPI_Finalize();
    return 0;
}