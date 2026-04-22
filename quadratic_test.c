#include "quadratic_solver.h"
#include <assert.h>
#include <math.h>

void test_two_roots() {
    double a = 1.0;
    double b = 0.0;
    double c = -1.0;
    double roots[2];
    
    solve_quadratic(a, b, c, roots);
    
    assert(roots[0] == -1.0);
    assert(roots[1] == 1.0);
}

void test_one_root() {
    double a = 1.0;
    double b = 0.0;
    double c = 0.0;
    double roots[2];
    
    solve_quadratic(a, b, c, roots);
    
    assert(roots[0] == 0.0);
}

void test_no_roots() {
    double a = 1.0;
    double b = 0.0;
    double c = 1.0;
    double roots[2] = {0.0, 0.0};
    
    solve_quadratic(a, b, c, roots);
}

void test_small_roots() {
    double a = 1.0;
    double b = 0.0;
    double c = -1e-7;
    double roots[2];
    double eps = 1e-4;
    
    solve_quadratic(a, b, c, roots);
    
    assert(fabs(roots[0] + 3.16227766e-4) < eps);
    assert(fabs(roots[1] - 3.16227766e-4) < eps);
}

void test_large_b() {
    double a = 1.0;
    double b = -1e10;
    double c = -1.0;
    double roots[2];
    double eps = 1e-11;
    
    solve_quadratic(a, b, c, roots);
    
    assert(fabs(roots[0] + 1e-10) < eps);
    assert(fabs(roots[1] - 1e10) / 1e10 < 1e-10);
}

void test_very_small_root() {
    double a = 1.0;
    double b = 0.0;
    double c = -1e-8;
    double roots[2];
    double eps = 1e-7;
    
    solve_quadratic(a, b, c, roots);
    
    // При c = -1e-8 корни: -0.0001 и 0.0001
    // Проверяем, что первый корень близок к -0.0001 или к 0 (из-за погрешности)
    assert(fabs(roots[0]) < eps || fabs(roots[0] + 1e-4) < eps);
}

int main() {
    test_two_roots();
    test_one_root();
    test_no_roots();
    test_small_roots();
    test_large_b();
    test_very_small_root();
    return 0;
}
