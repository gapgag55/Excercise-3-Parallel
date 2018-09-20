#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int A[100];
  srand(1234);
  for (int i = 0; i < 100; i++) {
    A[i] = i;
  }

  int rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int B[100];
  MPI_Scatter((void *) A, 100, MPI_INT, (void *) &B, 100, MPI_INT, 0, MPI_COMM_WORLD);

  printf("[%d] Received B[0] = %d\n", rank, B[0]);
  MPI_Finalize();
}