double x(double x);
double x_2(double x);
double sinx(double x);
double cosx(double x);
double e_x(double x);

typedef double (*func)(double);
double integral(func f, double a, double b);
