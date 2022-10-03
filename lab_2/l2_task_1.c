#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


int re_all(char** buff, char** p_buff, int* k){
    *k *= 2;
    char* p = (char*)realloc(*buff, (*k)*sizeof(char));
    if(p != NULL){
        *buff = p;
        *p_buff = p + ((*k)/2);
        return 0;
    }else{
        return 1;
    }
}



char* dynamic_string(int* k){
    char* buff = (char*)malloc((*k) * sizeof(char));
    return buff;
}


int main(){
    int k = 1;
    int checker = 0;
    char c;
    srand(time(NULL));

    printf("Enter length of array A:\n");
    char* buff = dynamic_string(&k);
    if(buff == 0){
        printf("Malloc Error\n");
        free(buff);
        return 0;
    }
    char* p_buff = buff + 1;
    while(scanf("%c", &c)){
        if(c == '\n') break;
        if(!isdigit(c)) checker++;
        if ((p_buff - buff) == k) {
            if (re_all(&buff, &p_buff, &k)) {
                printf("Realloc Error\n");
                free(buff);
                return 0;
            }
        }
        *(p_buff-1) = c;
        p_buff++;
    }
    *(p_buff-1) = 0;
    k = 1;
    if(checker){
        printf("\nInvalid number\n");
        free(buff);
        return 0;
    }
    const unsigned lenA = atoi(buff);
    free(buff);
    if(lenA == 0){
        printf("\nInvalid number\n");;
        return 0;
    }


    printf("Enter length of array B:\n");
    buff = dynamic_string(&k);
    if(buff == 0){
        printf("Malloc Error\n");
        free(buff);
        return 0;
    }
    p_buff = buff + 1;
    while(scanf("%c", &c)){
        if(c == '\n') break;
        if(!isdigit(c)) checker++;
        if ((p_buff - buff) == k) {
            if (re_all(&buff, &p_buff, &k)) {
                printf("Realloc Error\n");
                free(buff);
                return 0;
            }
        }
        *(p_buff-1) = c;
        p_buff++;
    }
    *(p_buff-1) = 0;
    k = 1;
    if(checker){
        printf("\nInvalid number\n");
        free(buff);
        return 0;
    }
    const unsigned lenB = atoi(buff);
    free(buff);
    if(lenB == 0){
        printf("\nInvalid number\n");;
        return 0;
    }


    int arrA[lenA];
    int arrB[lenB];
    int arrC[lenA];
    printf("\nArray A:\n");
    for(int i = 0; i < lenA; i++){
        arrA[i] = rand()%(21) - 10;
        printf("%d ", arrA[i]);
    }
    printf("\nArray B:\n");
    for(int i = 0; i < lenB; i++){
        arrB[i] = rand()%(21) - 10;
        printf("%d ", arrB[i]);
    }
    printf("\nArray C:\n");
    if(lenA > lenB){
        int i = 0;
        for(; i < lenB; i++){
            arrC[i] = arrA[i] + arrB[i];
            printf("%d ", arrC[i]);
        }
        for(; i < lenA; i++){
            arrC[i] = arrA[i] + arrB[lenB-1];
            printf("%d ", arrC[i]);
        }
    }
    else{
        for(int i = 0; i < lenA; i++){
            arrC[i] = arrA[i] + arrB[i];
            printf("%d ", arrC[i]);
        }
    }
    printf("\n");
}