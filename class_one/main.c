// Import OpenMP
#include <omp.h>

// Basic C stuff
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>



void simple_loop(int n){

    #pragma omp parallel for
    for(int i=0; i<10; i++){

        // your computing        
        sleep(n);
        
    }

}

void simple_loop_nested(int n){

    #pragma omp parallel for collapse(2)
    for(int i=0; i<10; i++){
        for(int i=0; i<10; i++){
            sleep(n);
        }
        
    }

}


void simple_loop_var_usage(int n){

    #pragma omp parallel for
    for(int i=0; i<10; i++){
        
        printf("%d \n", i);
        sleep(n);
        
    }

}

int main(int argc, char *argv[]){

    // runing example
    simple_loop_var_usage(1);
    return 0;

}