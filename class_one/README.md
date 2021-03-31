# Simple examples of OpenMP

# Motivation
Hello humans! in this module, I will make a small kickoff of the use of the OpenMP framework, enough to arouse interest in this tool and be able to apply it in your code. Fasten your seat belts and welcome aboard!


# Installation
It is very difficult to install OpenMP, use this command on your terminal:

``` sudo apt-get install libomp-dev ```

and end

# Compilation

To compile this code, use the following command:

```gcc -Wall -fopenmp -o main main.c -lm```

To perform, use:

``` OMP_NUM_THREADS=<num_of_threads> ./main ``` 

or just

``` ./main ```



