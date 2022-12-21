#include <stdio.h>
#include <malloc.h>
#include <string.h>


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

char* make_path(char* old_path){
    char* path = (char*)malloc((strlen(old_path)+5)*sizeof(char));
    if(!path){
        return NULL;
    }
    int id = strlen(old_path)+2;
    strcpy(path, old_path);
    while(path[id] != '.'){
        id--;
    }
    path[id++] = '_';
    path[id++] = 'o';
    path[id++] = 'u';
    path[id++] = 't';
    path[id++] = '.';
    path[id++] = 't';
    path[id++] = 'x';
    path[id++] = 't';
    path[id] = 0;
    return path;
}

int main(int argc, char *argv[]){
    FILE* inpt = fopen(argv[1], "r");
    if(!inpt){
        printf("\nCould not open a file\n");
        return 0;
    }
    char* path = make_path(argv[1]);
    if(path == NULL){
        printf("\nMemory Allocation Error\n");
        fclose(inpt);
        return 0;
    }
    FILE* otp = fopen(path, "w");
    if(!otp){
        printf("\nCould not open a file\n");
        fclose(inpt);
        free(path);
        return 0;
    }
    char* str = NULL;
    char* str1 = NULL;
    int len = 4, count = 0;
    str = (char*)malloc(len * sizeof(char));
    if(str == NULL){
        printf("\nMemory Allocation Error\n");
        fclose(inpt);
        fclose(otp);
        free(path);
        return 0;
    }
    char symbol;
    int minus = 0;
    while(!feof(inpt)){
        symbol = fgetc(inpt);
        if(symbol == ' ' || symbol == '\n' || symbol == '\t' || symbol == EOF){
            if(count != 0){
                str[count] = 0;
                if(minus) fprintf(otp, "-%s ", str);
                else fprintf(otp, "%s ", str);
                if(max_degree(str) == 0){
                    printf("\nWrong data\n");
                    fclose(inpt);
                    fclose(otp);
                    free(str);
                    free(path);
                    return 0;
                }
                fprintf(otp, "%d ", max_degree(str));
                if(minus) fprintf(otp, "%d\n", -translate(str, max_degree(str)));
                else fprintf(otp, "%d\n", translate(str, max_degree(str)));
                minus = 0;
                count = 0;
                len = 4;
                free(str);
                str = (char*)malloc(len * sizeof(char));
                if(str == NULL){
                    printf("\nMemory Allocation Error\n");
                    fclose(inpt);
                    fclose(otp);
                    free(path);
                    return 0;
                }


            }
        }else{
            if(symbol == '-'){
                if(minus){
                    printf("\nWrong data!\n");
                    fclose(inpt);
                    fclose(otp);
                    free(str);
                    free(path);
                    return 0;
                }else if(count > 0){
                    printf("\nWrong data!!\n");
                    fclose(inpt);
                    fclose(otp);
                    free(str);
                    free(path);
                    return 0;
                }else{
                    minus += 1;
                    continue;
                }
            }
            str[count] = symbol;
            count++;
            if(count == len-1){
                len *= 2;
                str1 = (char*)realloc(str, len * sizeof(char));
                if(str1 == NULL){
                    printf("\nMemory Allocation Error\n");
                    fclose(inpt);
                    fclose(otp);
                    free(str);
                    free(path);
                    return 0;
                }else{
                    str = str1;
                }
            }
        }
    }
    free(str);
    printf("\nDone! (%s)\n", path);
    fclose(otp);
    fclose(inpt);
    free(path);
    return 0;
}