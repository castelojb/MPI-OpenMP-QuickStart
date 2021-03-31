# Simple examples of MPI

# Motivation
Hello humans! In this module, we will explore the MPI framework, how to send variables, receive and orchestrate distributed computing, to infinity and beyond!


# Installation
It is very difficult to install MPI, use this command on your terminal:

``` sudo apt-get install libopenmpi-dev ```

and end

# Compilation

To compile this code, use the following command:

``` mpicc -Wall -o main main.c -lm ```

To perform, use:

``` mpirun -np <num_of_clusters> ./main ``` 

