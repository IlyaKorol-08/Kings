#include "func_integral.c"
#include "f(x).c"

int main(){
    printf("ТЕСТ. Вычисление определенного интеграла.\n");
    printf("%lf\n",integral(x, -1.0, 4.0));
    printf("%lf\n",integral(x_2, 0.0, 5.0));
    printf("%lf\n",integral(x_3, 3.0, 10.0));
    printf("%lf\n",integral(sinx, -1.0, 1.0));
    printf("%lf\n",integral(cosx, -1.0, 1.0));
    printf("%lf\n",integral(e_x, -5.0, 2.0));
    return 0;
}