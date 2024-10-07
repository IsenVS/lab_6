#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <windows.h>
using namespace std;

// Функция для заполнения матрицы случайными числами в диапазоне [100, 200]
void fillMatrix(int** matrix, int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 101 + 100;  // Генерация случайного числа в диапазоне [100, 200]
        }
    }
}

// Функция для вывода матрицы на экран
void printMatrix(int** matrix, int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(0)));  // генератор случайных чисел

    int M, N;  // Размер матрицы
    cout << "Введите размер матрицы M и N: ";
     std::cin >> M >> N;

    // Создание матрицы размером M x N
    int** matrix = new int* [M];
    for (int i = 0; i < M; ++i) {
        matrix[i] = new int[N];
    }

    // Заполнение матрицы случайными числами
    fillMatrix(matrix, M, N);

    cout << "Сгенерированная матрица:" << endl;
    printMatrix(matrix, M, N);

    // Подсчет частоты каждого числа в матрице
    unordered_map<int, int> frequencyMap;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            frequencyMap[matrix[i][j]]++;
        }
    }

    // Поиск числа, которое встречается наибольшее количество раз
    int maxFrequency = 0;  // Максимальная частота
    int mostFrequentNumber = 0;  // Число, которое встречается наибольшее количество раз
    bool found = false;  // Было ли найдено число, которое встречается более одного раза

    for (const auto& entry : frequencyMap) {
        if (entry.second > maxFrequency) {
            maxFrequency = entry.second;
            mostFrequentNumber = entry.first;
            found = true;
        }
    }

    if (found && maxFrequency > 1) {
        cout << "Число, которое встречается наибольшее количество раз: " << mostFrequentNumber << " (встречается " << maxFrequency << " раз)" << endl;
    }
    else {
        cout << "Нет числа, которое встречается более одного раза." << endl;
    }

    // Освобождение памяти
    for (int i = 0; i < M; ++i) {
        delete[] matrix[i];  // Освобождаем память для каждой строки
    }
    delete[] matrix;  // Освобождаем память для массива указателей

    return 0;
}
