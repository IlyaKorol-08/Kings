#include <stdio.h>
#include <math.h> // библиотека для математических функций
#include <float.h> // библиотека для DBL_EPSILON (минимальное положительное машинно-представимое число)

#define N 10000 // число отрезков разбиения (константа)

typedef double (*func)(double); // указатель функции

double integral(func f, double a, double b){ // функция вычисления интеграла

    if (f == NULL){ // проверка на передачу указателем адреса
    printf("Ошибка вычисления интеграла.\n");
    return 1;
    }

    if (fabs(b-a) < DBL_EPSILON) { // проверяем совпадение пределов интегрирования через эпсилон
        return 0;
    }

    double h = (b-a)/N; // шаг (длина отрезков)

    double sum = 0.0;
    sum += (f(a)+f(b))/2;

    for (int i = 1; i<N; i++){ 
        double x = a + h*i;
        sum+=f(x);
    }

    return h * sum;
}