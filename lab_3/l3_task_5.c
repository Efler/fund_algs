#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


enum{
    DONE = 0,
    MEMORY = 1,
    SYNTAX = 2,
    COUNT = 3
};

typedef struct list{
    int id;
    char* name;
    char* surname;
    int course;
    char* group;
    int* marks;
}list;

int reallocation(list** students, int* k){
    *k *= 2;
    list* p = (list*)realloc(*students, *k * sizeof(list));
    if(!p){
        return MEMORY;
    }
    *students = p;
    return DONE;
}

int free_list(list* students, int counter_of_persons){
    for(counter_of_persons; counter_of_persons > 0; counter_of_persons--){
        if((students + counter_of_persons - 1)->name != NULL) free((students + counter_of_persons - 1)->name);
        if((students + counter_of_persons - 1)->surname != NULL) free((students + counter_of_persons - 1)->surname);
        if((students + counter_of_persons - 1)->group != NULL) free((students + counter_of_persons - 1)->group);
        if((students + counter_of_persons - 1)->marks != NULL) free((students + counter_of_persons - 1)->marks);
    }
    free(students);
    return DONE;
}

int read_str(FILE* fin, char** str){
    if(feof(fin)) return COUNT;
    char c;
    int k = 4;
    *str = (char*)malloc(k*sizeof(char));
    if(!*str) return MEMORY;
    char* p_str = *str;
    while((c = (char)fgetc(fin)) != ' '){
        if(c == EOF){
            free (*str);
            return COUNT;
        }
        if(!isalpha(c)){
            free (*str);
            return SYNTAX;
        }
        if(p_str - *str == (k-1)){
            k *= 2;
            char* p = realloc(*str, k*sizeof(char));
            if(!p){
                return 2;
            }
            *str = p;
            p_str = *str + (k/2-1);
        }
        *p_str++ = c;
    }
    *p_str = 0;
    return DONE;
}

int read_int(FILE* fin, int* num){
    if(feof(fin)) return COUNT;
    *num = 0;
    char c;
    while((c = (char)fgetc(fin)) != ' '){
        if(c == EOF) return COUNT;
        if(!isdigit(c)){
            return SYNTAX;
        }
        *num = *num * 10 + (c - '0');
    }
    return DONE;
}

int read_file(list** students, int* k, FILE* fin, int* counter_of_persons){
    int error = 0;
    while(!feof(fin)){
        error = read_str(fin, &((*(*students + *counter_of_persons)).name));
        if(error == MEMORY){
            return MEMORY;
        }else if(error == SYNTAX){
            return SYNTAX;
        }else if(error == COUNT){
            return COUNT;
        }
        error = read_str(fin, &((*(*students + *counter_of_persons)).surname));
        if(error == MEMORY){
            return MEMORY;
        }else if(error == SYNTAX){
            return SYNTAX;
        }else if(error == COUNT){
            return COUNT;
        }//-------------------------------------------------------- !!!
    }
    return DONE;
}

int main(int argc, char *argv[]){
    int counter_of_persons = 0;
    int comm_error;
    int k = 2;
    if(argc != 2){
        printf("Wrong number of arguments\n");
        return 0;
    }
    printf("\n[ Reading file... ]\n\n");
    FILE* fin = fopen(argv[1], "r");
    if(!fin){
        printf("Could not open a file\n");
        return 0;
    }
    list* students = (list*)malloc(k * sizeof(list));
    if(!students){
        printf("Memory allocation error\n");
        return 0;
    }
    comm_error = read_file(&students, &k, fin, &counter_of_persons);
    if(comm_error == MEMORY){
        printf("Memory allocation error\n");
        free_list(students, counter_of_persons);
        fclose(fin);
        return 0;
    }else if(comm_error == SYNTAX){
        printf("Wrong syntax\n");
        free_list(students, counter_of_persons);
        fclose(fin);
        return 0;
    }else if(comm_error == COUNT) {
        printf("Wrong amount of line properties\n");
        free_list(students, counter_of_persons);
        fclose(fin);
        return 0;
    }
    return 0;
}