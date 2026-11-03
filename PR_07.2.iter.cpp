#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int n, const int Low, const int High);
void Print(int** a, const int n);
int  MinColInRow(int** a, const int n, const int i);
void MoveMinsToAntiDiagonal(int** a, const int n);

#ifndef UNIT_TEST   // під час unit-тестування функція main підміняється тестом
int main()
{
    srand((unsigned)time(NULL));

    int Low = -9;   // нижня межа діапазону значень елементів матриці
    int High = 9;   // верхня межа діапазону значень елементів матриці
    int n;          // розмір квадратної матриці (кількість рядків = кількість стовпців)
    cout << "n = "; cin >> n;

    // a – вказівник на динамічну матрицю n x n цілих чисел
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];

    Create(a, n, Low, High);
    cout << "Initial matrix:";
    Print(a, n);

    MoveMinsToAntiDiagonal(a, n);
    cout << "Modified matrix (row minimums are on the anti-diagonal):";
    Print(a, n);

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}
#endif

// Заповнює матрицю випадковими цілими числами з діапазону [Low; High].
// a – матриця (вихідний параметр), n – розмір матриці,
// Low, High – межі діапазону значень (вхідні параметри).
void Create(int** a, const int n, const int Low, const int High)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

// Виводить матрицю у вигляді таблиці (форматний вивід, ширина поля – 4).
void Print(int** a, const int n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

// Шукає номер стовпця мінімального елемента в рядку з номером i.
// Повертає номер стовпця (перший з однакових мінімальних).
// minJ – номер стовпця поточного мінімального елемента рядка.
int MinColInRow(int** a, const int n, const int i)
{
    int minJ = 0;
    for (int j = 1; j < n; j++)
        if (a[i][j] < a[i][minJ])
            minJ = j;
    return minJ;
}

// Міняє місцями елементи кожного рядка так, щоб мінімальний елемент
// рядка i опинився на побічній діагоналі, тобто у стовпці n-1-i.
// minJ – стовпець мінімуму рядка; diagJ – стовпець побічної діагоналі
// для рядка i; tmp – допоміжна змінна для обміну елементів.
void MoveMinsToAntiDiagonal(int** a, const int n)
{
    for (int i = 0; i < n; i++)
    {
        int minJ = MinColInRow(a, n, i);
        int diagJ = n - 1 - i;
        int tmp = a[i][minJ];
        a[i][minJ] = a[i][diagJ];
        a[i][diagJ] = tmp;
    }
}