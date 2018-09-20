#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[]) {
	int A[100];
	int B[100];
 	int C[100];
	int i, rank, size;
  
	srand(1234);
 	for (i = 0; i < 100; i++) {
		A[i] = rand() % 1000;
		B[i] = rand() % 1000;
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
  
	// Scatter
	int chunkSize = ceil(100 / size);
	int receiveA[chunkSize];
	int receiveB[chunkSize];
	
	MPI_Scatter(
		(void *) A, chunkSize, MPI_INT,
		(void *) &receiveA, chunkSize, MPI_INT,
		0, MPI_COMM_WORLD
	);

	MPI_Scatter(
		(void *) B, chunkSize, MPI_INT,
		(void *) &receiveB, chunkSize, MPI_INT,
		0, MPI_COMM_WORLD
	);

	for (i = 0; i < chunkSize; i++) {
		C[i] = receiveA[i] + receiveB[i]; 
	}

	// Gather to C[100] = A[100] + B[100];
	int receiveC[100];
	MPI_Gather(C, chunkSize, MPI_INT, receiveC, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);   

	if (rank == 0) {
		for (i = 0; i < 100; i++) {
			printf("receiveC[%d]: %d\n", i, receiveC[i]);
		}
	}	

	MPI_Finalize();
}






