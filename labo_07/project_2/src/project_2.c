/*
 ============================================================================
 Name        : project_2.c
 Author      : Breiner
 Version     :
 Copyright   : Your copyright notice
 Description : Calculate Pi in MPI
 ============================================================================
 */
/*
 ============================================================================
 Name        : prog00-HelloWorld.c
 Author      : Herminio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello PThreads World in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global variable: */
int thread_count;
int n;
int* fibseq;


/* Thread function */
void* Hello(void* rank);

int main(int argc, char* argv[]) {
	long thread; /* Use long in case of a 64 − bit system */
	pthread_t* thread_handles;
	/* Get number of threads from command line */
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	printf("Ingresa el numero de fibonacci n\n");
	   scanf("%d", &n);

	   fibseq = (int *)malloc((n + 1) * sizeof(int));

	for (thread = 0; thread < thread_count; thread++) {
		pthread_create(&thread_handles[thread],
						NULL,
						Hello,
						(void*) thread);
		pthread_join(thread_handles[thread], NULL);
	}


	printf("Hello from the main thread\n");
	/*for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread],
						NULL);*/

	if (n >= 2) {
		fibseq[n] = fibseq[n-1] + fibseq[n-2];

	}
		for (int i = 0; i <= n; i++) {
		printf("%d ", fibseq[i]);
	}
	free(thread_handles);
	return 0;
}/* main */

void* Hello(void* rank) {


	long my_rank = (long) rank;
	/* Use long in case of 64 − bit system */

	int local_n = n/thread_count;

	int local_a = my_rank*local_n;
    int local_b = local_a + local_n - 1;

	for (int i = local_a; i <= local_b; i++) {

		if(i == 0){
			fibseq[i] = 0;
			printf("%d\n", fibseq[i]);
		}

		if(i == 1){
					fibseq[i] = 1;
					printf("%d\n", fibseq[i]);
				}
		if (i >= 2) {
			fibseq[i] = fibseq[i-1] + fibseq[i-2];
			printf("%d\n", fibseq[i]);
		}


	 }

	/*for (int j=local_a; j < local_b; j++)
	   printf("%d\n", fibseq[j]);*/


	/* accessible to all threads */
	printf("Hello from thread %ld of %d\n", my_rank, thread_count);

	return NULL;


}/* Hello */





