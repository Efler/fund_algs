#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define EPSILON 1e-7

enum{
    DONE = 0,
    MEMORY = 1,
    SYNTAX = 2,
    COUNT = 3,
    OPENFILE = 4
};

typedef struct employee{
    int id;
    char* name;
    char* surname;
    double income;
}employee;

typedef struct node{
    struct node* prev;
    struct node* next;
    struct node* deep;
    double key;
    employee person;
    int rank;
}node;


int free_list(employee* list, int counter_of_persons){
    printf("\n\n [ Clearing list... ]\n");
    for(counter_of_persons; counter_of_persons > 0; counter_of_persons--){
        if((list + counter_of_persons - 1)->name != NULL) free((list + counter_of_persons - 1)->name);
        if((list + counter_of_persons - 1)->surname != NULL) free((list + counter_of_persons - 1)->surname);
    }
    free(list);
    return DONE;
}

int reallocation(employee** list, int* k){
    *k *= 2;
    employee* p = (employee*)realloc(*list, *k * sizeof(employee));
    if(!p){
        return MEMORY;
    }
    *list = p;
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

int read_double(FILE* fin, double* num){
    if(feof(fin)) return COUNT;
    char c;
    int k = 4;
    char* str = (char*)malloc(k*sizeof(char));
    if(!str) return MEMORY;
    char* p_str = str;
    c = (char)fgetc(fin);
    while(c != '\n' && c != EOF){
        if(c != '.'){
            if(!isdigit(c)){
                free(str);
                return SYNTAX;
            }
        }
        if(p_str - str == (k-1)){
            k *= 2;
            char* p = realloc(str, k*sizeof(char));
            if(!p){
                free(str);
                return MEMORY;
            }
            str = p;
            p_str = str + (k/2-1);
        }
        *p_str++ = c;
        c = (char)fgetc(fin);
    }
    *p_str = 0;
    *num = atof(str);
    free(str);
    return DONE;
}

employee* read_file(char *argv[], int* read_error, int* counter_of_persons){
    int k = 4;
    int error = 0;
    employee* list = (employee*)malloc(k * sizeof(employee));
    if(!list){
        *read_error = MEMORY;
        return NULL;
    }

    FILE* fin = fopen(argv[1], "r");
    if(!fin){
        free(list);
        *read_error = OPENFILE;
        return NULL;
    }

    while(!feof(fin)){
        if(*counter_of_persons == k){
            if(reallocation(&list, &k)){
                *read_error = MEMORY;
                free_list(list, *counter_of_persons);
                fclose(fin);
                return NULL;
            }
        }
        error = read_int(fin, &((*(list + *counter_of_persons)).id));
        if(error){
            if(error == COUNT && *counter_of_persons == 0) *read_error = -1;
            else *read_error = error;
            free_list(list, *counter_of_persons);
            fclose(fin);
            return NULL;
        }
        error = read_str(fin, &((*(list + *counter_of_persons)).name));
        if(error){
            *read_error = error;
            free_list(list, *counter_of_persons);
            fclose(fin);
            return NULL;
        }
        error = read_str(fin, &((*(list + *counter_of_persons)).surname));
        if(error){
            *read_error = error;
            free_list(list, *counter_of_persons);
            fclose(fin);
            return NULL;
        }
        error = read_double(fin, &((*(list + *counter_of_persons)).income));
        if(error){
            *read_error = error;
            free_list(list, *counter_of_persons);
            fclose(fin);
            return NULL;
        }
        (*counter_of_persons)++;
    }
    fclose(fin);
    return list;
}

int print_all_students(employee* list, int counter_of_persons){
    printf("\n");
    if(counter_of_persons == 0){
        printf("List if empty!\n");
        return DONE;
    }
    for(int i = 0; i < counter_of_persons; i++){
        printf("%d %s %s ", list[i].id, list[i].name, list[i].surname);
        printf("%f\n", list[i].income);
    }
    return DONE;
}

node* create_heap(employee person){
    node* core = (node*)malloc(sizeof(node));
    if(!core) return NULL;
    core->next = NULL;
    core->prev = NULL;
    core->deep = NULL;
    core->key = person.income;
    core->person = person;
    core->rank = 0;
    return core;
}

node* add_to_heap(node* core, employee person){
    node* new = (node*)malloc(sizeof(node));
    if(!new){
        node* tmp = core->next;
        while(tmp != core){
            node* tmp2 = tmp->next;
            free(tmp);
            tmp = tmp2;
        }
        free(core);
        return NULL;
    }
    if(core->next == NULL){
        new->next = core;
        new->prev = core;
        new->deep = NULL;
        new->key = person.income;
        new->person = person;
        new->rank = 0;
        core->next = new;
        core->prev = new;
    }else{
        new->next = core->next;
        core->next->prev = new;
        new->prev = core;
        core->next = new;
        new->deep = NULL;
        new->key = person.income;
        new->person = person;
        new->rank = 0;
    }
    if(new->key - core->key < EPSILON){
        return new;
    }else{
        return core;
    }
}

int main(int argc, char *argv[]){

    char error_memory[] = "\nMemory allocation error\n";
    char error_syntax[] = "\nWrong syntax\n";
    char error_count[] = "\nWrong amount of line properties\n";
    char error_file[] = "\nCould not open a file\n";
    char* errors[] = {error_memory, error_syntax, error_count, error_file};

    if(argc != 3){
        printf("\nWrong number of arguments\n");
        return 0;
    }

    employee* list;
    int counter_of_persons = 0;
    int read_error = 0;

    printf("\n[ Reading file... ]\n\n");
    list = read_file(argv, &read_error, &counter_of_persons);
    if(read_error){
        if(read_error == -1){
            printf("\nList if empty!\n");
            return DONE;
        }
        else{
            printf("%s", errors[read_error-1]);
            return read_error;
        }
    }
    printf("\n[ Read_file ---> Done! ]\n\n");
    print_all_students(list, counter_of_persons);

    int heap_count = 0;
    node* core;
    for(int i = 0; i < counter_of_persons; i++){
        if(!heap_count){
            core = create_heap(list[i]);
            if(!core){
                free_list(list, counter_of_persons);
                printf("%s", errors[MEMORY-1]);
                return MEMORY;
            }
            heap_count++;
            continue;
        }else{
            core = add_to_heap(core, list[i]);
            if(!core){
                free_list(list, counter_of_persons);
                printf("%s", errors[MEMORY-1]);
                return MEMORY;
            }
            heap_count++;
        }
    }


}