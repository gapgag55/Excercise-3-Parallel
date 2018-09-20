#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int A[8][8];
  srand(1234);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      A[i][j] = rand() % 1000;
    }
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Calculate the summation of all elements using MPI Collective communation on 8 processes
  // without MPI_Send and MPI_Recv

  MPI_Finalize();
}