#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define EPSILON 1e-7


double func_power(double num, int power){
    if(power == 0){
        return 1;
    }
    else if(power < 0){
        return func_power(num, power + 1) * (1.0 / num);
    }
    else{
        return func_power(num, power - 1) * num;
    }
}


double avg_geom(int count, ...){
    double res = 1.0;
    va_list l;
    va_start(l, count);
    for(int i = 0; i < count; i++){
        res *= va_arg(l, double);
    }
    va_end(l);
    if(!(count & 1) && (res < EPSILON)){
        return NAN;
    }
    if((count & 1) && (res < EPSILON)){
        return -pow(fabs(res), 1.0 / count);
    }
    else{
        return pow(res, 1.0 / count);
    }
}


int main(int argc, char *argv[]){
    int act;
    printf("Choose an action:\n1) Geometric mean\n2) Power\n");
    scanf("%d", &act);
    if (act == 1){
        double res = avg_geom(3, (double)-2.0, (double)8.0, (double)4.0);
        printf("%lf", res);
        return 0;
    }
    else if(act == 2){
        double num;
        int power;
        printf("Enter a number:\n");
        scanf("%lf", &num);
        printf("Enter a power:\n");
        scanf("%d", &power);
        printf("The result is: %lf", func_power(num, power));
        return 0;
    }
    else{
        printf("Unexpected action\n");
        return 0;
    }
}