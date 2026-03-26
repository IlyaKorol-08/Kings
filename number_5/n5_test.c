#include "func_integral.c"
#include "f(x).c"

int main(){
    integral(x, -1.0, 4.0);
    integral(x_2, 0.0, 5.0);
    integral(x_3, 3.0, 10.0);
    integral(sinx, -1.0, 1.0);
    integral(cosx, -1.0, 1.0);
    integral(e_x, -5.0, 2.0);
    return 0;
}