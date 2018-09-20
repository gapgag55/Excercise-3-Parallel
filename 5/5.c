#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[]) {
  int length = 8;
	int A[length][length];
  int i, j, rank, size;

	srand(1234);
 
  MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) {
 		for (i = 0; i < length; i++) {
    	for (j = 0; j < length; j++) {
      	A[i][j] = 1;
	  	}
  	}
	}

	// Let do sunmmation
	int chunkSize = length * 2;
	int chunkSize2 = chunkSize / size;
	int chunkSize3 = chunkSize2 / size;
	// Receiver receives the row of A[i]
	int receive[chunkSize];
	int receive2[chunkSize2];
	int receive3[chunkSize3];
	// Adder sums the value as vertical
	int sumVertical[chunkSize];	
	int sumVertical2[chunkSize2];
	// Adder sums the value as horizontal
	int number;

	// The our result
	int sum;

	// Send A[i] to each worker
	MPI_Scatter(
		(void *) A, chunkSize, MPI_INT,
		(void *) &receive, chunkSize, MPI_INT,
		0, MPI_COMM_WORLD
	);

	// Each worker got A[i] like [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
	MPI_Reduce(&receive, &sumVertical, length * 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	// The manager distributes 4 values to each worker
	MPI_Scatter(
		(void *) sumVertical, chunkSize2, MPI_INT,
		(void *) &receive2, chunkSize2, MPI_INT,
		0, MPI_COMM_WORLD 	
	);
	
	// Each worker got numbers[i] like [1, 2, 3, 4]
	MPI_Reduce(&receive2, &sumVertical2, length, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	MPI_Scatter(
		(void *) sumVertical2, chunkSize3, MPI_INT,
		(void *) &receive3, chunkSize3, MPI_INT,
		0, MPI_COMM_WORLD
	);

	// Workers do sum to the manager
	MPI_Reduce(&receive3, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	// the manager prints out
 	if (rank == 0)
		printf("Summation is: %d\n", sum);

  MPI_Finalize();
}
