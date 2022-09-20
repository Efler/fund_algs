#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


unsigned flag_f(unsigned number){
    if(number == 0 || number == 1){
        return 1;
    }
    if(number > 1 && flag_f(number-1) > 1 && number > UINT_MAX/flag_f(number-1)){
        printf("Flag 'f' Error: overflow\n");
        exit(0);
    }
    return number * flag_f(number-1);
}


void flag_a(unsigned number){
    if((number > UINT_MAX/(number-1))){
        printf("Flag 'a' Error: overflow\n");
        exit(0);
    }
    printf("Sum of numbers from 1 to %u is %u\n", number, number*(number-1)/2+(number));
    exit(0);
}


unsigned digits_kol(unsigned number){
    if(number != 0){
        return 1 + digits_kol(number/10);
    }
    else{
        return 0;
    }
}


void flag_s(unsigned number,unsigned digits_kol){
    unsigned tmp = pow(10, digits_kol);
    while(tmp > 0){
        number = number % tmp;
        tmp = tmp/10;
        if(tmp == 1){
            printf("%u\n", number/tmp);
            exit(0);
        }
        printf("%u ", number/tmp);
    }
}


void flag_h(unsigned number, unsigned kolvo_krat){
    if (kolvo_krat > 1){
        flag_h(number, kolvo_krat - 1);
    }
    printf("%u ", number * (kolvo_krat));
}


void flag_p(unsigned number){
    for(unsigned i=2; i<=(number/2); i++){
        if((number % i) == 0){
            printf("Number %u is composite\n", number);
            exit(0);
        }
    }
    printf("Number %u is prime\n", number);
    exit(0);
}


void flag_e(unsigned number){
    if(number>10){
        printf("Input Error: the number is bigger than 10 (flag e)\n");
        exit(0);
    }
    for(unsigned i = 1; i <= 10; i++){
        printf("%u: ", i);
        for(unsigned k = 1; k <= number; k++){
            if((i==10)&&(k==10)){
                printf("%lld ", (long long)pow(i,k));
            }else {
                printf("%u ", (unsigned)pow(i,k));
            }
        }
        printf("\n");
    }
    exit(0);
}


void input_validation(int argc, char *argv[],unsigned *number){
    if(argc == 1){
        printf("Invalid Input: no arguments\n");
        exit(0);
    }
    if(argc != 3){
        printf("Invalid Input: wrong number of arguments\n");
        exit(0);
    }
    if(strlen(argv[2]) != 2){
        printf("Invalid Input: unexpected flag\n");
        exit(0);
    }
    if((argv[1][0]=='0')&&(strlen(argv[1])!=1)){
        printf("Invalid Input: unexpected number\n");
        exit(0);
    }
    char* symbol = argv[1];
    while(*symbol){
        if (((*symbol - '0') < 0) || ((*symbol - '0') > 9)) {
            printf("Invalid Input: unexpected number\n");
            exit(0);
        }
        if((*number > UINT_MAX/10)){
            printf("Invalid Number: overflow\n");
            exit(0);
        }
        if(((*number * 10)/2 + (*symbol - '0')/2) > UINT_MAX/2){
            printf("Invalid Number: overflow\n");
            exit(0);
        }
        *number = *number * 10 + (*symbol++ - '0');
    }
}


int main(int argc, char *argv[]){
    unsigned number = 0;
    input_validation(argc, argv, &number);
    if(argv[2][0] == '-' || argv[2][0] == '/'){
        if(argv[2][1] == 'h'){
            if(100/number == 0){
                printf("No multiples of %u within 100!\n", number);
                exit(0);
            }
            printf("Multiples of %u within 100: ", number);
            flag_h(number, 100/number);
            exit(0);
        }
        else if(argv[2][1] == 'p'){
            flag_p(number);
        }
        else if(argv[2][1] == 's'){
            flag_s(number,digits_kol(number));
        }
        else if(argv[2][1] == 'e'){
            flag_e(number);
        }
        else if(argv[2][1] == 'a'){
            flag_a(number);
        }
        else if(argv[2][1] == 'f'){
            printf("Factorial of %u: %u\n", number, flag_f(number));
            exit(0);
        }
        else{
            printf("Invalid Flag: unexpected flag '%c'\n", argv[2][1]);
            exit(0);
        }
    }
    else{
        printf("Invalid Input: symbol '-' or '/' before flag not found\n");
        exit(0);
    }
}