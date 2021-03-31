// Import MPI
#include "mpi.h"

// Basic C stuff
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv[]){
    
    int numtasks, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Get_processor_name(hostname, &len);

    printf("[Rank %d] Hello from %s! You have %d clusters\n", rank, hostname, numtasks);

    if(rank == 0){
        int send_value = 10;

        MPI_Send(&send_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Status status;
        int recv_value = 0;

        MPI_Recv(&recv_value, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);

        printf("[Rank %d] Mandei %d e recebi com sucesso o valor %d \n", rank, send_value, recv_value);
    }else{
        MPI_Status status;
        int value;

        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        value++;

        MPI_Send(&value, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
