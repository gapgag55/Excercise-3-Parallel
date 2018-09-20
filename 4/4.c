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
	int chunkSize = length;
	
	// Receiver receives the row of A[i]
	int receive[chunkSize];
	
	// Adder sums the value as vertical
	int sumVertical[chunkSize];	

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


	// Each worker got A[i] like [1, 2, 3, 4, 5, 6, 7, 8]
	// Each worker do sum to be [76, 77, 78, 79, 80, 81, 82, 83]
	MPI_Reduce(&receive, &sumVertical, length, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	// The manager distributes 8 values to each worker
	MPI_Scatter(
		(void *) sumVertical, 1, MPI_INT,
		(void *) &number, 1, MPI_INT,
		0, MPI_COMM_WORLD 	
	);
	
	// Workers do sum to the manager
	MPI_Reduce(&number, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	// the manager prints out
 	if (rank == 0)
		printf("Summation is: %d\n", sum);

  MPI_Finalize();
}
