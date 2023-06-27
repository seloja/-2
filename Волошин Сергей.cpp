#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <clocale>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    cout << "количество процессоров: " << omp_get_num_procs() << "\n";

    const int n = 10000000;
    int number_of_threads = 32;

    // Создание массива одинарной точности
    float* Asgl = new float[n];
    for (int i = 0; i < n; ++i) Asgl[i] = rand();

    // Суммирование массива одинарной точности
    double sum1 = 0;
    double start1 = omp_get_wtime();
    for (int i = 0; i < n; ++i) sum1 += Asgl[i];
    double end1 = omp_get_wtime();
    cout << "Время последовательного суммирования массива одинарной точности: " << (end1 - start1) << "\n";

    // Создание массива двойной точности
    double* Adbl = new double[n];
    for (int i = 0; i < n; ++i) Adbl[i] = rand();

    // Суммирование массива двойной точности
    double sum2 = 0;
    double start2 = omp_get_wtime();
    for (int i = 0; i < n; ++i) sum2 += Adbl[i];
    double end2 = omp_get_wtime();
    cout << "Время последовательного суммирования массива двойной точности: " << (end2 - start2) << "\n";
    cout << "\n";

    // Параллельное суммирование массива одинарной точности
    double sum3 = 0;
    double start3 = omp_get_wtime();
#pragma omp parallel num_threads(number_of_threads)
    {
        for (int i = 0; i < n; ++i) sum3 += Asgl[i];
    }
    double end3 = omp_get_wtime();
    cout << "Время параллельного суммирования массива одинарной точности: " << (end3 - start3) << "\n";

    // Параллельное суммирование массива двойной точности
    double sum4 = 0;
    double start4 = omp_get_wtime();
#pragma omp parallel num_threads(number_of_threads)
    {
        for (int i = 0; i < n; ++i) sum4 += Adbl[i];
    }
    double end4 = omp_get_wtime();
    cout << "Время параллельного суммирования массива двойной точности: " << (end4 - start4) << "\n";
    cout << "\n";
}
