#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <windows.h>

using namespace std;

const int HEIGHT = 10;
const int WIDTH = 10;
const char ALIVE = '1';
const char DEAD = '-';

// Функция для вывода текущего состояния поля
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << std::endl;
    }
}

// Функция для инициализации начального состояния поля с фиксированными клетками
vector<vector<char>> initializeFixedGrid(int height, int width) {
    vector<vector<char>> grid(height, vector<char>(width, DEAD));
    grid[1][2] = ALIVE;
    grid[2][3] = ALIVE;
    grid[3][1] = ALIVE;
    grid[3][2] = ALIVE;
    grid[3][3] = ALIVE;
    return grid;
}

// Функция для рандомной инициализации начального состояния поля
vector<vector<char>> initializeRandomGrid(int height, int width) {
    vector<vector<char>> grid(height, vector<char>(width, DEAD));
    srand(time(0));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (rand() % 4 == 0) {  // 25% вероятность, что клетка будет живой
                grid[i][j] = ALIVE;
            }
        }
    }
    return grid;
}

// Функция для подсчета количества живых соседей вокруг клетки (x, y)
int countAliveNeighbors(const vector<vector<char>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;  // Пропускаем саму клетку
            int ni = (x + i + HEIGHT) % HEIGHT;  // Координаты с учетом замыкания по вертикали
            int nj = (y + j + WIDTH) % WIDTH;    // Координаты с учетом замыкания по горизонтали
            if (grid[ni][nj] == ALIVE) {
                count++;
            }
        }
    }
    return count;
}

// Функция для получения следующего поколения поля по классическим правилам
vector<vector<char>> getNextGenerationClassic(const vector<vector<char>>& grid) {
    vector<vector<char>> newGrid = grid;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int aliveNeighbors = countAliveNeighbors(grid, i, j);
            if (grid[i][j] == ALIVE) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j] = DEAD;
                }
            }
            else {
                if (aliveNeighbors == 3) {
                    newGrid[i][j] = ALIVE;
                }
            }
        }
    }
    return newGrid;
}

// Функция для получения следующего поколения поля по оригинальным правилам
vector<vector<char>> getNextGenerationOriginal(const vector<vector<char>>& grid) {
    vector<vector<char>> newGrid = grid;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int aliveNeighbors = countAliveNeighbors(grid, i, j);
            if (grid[i][j] == ALIVE) {
                if (aliveNeighbors == 0 || aliveNeighbors > 4) {
                    newGrid[i][j] = DEAD;
                }
            }
            else {
                if (aliveNeighbors == 2) {
                    newGrid[i][j] = ALIVE;
                }
            }
        }
    }
    return newGrid;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<vector<char>> grid;
    int choice;

    cout << "Выберите начальное состояние:\n1. Фиксированные клетки\n2. Рандомные клетки\n";
    cin >> choice;

    if (choice == 1) {
        grid = initializeFixedGrid(HEIGHT, WIDTH);
    }
    else {
        grid = initializeRandomGrid(HEIGHT, WIDTH);
    }

    cout << "Выберите правила:\n1. Классические правила\n2. Оригинальные правила\n";
    cin >> choice;

    int generations = 50;  // Ограничение на количество поколений
    for (int gen = 0; gen < generations; ++gen) {
        printGrid(grid);  // Вывод текущего состояния поля
        if (choice == 1) {
            grid = getNextGenerationClassic(grid);  // Обновление состояния поля по классическим правилам
        }
        else {
            grid = getNextGenerationOriginal(grid);  // Обновление состояния поля по оригинальным правилам
        }
        Sleep(3000);  // Задержка на 200 миллисекунд
        cout << "\033[H\033[J";  // Очистка экрана
    }
    return 0;
}
