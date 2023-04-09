#include "mpi.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <chrono>
using namespace std;

const int N = 300;

int main(int *argc, char** argv) {
	srand(time(NULL));
	int arr[N][N], i, j, indi, indj, difference, numtasks, rank, res1, res2;
	float averagevalue;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			arr[i][j] = rand() % N;
	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(arr, N * N, MPI_INT, 0, MPI_COMM_WORLD);
	int begin, end;
	auto start_time = MPI_Wtime();
	begin = rank * (N / numtasks); //номер процесса умножается на отношение размерности массива к количеству процессов
	end = begin + (N / numtasks);  //к началу приавляется отношение размерности массива к количеству процессов
	averagevalue = arr[0][0];
	//MPI_Bcast(&averagevalue, 1, MPI_SUM, 0, MPI_COMM_WORLD);
	for (i = begin; i < end; i++)
		for (j = 1; j < N; j++)
			averagevalue += arr[i][j];
	averagevalue /= N * N;
	difference = abs(arr[0][0] - averagevalue);
	//MPI_Bcast(&difference, 1, MPI_INT, 0, MPI_COMM_WORLD);
	indi = 0;
	//MPI_Bcast(&indi, 1, MPI_INT, 0, MPI_COMM_WORLD);
	indj = 0;
	//MPI_Bcast(&indj, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (i = begin; i < end; i++)
		for (j = 1; j < N; j++) {
			if (abs(arr[i][j] - averagevalue) < difference) {
				indi = i;
				indj = j;
				difference = abs(arr[i][j] - averagevalue);
			}
		}
	//MPI_Reduce(&res1, &res2, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	auto end_time = MPI_Wtime();
	cout << "The coordinates of the element closest to the average of all array elements:" << indi << ", " << indj << endl;
	cout << "Average value of all array elements:" << averagevalue << endl;
	cout << "The element closest to it: " << arr[indi][indj] << endl;
	cout << "Execution time of the main algorithm of the program:" << end_time - start_time << endl;
	MPI_Finalize();
	return 0;
}


