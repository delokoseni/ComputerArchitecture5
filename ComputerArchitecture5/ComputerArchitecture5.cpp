#include "mpi.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <chrono>
using namespace std;
const int N = 300;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "russian");
	srand(time(NULL));
	int arr[N][N], indi, indj, difference, numtasks, rank, begin, end;
	float averagevalue, averagevalue1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			arr[i][j] = rand() % N;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&(arr[0][0]), N * N, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&averagevalue, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&difference, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&indi, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&indj, 1, MPI_INT, 0, MPI_COMM_WORLD);

	auto start_time = MPI_Wtime();
	begin = rank * (N / numtasks); //номер процесса умножается на отношение размерности массива к количеству процессов
	end = begin + (N / numtasks);  //к началу приавляется отношение размерности массива к количеству процессов
	averagevalue = arr[0][0];
	for (int i = begin; i < end; i++)
		for (int j = 1; j < N; j++)
			averagevalue += arr[i][j];
	averagevalue /= N * N;
	difference = abs(arr[0][0] - averagevalue);
	indi = 0;
	indj = 0;
	for (int i = begin; i < end; i++)
		for (int j = 1; j < N; j++) {
			if (abs(arr[i][j] - averagevalue) < difference) {
				indi = i;
				indj = j;
				difference = abs(arr[i][j] - averagevalue);
			}
		}
	auto end_time = MPI_Wtime();
	if (rank == 0) {
		cout << "Координаты элемента, наиболее близкого к среднему значению всех элементов массива: " << indi << ", " << indj << endl;
		cout << "Среднее значение всех элементов массива: " << averagevalue << endl;
		cout << "Элемент, наиболее близкий к нему: " << arr[indi][indj] << endl;
		cout << "Время выполнения основного алгоритма программы: " << end_time - start_time << endl;
	}
	MPI_Finalize();
	return 0;
}


