#include <stdio.h>
#include <math.h>

int main() 
{
    double a, b, c;
    double d, x1, x2;
    
    printf("Решение квадратного уравнения ax^2 + bx + c = 0\n");
    printf("Введите a: ");
    scanf("%lf", &a);
    printf("Введите b: ");
    scanf("%lf", &b);
    printf("Введите c: ");
    scanf("%lf", &c);

    if (a == 0) 
    {
        if (b == 0) 
        {
            if (c == 0)
            {
                printf("Бесконечное множество решений\n");
            }
            else
            {
                printf("Нет решений\n");
            }
        }
        else 
        {
            x1 = -c / b;
            printf("Линейное уравнение, корень: %lf\n", x1);
        }
        return 0;
    }
    
    d = b*b - 4*a*c;
    
    if (d < 0) 
    {
        printf("Действительных корней нет\n");
    }
    else if (d == 0) 
    {
        x1 = -b/(2*a);
        printf("Один корень: x = %lf\n", x1);
    }
    else 
    {
        x1 = (-b + sqrt(d))/(2*a);
        x2 = (-b - sqrt(d))/(2*a);
        printf("Два корня:\n");
        printf("x1 = %lf\n", x1);
        printf("x2 = %lf\n", x2);
    }
    return 0;
}