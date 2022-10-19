#include <stdio.h>
#include <math.h>
#include <stdarg.h>



typedef struct coord{
    int x;
    int y;
} coord;


double polinom(double x, int n, ...){
    double res = 0.0;
    va_list l;
    va_start(l, n);
    for(int i = 0; i < n + 1; i++){
        if (!i){
            res = va_arg(l, double) * x;
        }else if(i < n){
            res = (res + va_arg(l, double)) * x;
        }
        else{
            res += va_arg(l, double);
        }
    }
    va_end(l);
    return res;
}


int convex(int count, ...){
    int step = count / 2;
    if(!(count & 1) && count >= 6){
        coord vertices[step];
        va_list l;
        va_start(l, count);
        for (int i = 0; i < step; i++) {
            vertices[i].x = va_arg(l, int);
            vertices[i].y = va_arg(l, int);
        }
        va_end(l);
        int sign;
        for (int i = 0; i < step; i++){
            int current = i % step;
            int next = (i + 1) % step;
            int after_next = (i + 2) % step;
            int x1 = vertices[next].x - vertices[current].x;
            int y1 = vertices[next].y - vertices[current].y;
            int x2 = vertices[after_next].x - vertices[next].x;
            int y2 = vertices[after_next].y - vertices[next].y;
            int rotation = x1 * y2 - x2 * y1;
            if (!i){
                sign = (rotation <= 0);
            }
            else if(sign != (rotation <= 0)){
                return 0;
            }
        }
        return 1;
    }
    return -1;
}


int main(){
    printf("Counted Polynomial is %lf\n", polinom(2.5, 3, 2.0, 1.2, 4.0, 5.6));
    if(convex(12, 0, 0, 2, 1, 0, 4, 2, 5, 6, 3, 3, 0) < 0){
        printf("Unexpected data\n");
    }
    else if(convex(12, 0, 0, 2, 1, 0, 4, 2, 5, 6, 3, 3, 0) > 0){
        printf("Is the polygon is convex? ---> YES\n");
    }
    else{
        printf("Is the polygon is convex? ---> NO\n");
    }
}