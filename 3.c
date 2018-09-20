#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int A[100];
  int B[100];
  int C[100];

  srand(1234);
  for (int i = 0; i < 100; i++) {
    A[i] = rand() % 1000;
    B[i] = rand() % 1000;
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Scatter

  // Gather to C[100] = A[100] + B[100];

  MPI_Finalize();
}