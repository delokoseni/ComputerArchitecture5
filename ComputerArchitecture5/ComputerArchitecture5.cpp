#include "mpi.h"
#include <iostream>

using namespace std;

int main(int *argc, char **argv) {
	int numtasks, rank;
	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	cout << "Hello MPI from prouses: " << rank <<", total number of prouseses: " << numtasks << endl;
	MPI_Finalize();
	return 0;
}