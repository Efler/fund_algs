#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void arg_to_int(int* p_num, char* symbol){
    char* symbol_1 = symbol;
    int zn = 1;
    if(*symbol == '0'){//----------------------------------------------************
        printf("Invalid Input: unexpected number\n");
        exit(0);
    }
    while(*symbol){
        if((((*symbol - '0') < 0) || ((*symbol - '0') > 9))&&(*symbol!='-')){
            printf("Invalid Input: unexpected number\n");
            exit(0);
        }
        if(*symbol=='-'){
            if(symbol != symbol_1){
                printf("Invalid Input: unexpected number\n");
                exit(0);
            }
            zn = -1;
            symbol++;
        }else{
            if(zn == 1){
                if((*p_num > INT_MAX/10)){
                    printf("Invalid Number: overflow\n");
                    exit(0);
                }
                if(((*p_num * 10)/2 + (*symbol - '0')/2) > INT_MAX/2){
                    printf("Invalid Number: overflow\n");
                    exit(0);
                }
                *p_num = *p_num * 10 + (*symbol++ - '0');
            }else{
                if((*p_num > (INT_MAX/10))){
                    printf("Invalid Number: overflow\n");
                    exit(0);
                }
                if(((*p_num * 10)/2 + (*symbol - '0')/2) > (INT_MAX/2)){
                    printf("Invalid Number: overflow\n");
                    exit(0);
                }
                *p_num = *p_num * 10 + (*symbol++ - '0');
            }
        }
    }
    if(zn==-1) *p_num *= zn;
}


void input_validation(int argc, char *argv[]){

    if(argv[1][1] == 'q'){
//--------------------------------------!!!
    }
    else if(argv[1][1] == 'm'){
        if(argc != 4){
            printf("Invalid Input (flag 'm'): wrong number of arguments\n");
            exit(0);
        }
        if((strlen(argv[2])==1)&&(argv[2][0]=='0')){
            printf("Invalid Input (flag 'm'): at least one of the numbers is 0\n");
            exit(0);
        }
        if((strlen(argv[3])==1)&&(argv[3][0]=='0')){
            printf("Invalid Input (flag 'm'): at least one of the numbers is 0\n");
            exit(0);
        }

        int num1 = 0, num2 = 0;//-----------------------------------------------******
        arg_to_int(&num1, argv[2]);
        arg_to_int(&num2, argv[3]);

        printf("%d %d",num1,num2);

    }
    else if(argv[1][1] == 't'){
//--------------------------------------------------!!!
    }
}


int main(int argc, char *argv[]){
    if(argc == 1){
        printf("Invalid Input: no arguments\n");
        exit(0);
    }
    if(argv[1][0] == '-' || argv[1][0] == '/'){
        if(strlen(argv[1]) != 2){
            printf("Invalid Input: unexpected flag\n");
            exit(0);
        }
        if(argv[1][1] == 'q'){

        }
        else if(argv[1][1] == 'm'){
            input_validation(argc,argv);
        }
        else if(argv[1][1] == 't'){

        }
        else{
            printf("Invalid Flag: unexpected flag '%c'\n", argv[1][1]);
            exit(0);
        }
    }else{
        printf("Invalid Input: symbol '-' or '/' before flag not found\n");
        exit(0);
    }
}