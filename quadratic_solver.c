#include "quadratic_solver.h"
#include <math.h>

void solve_quadratic(double a, double b, double c, double *roots) {
    double discriminant = b * b - 4.0 * a * c;
    
    if (discriminant == 0.0) {
        roots[0] = -b / (2.0 * a);
    } else if (discriminant > 0.0) {
        double sqrt_d = sqrt(discriminant);
        
        if (b >= 0.0) {
            roots[0] = (-b - sqrt_d) / (2.0 * a);
            roots[1] = (2.0 * c) / (-b - sqrt_d);
        } else {
            roots[0] = (2.0 * c) / (-b + sqrt_d);
            roots[1] = (-b + sqrt_d) / (2.0 * a);
        }
        
        if (roots[0] > roots[1]) {
            double temp = roots[0];
            roots[0] = roots[1];
            roots[1] = temp;
        }
    }
}
