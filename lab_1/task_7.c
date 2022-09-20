#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){

    srand(time(NULL));

    printf("Enter a size of an array:");
    char str[12];
    unsigned size = 0;
    fgets(str, 12, stdin);
    fflush(stdin);
    printf("\n");
    if((strlen(str) == 11)&&(str[10] != '\n')){
        printf("Invalid Input: overflow\n");
        exit(0);
    }
    char *p_str = str;
    while((*p_str != '\n')&&(*p_str)){
        if (((*p_str - '0') < 0) || ((*p_str - '0') > 9)) {
            printf("Invalid Input: unexpected size\n");
            exit(0);
        }
        if((size > UINT_MAX/10)){
            printf("Invalid Number: overflow\n");
            exit(0);
        }
        if(((size * 10)/2 + (*p_str - '0')/2) > UINT_MAX/2){
            printf("Invalid Number: overflow\n");
            exit(0);
        }
        size = size * 10 + (*p_str++ - '0');
    }
    if(size == 0){
        printf("Invalid Input: size is 0\n");
        exit(0);
    }

    int* array = (int*)malloc(size * sizeof(int));
    if(!array){
        printf("Allocation Error\n");
        free(array);
        exit(0);
    }
    printf("Randomly generated array:\n");
    for(unsigned i = 0; i < size; i++){
        array[i] = rand()%(20001) - 10000;
        printf("%d ", array[i]);
    }
    printf("\n\n");

    unsigned max = 0, min = 0;
    for(unsigned i = 0; i < size; i++){
        if(array[i] > array[max]) max = i;
        if(array[i] < array[min]) min = i;
    }
    printf("Max element: %d\nMin element: %d\n\n", array[max], array[min]);

    int tmp = array[max];
    array[max] = array[min];
    array[min] = tmp;
    printf("Edited array:\n");
    for(unsigned i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    free(array);
    exit(0);

}