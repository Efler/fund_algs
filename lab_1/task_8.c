#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


char* dynamic_string(int* k){
    char* buff = (char*)malloc((*k) * sizeof(char));
    if(buff == NULL){
        return 0;
    }
    return buff;
}

int re_all(char** buff, char** p_buff, int* k){
    *k *= 2;
    char* p = (char*)realloc(*buff, (*k)*sizeof(char));
    if(p != NULL){
        *buff = p;
        *p_buff = p + ((*k)/2) + 1;
        return 0;
    }else{
        return 1;
    }
}

int str_to_int(char* buff){
    int num = 0;
    while(*buff != 0){
        num = num * 10 + (*buff++ - '0');
    }
    return num;
}

int main(int argc, char *argv[]){
    char c = 0, cp = 0;
    int action;
    char* buff;
    char* p_buff;
    int k = 4;
    int num;

    if(argc == 1){
        printf("Invalid Input: no arguments\n");
        return 0;
    }

    FILE* fin = fopen(argv[1], "r");
    if(!fin){
        printf("File Error: could not open file\n");
        return 0;
    }

    printf("--- Choose an action ---:\n1) numbers in odd positions\n2) even numbers\n\n8) exit\n");
    scanf("%d", &action);

    if(action == 1){
        buff = dynamic_string(&k);
        if(buff == 0){
            printf("Malloc Error\n");
            free(buff);
            fclose(fin);
            return 0;
        }
        p_buff = buff + 1;
        while(c != EOF){
            c = fgetc(fin);
            if(c == EOF){
                if ((p_buff - buff) == k+1) {
                    if (re_all(&buff, &p_buff, &k)) {
                        printf("Realloc Error\n");
                        free(buff);
                        fclose(fin);
                        return 0;
                    }
                }
                *(p_buff-1) = 0;
                num = str_to_int(buff);
                printf("%d\n", num);
                k = 16;
                free(buff);
            }
            else{
                if(c == ' ' || c == '\n' || c == '\t'){
                    if(cp != ' ' && cp != '\n' && cp != '\t'){
                        if ((p_buff - buff) == k+1) {
                            if (re_all(&buff, &p_buff, &k)) {
                                printf("Realloc Error\n");
                                free(buff);
                                fclose(fin);
                                return 0;
                            }
                        }
                        *(p_buff-1) = 0;
                        num = str_to_int(buff);
                        printf("%d ", num);
                        k = 16;
                        cp = c;
                        free(buff);
                        buff = dynamic_string(&k);
                        if(buff == 0){
                            printf("Malloc Error\n");
                            free(buff);
                            fclose(fin);
                            return 0;
                        }
                        p_buff = buff + 1;
                    }else cp = c;
                }
                else{
                    if(!isdigit(c)){
                        printf("Array Error: one of elements is not a number\n");
                        free(buff);
                        fclose(fin);
                        return 0;
                    }
                    if ((p_buff - buff) == k+1) {
                        if (re_all(&buff, &p_buff, &k)) {
                            printf("Realloc Error\n");
                            free(buff);
                            fclose(fin);
                            return 0;
                        }
                    }
                    *(p_buff-1) = c;
                    p_buff++;
                    cp = c;
                }
            }
        }
        fclose(fin);
        printf("Done!\n");
    }
    else if(action == 2){

    }
    else if(action == 8){
        printf("Closing program...\n");
        fclose(fin);
        return 0;
    }
    else{
        printf("Unexpected action\n");
        fclose(fin);
        return 0;
    }
}

//float?
//overflow?
//file?