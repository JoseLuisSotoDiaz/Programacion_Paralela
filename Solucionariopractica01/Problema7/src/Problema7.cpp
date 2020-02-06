/*
 ============================================================================
 Name        : Problema7.c
 Author      : Jose
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
using namespace std;

void Get_Input(int comm_sz, int my_rank, int* n_p);
 
int main(void) {

	int my_rank, comm_sz, n, local_n;

	int local_a, local_b;

	int local_int, total_int;

	MPI_Init(NULL, NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	Get_Input(comm_sz, my_rank, &n);

	local_n = n / comm_sz;

	local_a = 1 + my_rank*local_n;
	local_b = local_a + local_n - 1;

	local_int = 1;

	for (int i = local_a; i <= local_b; i++ ){
		local_int*= i;
	}

	MPI_Reduce(&local_int, &total_int, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

	if ( my_rank == 0) {
		printf("El factorial es: %d\n", total_int);
	}

	MPI_Finalize();

	return 0;

}

void Get_Input(int comm_sz, int my_rank, int* n_p ) {

	if ( my_rank  == 0) {
		printf("Numero a hallar el factorial\n");
		scanf("%d", n_p);
	}

	MPI_Bcast(n_p, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

