#include <stdio.h>
#include <math.h>
#include <float.h> 

#include "integral_solver.h"

#define N 10000

double x(double x) { return x; } // f(x) = x

double x_2(double x) { return x*x; } // f(x) = x^2

double sinx(double x) { return sin(x); } // f(x) = sin(x)

double cosx(double x) { return cos(x); } // f(x) = cos(x)

double e_x(double x) { return exp(x); } // f(x) = e^x

typedef double (*func)(double); 

double integral(func f, double a, double b){

    if (f == NULL)
    { 
        printf("Ошибка вычисления интеграла.\n");
        return 1;
    }

    if (fabs(b-a) < DBL_EPSILON) 
    {
        return 0;
    }

    double sign = 1.0;
    if (a > b)
    {
        double tmp = a;
        a = b;
        b = tmp;
        sign = -1.0;
    }

    double h = (b-a)/N; 

    double sum = 0.0;
    sum += (f(a)+f(b))/2;

    for (int i = 1; i<N; i++)
    { 
        double x = a + h*i;
        sum+=f(x);
    }

    return sign * h * sum;
}
