#include <assert.h>
#include <math.h>

#include "integral_solver.h"

void test_integral_x()
{
    double a = -1.0;
    double b = 4.0;

    double res = integral(x, a, b);
    
    assert(fabs(res-7.5) < 0.1);
}

void test_integral_x_2()
{
    double a = 0;
    double b = 3;

    double res = integral(x_2, a, b);

    assert(fabs(res-9.0) < 0.1);
}

void test_integral_sinx()
{
    double a = -1.0;
    double b = 1.0;

    double res = integral(sinx, a, b);
        
    assert(fabs(res-0) < 0.1);
}

void test_integral_cosx()
{
    double a = 1.0;
    double b = 4.0;

    double res = integral(cosx, a, b);
        
    assert(fabs(res+1.6) < 0.1);
}

void test_integral_e_x()
{
    double a = -2.0;
    double b = 1.0;

    double res = integral(e_x, a, b);
        
    assert(fabs(res-2.6) < 0.1);
}

int main()
{
    test_integral_x();
    test_integral_x_2();
    test_integral_sinx();
    test_integral_cosx();
    test_integral_e_x();
    return 0;
}
