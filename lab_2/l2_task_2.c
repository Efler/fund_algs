#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char* dynamic_string(int* k){
    char* buff = (char*)malloc((*k) * sizeof(char));
    if(!buff){
        return 0;
    }
    return buff;
}


int length_str(char str[]){
    int count = 0;
    int k = 0;
    while(str[k] != '\0'){
        count++;
        k++;
    }
    return count;
}


char* reverse_str(char str[]){
    int count = length_str(str);
    int k = count + 1;
    char* rev_str = dynamic_string(&k);
    if(!rev_str){
        printf("Malloc Error\n");
        free(rev_str);
        return 0;
    }
    char* p_rev_str = rev_str;
    while(count > 0){
        *p_rev_str++ = str[count---1];
    }
    *p_rev_str = 0;
    return rev_str;
}


char* upper_odd(char str[]){
    int count = length_str(str);
    while(count > 0){
        if((count-1) & 1)
            str[count-1] = toupper(str[count-1]);
        count--;
    }
    return str;
}


char* digit_alpha_els(char str[]){
    int count = length_str(str);
    char* digit = dynamic_string(&count);
    char* alpha = dynamic_string(&count);
    char* els = dynamic_string(&count);
    char* res = (char*)malloc((count+1) * sizeof(char));
    if (!digit || !alpha || !els || !res){
        printf("Malloc Error\n");
        free(digit);
        free(alpha);
        free(els);
        free(res);
        return 0;
    }
    char* p_digit = digit;
    char* p_alpha = alpha;
    char* p_els = els;
    char* p_res = res;
    for(int i = 0; i < count; i++){
        if(isdigit(str[i])){
            *p_digit++ = str[i];
        }
        else if(isalpha(str[i])){
            *p_alpha++ = str[i];
        }
        else{
            *p_els++ = str[i];
        }
    }
    *p_digit = 0;
    *p_alpha = 0;
    *p_els = 0;
    p_digit = digit;
    p_alpha = alpha;
    p_els = els;
    while(*p_digit != 0){
        *p_res++ = *p_digit++;
    }
    while(*p_alpha != 0){
        *p_res++ = *p_alpha++;
    }
    while(*p_els != 0){
        *p_res++ = *p_els++;
    }
    *p_res = 0;
    free(digit);
    free(alpha);
    free(els);
    return res;
}


char* str_cat(char str[], char str2[]){
    int count = length_str(str) + length_str(str2) + 1;
    char* res = dynamic_string(&count);
    if(!res){
        printf("Malloc Error\n");
        free(res);
        return 0;
    }
    char* p_res = res;
    while(*str){
        *p_res++ = *str++;
    }
    while(*str2){
        *p_res++ = *str2++;
    }
    *p_res = 0;
    return res;
}


int main(int argc, char *argv[]){
    if(argc == 1){
        printf("Input Error: wrong number of arguments\n");
        return 0;
    }
    if(strlen(argv[2]) != 2){
        printf("Input Error: invalid flag\n");
        return 0;
    }
    if(argv[2][0] != '-'){
        printf("Input Error: invalid flag\n");
        return 0;
    }

    if(argv[2][1] == 'l'){
        if(argc != 3){
            printf("Input Error: wrong number of arguments\n");
            return 0;
        }
        int count = length_str(argv[1]);
        printf("Length of the string is %u symbols\n", count);
        return 0;
    }
    else if(argv[2][1] == 'r'){
        if(argc != 3){
            printf("Input Error: wrong number of arguments\n");
            return 0;
        }
        char* rev_str = reverse_str(argv[1]);
        printf("Reversed string: %s\n", rev_str);
        free(rev_str);
        return 0;
    }
    else if(argv[2][1] == 'u'){
        if(argc != 3){
            printf("Input Error: wrong number of arguments\n");
            return 0;
        }
        char* str = upper_odd(argv[1]);
        printf("New string: %s\n", str);
        return 0;
    }
    else if(argv[2][1] == 'n'){
        if(argc != 3){
            printf("Input Error: wrong number of arguments\n");
            return 0;
        }
        char* res = digit_alpha_els(argv[1]);
        printf("New string: %s\n", res);
        free(res);
        return 0;
    }
    else if(argv[2][1] == 'c'){
        if(argc != 4){
            printf("Input Error: wrong number of arguments\n");
            return 0;
        }
        char* res = str_cat(argv[1], argv[3]);
        printf("New string: %s\n", res);
        free(res);
        return 0;
    }
    else{
        printf("Input Error: invalid flag\n");
        return 0;
    }
}