#include "mpi.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <chrono>
using namespace std;

const int N = 100;

int main(int *argc, char** argv) {
	int numtasks, rank;
	srand(time(NULL));
	int arr[N][N], i, j, indi, indj, difference;
	float averagevalue;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			arr[i][j] = rand() % N;
	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	cout << "Hello MPI from prouses: " << rank << ", total number of prouseses: " << numtasks << endl;
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(arr, N * N, MPI_INT, 0, MPI_COMM_WORLD);
	auto start_time = MPI_Wtime();
	averagevalue = arr[0][0];
	for (i = 0; i < N; i++)
		for (j = 1; j < N; j++)
			averagevalue += arr[i][j];
	averagevalue /= N * N;
	MPI_Bcast(&averagevalue, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	difference = abs(arr[0][0] - averagevalue);
	MPI_Bcast(&difference, 1, MPI_INT, 0, MPI_COMM_WORLD);
	indi = 0;
	indj = 0;
	for (i = 0; i < N; i++)
		for (j = 1; j < N; j++) {
			if (abs(arr[i][j] - averagevalue) < difference) {
				indi = i;
				indj = j;
				difference = abs(arr[i][j] - averagevalue);
			}
		}
	auto end_time = MPI_Wtime();
	MPI_Finalize();
	cout << "The coordinates of the element closest to the average of all array elements:" << indi << ", " << indj << endl;
	cout << "Average value of all array elements:" << averagevalue << endl;
	cout << "The element closest to it: " << arr[indi][indj] << endl;
	cout << "Execution time of the main algorithm of the program:" << end_time - start_time << endl;
	return 0;
}


