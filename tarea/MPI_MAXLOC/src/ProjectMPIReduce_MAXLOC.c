/*
 ============================================================================
 Name        : ProjectMPIReduce_MAXLOC.c
 Author      : JOSE
 Version     :
 Copyright   : Your copyright notice
 Description :
 * Compile:  mpicc -g -Wall -o ProjectMPIReduce_MAXLOC ProjectMPIReduce_MAXLOC.c
 * Run:      mpiexec -n <number of processes> ./ProjectMPIReduce_MAXLOC
 ============================================================================
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

	int my_rank, comm_sz;

	struct {
		int val;
		int rank;
	} random, result;

	/* Let the system do what it needs to start up MPI */
	MPI_Init(NULL, NULL);

	/* Get my process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out how many processes are being used */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	srand(time(NULL) + my_rank);

	random.val = rand() % 100 + 1;
	random.rank = my_rank;

	printf("El valor generado es %d y esta localizado en %d\n", random.val, random.rank);

	/* Add up the integrals calculated by each process */
	MPI_Reduce(&random, &result, 1, MPI_FLOAT_INT, MPI_MAXLOC, 0,
	MPI_COMM_WORLD);

	/* Print the result */
	if (my_rank == 0) {
		printf("El maximo valor es = %d y esta localizado en %d\n", result.val, result.rank);
	}

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
}
