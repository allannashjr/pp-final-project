/* File: final.c
 * 
 * 
 */

#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void) {

	int comm_sz, my_rank;

	/* Start Up MPI */
	MPI_Init(NULL, NULL);

	/* Get the Number of Processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	/* Get the Rank Among All the Processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		printf("=========================================\n");
		printf("|| Welcome to the Final Project for PP ||\n");
		printf("=========================================\n");
	}

	/* Shut Down MPI */
	MPI_Finalize();

	return 0;
}
