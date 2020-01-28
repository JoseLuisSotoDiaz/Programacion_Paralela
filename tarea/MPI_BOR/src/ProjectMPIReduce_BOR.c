/*
 ============================================================================
 Name        : ProjectMPIReduce_BOR.c
 Author      : Jose
 Version     :
 Copyright   : Your copyright notice
 Description :
 * Compile:  mpicc -g -Wall -o ProjectMPIReduce_MAX ProjectMPIReduce_BOR.c
 * Run:      mpiexec -n <number of processes> ./ProjectMPIReduce_BOR
 ============================================================================
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

   int my_rank, comm_sz, random, result;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   srand(time(NULL) + my_rank);

   random = rand() % 100 + 1;

   printf("El numero aleatorio en el proceso %d es = %d\n", my_rank, random);

   /* Add up the integrals calculated by each process */
   MPI_Reduce(&random, &result, 1, MPI_INT, MPI_BOR, 0,
         MPI_COMM_WORLD);

   /* Print the result */
   if (my_rank == 0) {
      printf("El OR logico bit a bit es = %d\n", result);
   }

   /* Shut down MPI */
   MPI_Finalize();

   return 0;
}
