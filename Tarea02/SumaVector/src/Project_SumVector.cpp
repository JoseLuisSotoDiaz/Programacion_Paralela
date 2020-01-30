/*
 ============================================================================
 Name        : Project_SumVector.c
 Author      : Soto Diaz Jose Luis
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */

#include "mpi.h" 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {

	int my_rank,    comm_sz,    n = 100;
	MPI_Status status;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	srand(time(NULL) + my_rank);

	if (my_rank != 0) {

		int a[m], b[m], c[m];

		MPI_Recv(&a, m, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&b, m, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

		int inicio = my_rank * (m / comm_sz);
		int final = inicio + m/ comm_sz;

		for (int i = inicio; i < final; i++) {
			c[i] = a[i] + b[i];
		}

		MPI_Send(&c, m, MPI_INT, 0, 0, MPI_COMM_WORLD);

	} else {

		int x[m], y[m], z[m];

		for (int i = 0; i < m; i++) {
			x[i] = rand() % 1000 + 1;
			y[i] = rand() % 1000 + 1;
			cout << "X[" << i << "] = " << x[i] << endl;
			cout << "Y[" << i << "] = " << y[i] << endl;
		}

		for (int i = 1; i < comm_sz; i++) {
			MPI_Send(&x, m, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&y, m, MPI_INT, i, 1, MPI_COMM_WORLD);
		}

		for (int i = 0; i < m / comm_sz; i++) {
			z[i] = x[i] + y[i];
		}

		for (int i = 1; i < comm_sz; i++) {

			int aux[m];

			MPI_Recv(&aux, m, MPI_INT, i, 0, MPI_COMM_WORLD, &status);

			int inicio = i * (m / comm_sz);
			int final = inicio + m / comm_sz;

			for (int j = inicio; j < final; j++) {
				z[j] = aux[j];
			}

		}

		for (int i = 0; i < m; i++) {
			cout << "Z[" << i << "] = " << z[i] << endl;
		}

	}

	MPI::Finalize();
	return 0;
}

