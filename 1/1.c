#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[]) {
  	int A[100];
	int i, rank, size;
	srand(1234);  

	for (i = 0; i < 100; i++) {
		A[i] = rand() % 1000;
	}

  	MPI_Init(&argc, &argv);
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int chunkSize = ceil(100 / size);
  	int B[chunkSize];
  	MPI_Scatter(
		(void *) A, chunkSize, MPI_INT, 
		(void *) &B, chunkSize, MPI_INT, 
		0, MPI_COMM_WORLD
	);
  	
	// Let do as local
	int maximum = B[0];
	int minimum = B[0];
	double average = 0;
	
	for (i = 1; i < chunkSize; i++) {
		//printf("[%d] Received B[%d] = %d\n", rank, i, B[i]);
  		if (B[i] < minimum) minimum = B[i];
		if (B[i] > maximum) maximum = B[i];
		average += B[i];
	}

	average = average / chunkSize;
	printf("[Local %d]: max: %d\tmin: %d\t avg: %.2f\n", rank, maximum, minimum, average);
		
	
	// Let do as global
	int max;
	int min;
	double avg;

	MPI_Reduce(&maximum, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); 
	MPI_Reduce(&minimum, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD); 
	MPI_Reduce(&average, &avg, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 
	
	if (rank == 0) 
		printf("[Global %d]: max: %d\tmin: %d\t avg: %.2f\n", rank, max, min, avg / size);

	MPI_Finalize();
}
