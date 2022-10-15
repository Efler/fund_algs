#include <stdio.h>
#include <math.h>
#define EPSILON 1e-7

double f(double x) {
    return x - 4 + 5 * (cos(x));
}

double dihotomia(double a, double b, int accur){
    if((b-a)<EPSILON){
        double tmp = a;
        a = b;
        b = tmp;
    }
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
    printf("\nX: %lf\n", dihotomia((double)1.0, (double)5.0, 10));
}