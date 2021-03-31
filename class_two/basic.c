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

    MPI_Finalize();

    return 0;
}
