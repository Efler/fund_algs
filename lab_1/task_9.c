#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum{
    DONE = 0,
    MEMORY = 1,
    SYNTAX = 2
};


int traverse_num(char** str, int num, int base){
    int k = 4;
    *str = (char*)malloc(k * sizeof(char));
    if(!*str) return MEMORY;
    int index = 0;
    int ost = base;
    while(num){
        if(index == k-1){
            k *= 2;
            char* p = (char*)realloc(*str, k * sizeof(char));
            if(!p){
                free(*str);
                return MEMORY;
            }
            *str = p;
        }
        ost = num % base;
        num /= base;
        if(ost > 9){
            (*str)[index++] = (char)(ost + 55);
        }else{
            (*str)[index++] = (char)(ost + 48);
        }
    }
    if(index == k-1){
        k *= 2;
        char* p = (char*)realloc(*str, k * sizeof(char));
        if(!p){
            free(*str);
            return MEMORY;
        }
        *str = p;
    }
    (*str)[index] = 0;
    char* tmp = (char*)malloc((strlen(*str) + 1) * sizeof(char));
    if(!tmp) return MEMORY;
    index = strlen(*str) - 1;
    for(int i = 0; i < strlen(*str); i++){
        tmp[i] = (*str)[index--];
    }
    tmp[strlen(*str)] = 0;
    free(*str);
    *str = tmp;
    return DONE;
}

int translate(char* str, int base){
    int num = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++){
        if(str[i] <= '9' && str[i] >= '0'){
            num = num * base + str[i] - 48;

        }else if(str[i] >= 'a' && str[i] <= 'z'){
            num = num * base + str[i] - 87;
        }else if(str[i] >= 'A' && str[i] <= 'Z'){
            num = num * base + str[i] - 55;
        }
    }
    return num;
}

int max_degree(char* str){
    int maxd = 0, flg = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] <= '9' && str[i] >= '0' && flg == 0){
            if(str[i]-48 > maxd){
                maxd = str[i] - 48;
            }
        }else if(str[i] >= 'a' && str[i] <= 'z'){
            if(maxd < str[i] - 87){
                maxd = str[i] - 87;
                flg++;
            }
        }else if(str[i] >= 'A' && str[i] <= 'Z'){
            if (maxd < str[i] - 55){
                maxd = str[i] - 55;
                flg++;
            }
        }else{
            return 0;
        }
    }
    return maxd + 1;
}

int input_str(char** str){
    fflush(stdin);
    char c;
    int k = 2;
    *str = (char*)malloc(k*sizeof(char));
    char* p_str = *str;
    if(!*str) return MEMORY;
    while((c = getchar()) != '\n'){
        if(p_str - *str == k-1){
            k*=2;
            char* p = (char*)realloc(*str, k*sizeof(char));
            if(!p){
                free(*str);
                return MEMORY;
            }else{
                *str = p;
                p_str = *str + (k/2)-1;
            }
        }
        if(!isdigit(c) && (toupper(c) < 'A' || toupper(c) > 'Z') && c != '-'){
            free(*str);
            return SYNTAX;
        }
        if(c == '-') continue;
        *p_str++ = c;
    }
    *p_str = 0;
    fflush(stdin);
    return DONE;
}

int main(int argc, char *argv[]){

        char error_memory[] = "\nMemory allocation error\n";
        char error_syntax[] = "\nWrong syntax\n";
        char* errors[] = {error_memory, error_syntax};

        int bases[] = {9, 18, 27, 36};

    if(argc != 1){
        printf("\nWrong count of arguments!\n");
        return DONE;
    }
    int base;
    printf("\nEnter the base of the system in range [2, 36]:\n");
    if (!(scanf("%d", &base)) || (base < 2 || base > 36)){
        printf("Wrong input!\n");
        return SYNTAX;
    }
    char* buff;
    int flag = 1;
    int num = 0;
    int max = 0;
    int error = DONE;
    while(flag){
        printf("\nEnter a number or a command 'Stop':\n");
        error = input_str(&buff);
        if(error){
            printf("%s", errors[error-1]);
            return error;
        }
        if(!strcmp(buff, "Stop")) flag = 0;
        else{
            if(max_degree(buff) > base){
                printf("\nWrong number in entered base\n");
                free(buff);
                return SYNTAX;
            }
            num = translate(buff, base);
            if (num > max) max = num;
            free(buff);
            buff = NULL;
        }
    }
    printf("\nMax number in base 10 = %d\n", max);
    for(int i = 0; i < 4; i++){
        if(!num){
            printf("\nMax number in base %d = %d\n", bases[i], 0);
            free(buff);
            buff = NULL;
        }
        else{
            error = traverse_num(&buff, max, bases[i]);
            if(error){
                printf("%s", errors[error-1]);
                free(buff);
                return error;
            }
            printf("\nMax number in base %d = %s\n", bases[i], buff);
            free(buff);
            buff = NULL;
        }
    }
    return DONE;
}