#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[]) {
  int A[100];
	int i, rank, size;
  srand(1234);

  for (i = 0; i < 100; i++)
    A[i] = rand() % 1000;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	// Scatter
	int chunkSize = ceil(100 / size);	
	int B[chunkSize];

	MPI_Scatter(
		(void *) A, chunkSize, MPI_INT,
		(void *) &B, chunkSize, MPI_INT,
		0, MPI_COMM_WORLD
	);

	// Receive the conditional integer
  int receive;

	if (rank == 0) {
		printf("Enter the integer: ");
		fflush(stdout);
  	scanf("%d", &receive);
	}

	// Boardcast [receive]
	MPI_Bcast(&receive, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	printf("Rank: %d, Receive: %d\n", rank, receive);
 
	// Reduce them to Manager
	int sum = 0;
	int count = 0;

	for (i = 0; i < chunkSize; i++)	{
		if (B[i] < receive) sum += 1;
	}

	MPI_Reduce(&sum, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) 
		printf("Rank: %d\tCount: %d\n", rank, count);
	

  MPI_Finalize();
}
