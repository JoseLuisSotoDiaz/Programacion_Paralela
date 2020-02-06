/*
 ============================================================================
 Name        : Problema2.c
 Author      : Jose
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */

#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

	int rank, contador;
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Send(&rank, 1, MPI_INT, rank, 0, MPI_COMM_WORLD);

	MPI_Recv(&contador, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, &estado);

	cout << "El proceso " << rank << " y recibi " << contador << endl;

	MPI_Finalize();

	return 0;

}
