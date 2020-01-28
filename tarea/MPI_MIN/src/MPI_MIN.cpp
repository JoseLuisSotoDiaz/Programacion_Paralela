/*
 ============================================================================
 Name        : MPI_MIN.c
 Author      : Jose
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <stdio.h>
    #include <stdlib.h>
    #include <mpi.h>


    int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);

        // Get the number of processes and check only 4 are used.
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        if(size != 7)
        {
            printf("Esta Aplicacion debe ser realizada con 4 procesos.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }

        // Determine root's rank
        int root_rank = 0;

        // Get my rank
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Each MPI process sends its rank to reduction, root MPI process collects the result
        int reduction_result = 0;
        MPI_Reduce(&my_rank, &reduction_result, 1, MPI_INT, MPI_MIN, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El minimo rank es %d.\n", reduction_result);
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
