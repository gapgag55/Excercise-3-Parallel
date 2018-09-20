#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int A[100];
  srand(1234);
  for (int i = 0; i < 100; i++) {
    A[i] = rand() % 1000;
  }

  // Scatter as distinct part

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int receive;
  scanf("Enter the integer: %d", &receive);

  // Board_cast [receive]

  // Count the value less than the [receive]

  // Reduce them to Manager


  MPI_Finalize();
}