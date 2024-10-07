#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

// Функция для заполнения матрицы случайными числами в диапазоне [-100, 100]
void fillMatrix(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 201 - 100;  // Генерация случайного числа в диапазоне [-100, 100]
        }
    }
}

// Функция для вывода матрицы на экран
void printMatrix(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));  // Инициализация генератора случайных чисел

    int N;  // Размер матрицы
    cout << "Введите размер матрицы N: ";
     std::cin >> N;

    // Создание матрицы размером N x N
    int** matrix = new int* [N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }

    // Заполнение матрицы случайными числами
    fillMatrix(matrix, N);

    cout << "Сгенерированная матрица:" << endl;
    printMatrix(matrix, N);

    // Поиск строки с наибольшим количеством положительных чисел
    int maxPositives = 0;  // Максимальное количество положительных чисел
    int rowIndex = 0;  // Индекс строки с наибольшим количеством положительных чисел
    for (int i = 0; i < N; ++i) {
        int positiveCount = 0;  // Счетчик положительных чисел в строке
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] > 0) {
                ++positiveCount;
            }
        }
        // Обновление максимального количества положительных чисел и индекса строки
        if (positiveCount > maxPositives) {
            maxPositives = positiveCount;
            rowIndex = i;
        }
    }

    // Создание нового массива, инициализированного найденной строкой
    int* newArray = new int[N];
    for (int j = 0; j < N; ++j) {
        newArray[j] = matrix[rowIndex][j];
    }

    cout << "Строка с наибольшим количеством положительных чисел (индекс " << rowIndex << "):" << endl;
    for (int j = 0; j < N; ++j) {
        cout << newArray[j] << ' ';
    }
    cout << endl;

    // Освобождение памяти, выделенной для матрицы и массива
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i]; // Освобождаем память для каждой строки
    }
    delete[] matrix; // Освобождаем память для массива указателей
    delete[] newArray; // Освобождаем память для одномерного массива

    return 0;
}
