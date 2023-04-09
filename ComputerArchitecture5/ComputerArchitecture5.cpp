#include <iostream>
#include <Windows.h>
#include <cmath>
#include <chrono>
using namespace std;

const int N = 300;

int main() {
	setlocale(LC_ALL, "russian");
	srand(time(NULL));
	int arr[N][N], i, j,indi, indj, difference;
	float averagevalue;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			arr[i][j] = rand() % N;
	auto start_time = chrono::steady_clock::now();
	averagevalue = arr[0][0];
	for (i = 0; i < N; i++)
		for (j = 1; j < N; j++)
			averagevalue += arr[i][j];
	averagevalue /= N*N;
	difference = abs(arr[0][0] - averagevalue);
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
	auto end_time = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
	cout << "Координаты элемента, наиболее близкого к среднему значению всех элементов массива: " << indi << ", " << indj << endl;
	cout << "Среднее значение всех элементов массива: " << averagevalue << endl;
	cout << "Элемент, наиболее близкий к нему: " << arr[indi][indj] << endl;
	cout << "Время выполнения основного алгоритма программы: " << elapsed_ms.count() << endl;
	return 0;
}


