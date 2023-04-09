#include "mpi.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <chrono>
using namespace std;
const int N = 10;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "russian");
	srand(time(NULL));
	int arr[N][N], indi, indj, indi1, indj1, difference, numtasks, rank, begin, end;
	float averagevalue;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			arr[i][j] = rand() % N;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(arr, N * N, MPI_INT, 0, MPI_COMM_WORLD);
	auto start_time = MPI_Wtime();
	begin = rank * (N / numtasks); //����� �������� ���������� �� ��������� ����������� ������� � ���������� ���������
	end = begin + (N / numtasks);  //� ������ ����������� ��������� ����������� ������� � ���������� ���������
	averagevalue = arr[0][0];
	MPI_Bcast(&averagevalue, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	for (int i = begin; i < end; i++)
		for (int j = 1; j < N; j++)
			averagevalue += arr[i][j];
	averagevalue /= N * N;
	difference = abs(arr[0][0] - averagevalue);
	MPI_Bcast(&difference, 1, MPI_INT, 0, MPI_COMM_WORLD);
	indi = 0;
	MPI_Bcast(&indi, 1, MPI_INT, 0, MPI_COMM_WORLD);
	indj = 0;
	MPI_Bcast(&indj, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = begin; i < end; i++)
		for (int j = 1; j < N; j++) {
			if (abs(arr[i][j] - averagevalue) < difference) {
				indi = i;
				indj = j;
				difference = abs(arr[i][j] - averagevalue);
			}
		}
	MPI_Reduce(&indi, &indi1, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&indj, &indj1, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	auto end_time = MPI_Wtime();
	cout << "������s ��������, �������� �������� � �������� �������� ���� ��������� �������: " << indi1 << ", " << indj1 << endl;
	cout << "������� �������� ���� ��������� �������: " << averagevalue << endl;
	cout << "�������, �������� ������� � ����: " << arr[indi1][indj1] << endl;
	cout << "����� ���������� ��������� ��������� ���������: " << end_time - start_time << endl;
	MPI_Finalize();
	return 0;
}


