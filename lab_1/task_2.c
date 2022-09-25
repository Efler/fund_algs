#include <stdio.h>
#include <string.h>
#include <math.h>
#define EPSILON 1e-5


int is_right_triangle(float a, float b, float c){
    float max = a;
    float min = a;
    float middle = 0;
    float arr[3] = {a,b,c};
    for(int i = 0; i < 3; i++){
        if(arr[i] > max) max = arr[i];
        if(arr[i] < min) min = arr[i];
    }
    for(int i = 0; i < 3; i++){
        if(arr[i] < max && arr[i] > min) middle = arr[i];
    }
    if(fabs(min*min + middle*middle - max*max) < EPSILON){
        return 1;
    }else{
        return 0;
    }
}


int valid_number(char *s){
    for(int i = 0; s[i] != '\0'; i++){
        if ((((s[i] - '0') < 0) || ((s[i] - '0') > 9)) && (s[i] != '.') && (s[i] != '-')) {
            return 1;
        }
    }
    return 0;
}


int is_multiple(int a, int b){
    if(a % b == 0){
        return 1;
    }else{
        return 0;
    }
}


int roots(float a, float b, float c, float* x1, float* x2){
    if(fabs(a) < EPSILON){
        return (-1);
    }
    float d = b*b - 4*a*c;
    if(d > EPSILON){
        *x1 = (b*(-1)+(sqrt(d)))/(2*a);
        *x2 = (b*(-1)-(sqrt(d)))/(2*a);
        return 2;
    }
    else if(fabs(d) < EPSILON) {
        *x1 = (-b)/(2*a);
        return 1;
    }else{
        return 0;
    }
}


float str_to_float(char *s, int* check_float) {
    int negative = 1, i = 0, findDot = 0;
    float result = 0, point = 1;

    if(s[0] == '-'){
        i++;
        negative = -1;
    }

    for(; s[i] != '\0'; i++){
        if(findDot){
            *check_float = 1;
            point = point / 10;
            result = result + (s[i] - '0') * point;
        }else{
            if(s[i] == '.'){
                findDot = 1;
            }else{
                result = result * 10 + (s[i] - '0');
            }
        }
    }
    return result * negative;
}



int main(int argc, char *argv[]){
    int checker;
    int check_float = 0;
    int count = 1;
    float x1, x2 = 0;

    if(argc == 1){
        printf("Invalid Input: no arguments\n");
        return 0;
    }
    if(strlen(argv[1]) != 2 || (argv[1][0] != '-' && argv[1][0] != '/')){
        printf("Invalid Input: unexpected flag\n");
        return 0;
    }
    for(int e = 3; e <= argc; e++){
        if(valid_number(argv[e-1])){
            printf("Invalid Input: unexpected number\n");
            return 0;
        }
    }
    if(argv[1][1] == 'q'){
        if(argc != 5){
            printf("Invalid Input: wrong number of arguments\n");
            return 0;
        }
        float arr[3] = {str_to_float(argv[2], &check_float),str_to_float(argv[3], &check_float),str_to_float(argv[4], &check_float)};

        for (int i = 0; i < 3; i++) {
            for (int j =0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if(i!=j && i!=k && j!=k){
                        checker = roots(arr[i],arr[j],arr[k], &x1, &x2);
                        if(checker == -1){
                            printf("%d) %fx^2 + %fx + %f:   invalid quadratic equation coefficient (a = 0)!\n", count, arr[i], arr[j], arr[k]);
                            count++;
                        }else if(checker == 0){
                            printf("%d) %fx^2 + %fx + %f:   no roots!\n", count, arr[i], arr[j], arr[k]);
                            count++;
                        }else if(checker == 1){
                            printf("%d) %fx^2 + %fx + %f:   x = %f\n", count, arr[i], arr[j], arr[k], x1);
                            count++;
                        }else if(checker == 2){
                            printf("%d) %fx^2 + %fx + %f:   x1 = %f; x2 = %f\n", count, arr[i], arr[j], arr[k], x1, x2);
                            count++;
                        }
                    }
                }
            }
        }
        return 0;
    }
    else if(argv[1][1] == 'm'){
        if(argc != 4){
            printf("Invalid Input: wrong number of arguments\n");
            return 0;
        }
        int a = str_to_float(argv[2], &check_float);
        int b = str_to_float(argv[3], &check_float);
        if(check_float){
            printf("Flag -m error: at least one number is not integer\n");
            return 0;
        }
        if(a == 0 || b == 0){
            printf("Flag -m error: at least one number is 0\n");
            return 0;
        }
        if(is_multiple(a,b)){
            printf("Yes, it is multiple\n");
            return 0;
        }else{
            printf("No, it is not multiple\n");
            return 0;
        }
    }else if(argv[1][1] == 't'){
        if(argc != 5){
            printf("Invalid Input: wrong number of arguments\n");
            return 0;
        }
        if(fabs(str_to_float(argv[2], &check_float)) < EPSILON || fabs(str_to_float(argv[3], &check_float)) < EPSILON || fabs(str_to_float(argv[4], &check_float)) < EPSILON){
            printf("Flag -t error: at least one number is 0\n");
            return 0;
        }else if(str_to_float(argv[2], &check_float) > EPSILON || str_to_float(argv[3], &check_float) > EPSILON || str_to_float(argv[4], &check_float) > EPSILON){
            if(is_right_triangle(str_to_float(argv[2], &check_float), str_to_float(argv[3], &check_float), str_to_float(argv[4], &check_float))){
                printf("Yes, it can be a right triangle\n");
                return 0;
            }else{
                printf("No, it can't be a right triangle\n");
                return 0;
            }
        }else{
            printf("No, it can't be a right triangle\n");
            return 0;
        }
    }else{
        printf("Invalid Input: unexpected flag\n");
        return 0;
    }
}