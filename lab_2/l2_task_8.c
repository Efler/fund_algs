#include <stdio.h>
#include <math.h>

double f(double x) {
    return x -4 - 5 * (sin(x));
}

double dihotomia(double (*f)(double), double a, double b, int accur) {
    double res = 0.0;
    double epsilon = pow(10, -accur);
    do{
        res = (a + b) / 2.0;
        if(f(res) * f(a) < epsilon) b = res;
        else a = res;
    }
    while(fabs(a-b) >= epsilon);

    return res;
}

int main() {
    printf("\nX: %lf\n", dihotomia(f, (double)1.1, (double)3.5, 7));
}