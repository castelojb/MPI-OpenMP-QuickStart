#include "mpi.h"

#include <omp.h>
#include <stdint.h>

#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include "filters.c"

#include <time.h>

#include <math.h>

void root_operations(int rank, int numtasks){
    
    // read image in disk
    printf("[Rank %d] Reading image\n", rank);

    int width, height, channels;

    unsigned char *image = stbi_load("images/16k-image.jpg", &width, &height, &channels, 0);

    printf("[Rank %d] Your image has been read and have %d pixels\n", rank, width*height);

    // make image fragmentation
    int numworkers = numtasks - 1;
    int lines_per_worker = round(width/numworkers);

    // calc of elements per worker
    int step_pixels = height*channels*lines_per_worker;

    // send data
    printf("[Rank %d] Sending data for workers\n", rank);

    
    for(int worker = 1; worker <= numworkers; worker++){
        

        // send dims of image
        MPI_Send(&lines_per_worker, 1, MPI_INT, worker, 0, MPI_COMM_WORLD);
        MPI_Send(&height, 1, MPI_INT, worker, 1, MPI_COMM_WORLD);
        MPI_Send(&channels, 1, MPI_INT, worker, 2, MPI_COMM_WORLD);
        MPI_Send(&step_pixels, 1, MPI_INT, worker, 3, MPI_COMM_WORLD);


        // copy the values of real image to new array to send
        unsigned char *frag_image = malloc(step_pixels * sizeof(unsigned char));
        int i = 0;
        for(int idx = (worker -1)*step_pixels; idx < worker * step_pixels; idx++ ){
            
            frag_image[i] = image[idx];
            i++;

        }

        // send frag image
        MPI_Send(frag_image, step_pixels, MPI_UNSIGNED_CHAR, worker, 4, MPI_COMM_WORLD);

    }   

    // prepare memory to receive the new image
    unsigned char *result_image = malloc(width * height * sizeof(unsigned char));

    int size_frag_frame = lines_per_worker * height;

    printf("[Rank %d] Waiting result processing \n", rank);
     
    for(int worker = 1; worker <= numworkers; worker++){
        MPI_Status status;
        
        unsigned char *frag_image = malloc(size_frag_frame * sizeof(unsigned char));
        
        MPI_Recv(frag_image, size_frag_frame, MPI_UNSIGNED_CHAR, worker, 5, MPI_COMM_WORLD, &status);
        printf("[Rank %d] Image received for worker %d \n", rank, worker);

        int i = 0;
        for(int idx = (worker -1)*size_frag_frame; idx < worker * size_frag_frame; idx++){
            result_image[idx] = frag_image[i];
            i++;
        }

    }

    printf("[Rank %d] Saving image \n", rank);

    stbi_write_jpg("out/mpi_gray_image.jpg", width, height, 1, result_image, 100);

}

void worker_operations(int root, int rank){
    
    MPI_Status status;

    // receive image dims
    int width, height, channels, step_pixels; 
    MPI_Recv(&width, 1, MPI_INT, root, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&height, 1, MPI_INT, root, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&channels, 1, MPI_INT, root, 2, MPI_COMM_WORLD, &status);
    MPI_Recv(&step_pixels, 1, MPI_INT, root, 3, MPI_COMM_WORLD, &status);

    

    // prepare to receive the frag image
    unsigned char *image = malloc(step_pixels * sizeof(unsigned char));

    // receive frag image
    MPI_Recv(image, step_pixels, MPI_UNSIGNED_CHAR, root, 4, MPI_COMM_WORLD, &status);
    printf("[Rank %d] Image receive!\n", rank);

    // apply gray filter in image
    unsigned char *gray_img = gray_filter(image, width, height);
    printf("[Rank %d] Image is read to send\n", rank);

  
    MPI_Send(gray_img, width*height, MPI_UNSIGNED_CHAR, root, 5, MPI_COMM_WORLD);

    // clean memory use
    // stbi_image_free(gray_img);
    // stbi_image_free(image);   
}

int main(int argc, char *argv[]){
    int numtasks, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    int root = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Get_processor_name(hostname, &len);

    

    // checando quantidade de processos
    if(numtasks < 2){
        printf("Ei chapa, para funcionar, precisa de, no minimo, dois processos\n");
        return 1;
    }

    printf("[Rank %d] Hello!\n", rank);

    if(rank == root){

        root_operations(rank, numtasks);  

    } else {

        worker_operations(root, rank); 

    }

    MPI_Finalize();

    return 0;
}