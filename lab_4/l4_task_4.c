#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct arr{
    char name;
    int* value;
    int value_buff;
    int count_of_el;
}arr;

void clear_arrays_value(arr* arrays, int* checker){
    if(*checker != -1){
        for(int i = 0; i < *checker+1; i++){
            free(arrays[i].value);
        }
    }
    else{
        for(int i = 0; i < 26; i++){
            free(arrays[i].value);
        }
    }
    printf("AHAHAHAHAHHA\n");
}

int create_arrays(arr* arrays, int* checker){
    for(int i = 0; i < 26; i++){
        arrays[i].name = (char)(65 + i);
        arrays[i].value_buff = 4;
        arrays[i].count_of_el = 0;
        arrays[i].value = (int*)malloc(arrays[i].value_buff * sizeof(int));
        if(!arrays[i].value){
            *checker = i;
            return 1;
        }
    }
    return 0;
}

int find_array(arr* arrays, char Name){
    for(int i = 0; i < 26; i++){
        if(arrays[i].name == Name) return i;
    }
}

int load_args(FILE* fin, char** file, char* Name, int* k){
    char c;
    *Name = fgetc(fin);
    if(!isalpha(*Name)){
        return 1;
    }
    if(toupper(*Name) < 65 || toupper(*Name) > 90){
        return 1;
    }
    c = fgetc(fin);
    if(c != ','){
        return 2;
    }
    c = fgetc(fin);
    if(c != ' '){
        return 2;
    }
    char* p_file = *file;
    while(c = fgetc(fin)){
        if(c == '\n' || c == EOF){
            break;
        }
        if((p_file - *file) == *k){
            *k *= 2;
            char* p = (char*)realloc(*file, (*k)*sizeof(char));
            if(!p){
                free(*file);
                return 3;
            }else{
                *file = p;
                p_file = p + *k/2;
            }
        }
        *p_file++ = c;
    }
    if((p_file - *file) == *k){
        char* p = (char*)realloc(*file, (*k+1)*sizeof(char));
        if(!p){
            free(*file);
            return 3;
        }else{
            *file = p;
            p_file = p + *k;
        }
    }
    *p_file = 0;
    return 0;
}

int load(FILE* fin, char* comm, arr* arrays){
    char Name;
    int k = 6;
    char* file = (char*)malloc((k) * sizeof(char));
    int error = load_args(fin, &file, &Name, &k);
    if(error == 1){
        return 1;
    }else if(error == 2){
        return 2;
    }else if(error == 3){
        return 3;
    }
    FILE* file_load = fopen(file, "r");
    if(!file_load){
        free(file);
        return 4;
    }
    int index = find_array(arrays, Name);
    char c;
    char cp;
    int check_cp = 0;
    k = 4;
    int num;
    char* buff = (char*)malloc((k) * sizeof(char));
    if(!buff){
        fclose(file_load);
        free(file);
        return 3;
    }
    char* p_buff = buff;
    while(c = fgetc(file_load)){
        if(c == ' '){
            if(check_cp == 0){
                cp = c;
                check_cp = 1;
                continue;
            }else{
                if(cp == c){
                    cp = c;
                    continue;
                }else{
                    cp = c;
                    if((p_buff - buff) == k){
                        char* p = (char*)realloc(buff, (k+1)*sizeof(char));
                        if(!p){
                            fclose(file_load);
                            free(file);
                            free(buff);
                            return 3;
                        }else{
                            buff = p;
                            p_buff = p + k;
                        }
                    }
                    *p_buff = 0;
                    num = atoi(buff);
                    free(buff);
                    k = 4;
                    buff = (char*)malloc((k) * sizeof(char));
                    if(!buff){
                        fclose(file_load);
                        free(file);
                        return 3;
                    }
                    p_buff = buff;
                    if((arrays[index].value_buff - arrays[index].count_of_el) == 0){
                        arrays[index].value_buff *= 2;
                        int* p = (int*)realloc(arrays[index].value, arrays[index].value_buff * sizeof(int));
                        if(!p){
                            fclose(file_load);
                            free(file);
                            free(buff);
                            return 6;
                        }else{
                            arrays[index].value = p;
                        }
                    }
                    *(arrays[index].value + arrays[index].count_of_el) = num;
                    arrays[index].count_of_el++;
                }
            }
        }else if(c == EOF){
            if(check_cp == 0){
                break;
            }else{
                if(cp == ' '){
                    break;
                }else{
                    if((p_buff - buff) == k){
                        char* p = (char*)realloc(buff, (k+1)*sizeof(char));
                        if(!p){
                            fclose(file_load);
                            free(file);
                            free(buff);
                            return 3;
                        }else{
                            buff = p;
                            p_buff = p + k;
                        }
                    }
                    *p_buff = 0;
                    num = atoi(buff);
                    free(buff);
                    k = 4;
                    buff = (char*)malloc((k) * sizeof(char));
                    if(!buff){
                        fclose(file_load);
                        free(file);
                        return 3;
                    }
                    p_buff = buff;
                    if((arrays[index].value_buff - arrays[index].count_of_el) == 0){
                        arrays[index].value_buff *= 2;
                        int* p = (int*)realloc(arrays[index].value, arrays[index].value_buff * sizeof(int));
                        if(!p){
                            fclose(file_load);
                            free(file);
                            free(buff);
                            return 6;
                        }else{
                            arrays[index].value = p;
                        }
                    }
                    *(arrays[index].value + arrays[index].count_of_el) = num;
                    arrays[index].count_of_el++;
                }
                break;
            }
        }else if(!isdigit(c)){
                fclose(file_load);
                free(file);
                free(buff);
                return 5;
        }else{
            if(check_cp == 0){
                check_cp = 1;
                cp = c;
                if((p_buff - buff) == k){
                    k *= 2;
                    char* p = (char*)realloc(buff, (k)*sizeof(char));
                    if(!p){
                        fclose(file_load);
                        free(file);
                        free(buff);
                        return 3;
                    }else{
                        buff = p;
                        p_buff = p + k/2;
                    }
                }
                *p_buff++ = c;
            }else{
                cp = c;
                if((p_buff - buff) == k){
                    k *= 2;
                    char* p = (char*)realloc(buff, (k)*sizeof(char));
                    if(!p){
                        fclose(file_load);
                        free(file);
                        free(buff);
                        return 3;
                    }else{
                        buff = p;
                        p_buff = p + k/2;
                    }
                }
                *p_buff++ = c;
            }
        }
    }
    fclose(file_load);
    free(file);
    free(buff);
    return 0;
}

char* write_command(FILE* fin, int* error){
    int k = 8;
    char s = '-';
    char* buff = (char*)malloc((k) * sizeof(char));
    if(!buff){
        return 0;
    }
    char* p_buff = buff;
    while(s = fgetc(fin)){
        if(s == ' ' || s == '(' || s == EOF){
            if(s == EOF) *error = 1;
            break;
        }
        if((p_buff - buff) == k){
            k *= 2;
            char* p = (char*)realloc(buff, (k)*sizeof(char));
            if(!p){
                free(buff);
                return 0;
            }else{
                buff = p;
                p_buff = p + k/2;
            }
        }
        *p_buff++ = s;
    }
    if((p_buff - buff) == k){
        char* p = (char*)realloc(buff, (k+1)*sizeof(char));
        if(!p){
            free(buff);
            return 0;
        }else{
            buff = p;
            p_buff = p + k;
        }
    }
    *p_buff = 0;
    return buff;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Wrong number of arguments\n");
        return 0;
    }
    FILE* fin = fopen(argv[1], "r");
    if(!fin){
        printf("Could not open a file\n");
        return 0;
    }
    int error = 0;
    char* comm = write_command(fin, &error);
    if(!comm){
        printf("Memory Allocation Error: command\n");
        fclose(fin);
        return 0;
    }
    if(error == 1){
        printf("Wrong format of a command\n");
        free(comm);
        fclose(fin);
        return 0;
    }
    arr arrays[26];
    int checker = 0;
    if(create_arrays(arrays, &checker)){
        printf("Memory Allocation Error: arrays\n");
        clear_arrays_value(arrays, &checker);
        free(comm);
        fclose(fin);
        return 0;
    }
    if(!strcmp(comm, "Load")){
        int load_error = load(fin, comm, arrays);
        if(load_error == 1){
            printf("Wrong syntax of arguments: Load\n");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }else if(load_error == 2){
            printf("Wrong syntax of arguments: Load\n");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }else if(load_error == 3){
            printf("Memory Allocation Error: Load\n");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }else if(load_error == 4){
            printf("Could not open a file: Load\n");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }else if(load_error == 5){
            printf("Invalid numbers in file: Load\n");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }else if(load_error == 6) {
            printf("Memory Allocation Error: Load ---> arrays");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }
        for(int i = 0; i < arrays[5].count_of_el; i++){
            printf("%d\n", *(arrays[5].value + i));
        }
    }else if(!strcmp(comm, "Save")){

    }else if(!strcmp(comm, "Rand")){

    }else if(!strcmp(comm, "Concat")){

    }else if(!strcmp(comm, "Free")){

    }else if(!strcmp(comm, "Remove")){

    }else if(!strcmp(comm, "Copy")){

    }else if(!strcmp(comm, "Sort")){

    }else if(!strcmp(comm, "Shuffle")){

    }else if(!strcmp(comm, "Stats")){

    }else if(!strcmp(comm, "Print")){

    }else{
        printf("Wrong command\n");
    }
    checker = -1;
    clear_arrays_value(arrays, &checker);
    free(comm);
    fclose(fin);
    return 0;
}