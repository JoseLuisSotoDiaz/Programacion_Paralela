/*
 ============================================================================
 Name        : MPI_LOR.c
 Author      : Jose
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <mpi.h>


    int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);

        // Get the number of processes and check only 4 are used.
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);


        // Determine root's rank
        int root_rank = 0;

        // Get my rank
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Each MPI process sends its rank to reduction, root MPI process collects the result
        bool my_value = (my_rank == 3);
        bool reduction_result = false;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_C_BOOL, MPI_LOR, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("The logical or of all values is %s.\n", reduction_result ? "true" : "false");
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
