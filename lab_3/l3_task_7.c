#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define EPSILON 1e-7


typedef struct list{
    char* name;
    char* surname;
    char* patronymic;
    int day;
    int month;
    int year;
    int gender;
    double income;
    struct list* next;
}list;

int read_str(FILE* fin, char** str){
    if(feof(fin)) return 0;
    char c;
    int k = 4;
    *str = (char*)malloc(k*sizeof(char));
    if(!*str) return 2;
    char* p_str = *str;
    while((c = (char)fgetc(fin)) != ' '){
        if(c == EOF) return 0;
        if(!isalpha(c)){
            return 1;
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
    return 0;
}

int read_int(FILE* fin, int* num, int flag){
    if(feof(fin)) return 0;
    *num = 0;
    char c;
    if(flag == 1){
        while((c = (char)fgetc(fin)) != '.'){
            if(!isdigit(c)){
                return -1;
            }
            *num = *num * 10 + (c - '0');
        }
        if(*num < 1 || *num > 31){
            return 1;
        }
    }else if(flag == 2){
        while((c = (char)fgetc(fin)) != '.'){
            if(!isdigit(c)){
                return -1;
            }
            *num = *num * 10 + (c - '0');
        }
        if(*num < 1 || *num > 12){
            return 2;
        }
    }else if(flag == 3){
        while((c = (char)fgetc(fin)) != ' '){
            if(!isdigit(c)){
                return -1;
            }
            *num = *num * 10 + (c - '0');
        }
        if(*num < 2000){
            return 3;
        }
    }
    return 0;
}

int read_double(FILE* fin, double* num){
    if(feof(fin)) return 0;
    char c;
    int k = 4;
    char* str = (char*)malloc(k*sizeof(char));
    if(!str) return 2;
    char* p_str = str;
    c = (char)fgetc(fin);
    while(c != '\n' && c != EOF){
        if(c != '.'){
            if(!isdigit(c)){
                free(str);
                return 1;
            }
        }
        if(p_str - str == (k-1)){
            k *= 2;
            char* p = realloc(str, k*sizeof(char));
            if(!p){
                free(str);
                return 2;
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
    return 0;
}

int create_new(list** core) {
    list* tmp = (list*)malloc(sizeof(list));
    if(!tmp){
        return 1;
    }
    tmp->next = (*core);
    (*core) = tmp;
    return 0;
}

int add(list** core, int count){
    list* previous;
    list* new = *core;
    list* next;
    if(count > 2){
        if((new->year)*10000+(new->month*100)+(new->day) > (new->next->year)*10000+(new->next->month*100)+(new->next->day)){
            previous = new->next;
            next = previous->next;
            *core = previous;
        }else{
            return 0;
        }
        while((new->year)*10000+(new->month*100)+(new->day) > (next->year)*10000+(next->month*100)+(next->day)){
            if(next->next == NULL){
                break;
            }
            previous = previous->next;
            next = previous->next;
        }
        if(next->next == NULL){
            previous->next = next;
            next->next = new;
            new->next = NULL;
            return 0;
        }
        previous->next = new;
        new->next = next;
        return 0;
    }else if(count == 2){
        if((new->year)*10000+(new->month*100)+(new->day) > (new->next->year)*10000+(new->next->month*100)+(new->next->day)){
            new->next->next = new;
            new->next = NULL;
            return 0;
        }
    }else{
        return 0;
    }
    return 0;
}

void clear_list(list** core){
    list* tmp;
    while(1){
        tmp = *core;
        if(tmp->next == NULL){
            tmp->name = NULL;
            free(tmp->name);
            tmp->surname = NULL;
            free(tmp->surname);
            tmp->patronymic = NULL;
            free(tmp->patronymic);
            free(tmp);
            printf("\n[ List cleared (dynamic memory) ]\n\n");
            break;
        }
        *core = tmp->next;
        tmp->name = NULL;
        free(tmp->name);
        tmp->surname = NULL;
        free(tmp->surname);
        tmp->patronymic = NULL;
        free(tmp->patronymic);
        free(tmp);
    }
}

int check_date(int day, int month, int year){
    if(month < 8 && (!(month&1)) && day > 30) return 1;
    if(month >= 8 && (month & 1) && day > 30) return 1;
    if(month == 2 && (year % 4) && day > 28) return 1;
    if(month == 2 && (!(year % 4)) && day > 29) return 1;
    return 0;
}

int main(int argc, char *argv[]){
    int counter_of_persons = 0;
    int comm_error;
    char* gender = NULL;
    const char* male = "male";
    const char* female = "female";

    if(argc != 2){
        printf("Wrong number of arguments\n");
        return 0;
    }
    list* core = (list*)malloc(sizeof(list));
    if(!core){
        printf("Memory allocation error\n");
        return 0;
    }
    list* input;
    core->name = NULL;
    core->surname = NULL;
    core->patronymic = NULL;
    core->day = -1;
    core->month = -1;
    core->year = -1;
    core->gender = -1;
    core->income = -1.0;
    core->next = NULL;
    FILE* fin = fopen(argv[1], "r");
    if(!fin){
        printf("Could not open a file\n");
        free(core);
        return 0;
    }
    printf("\n[ Reading file... ]\n\n");
    while(!feof(fin)){
        if(counter_of_persons == 0) input = core;
        else{
            if(create_new(&core)){
                free(gender);
                clear_list(&core);
                fclose(fin);
                printf("Error -> create_new: memory allocation error\n");
            }
            input = core;
        }
        comm_error = read_str(fin, &input->name);
        if(comm_error == 1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_str: invalid symbols\n");
            return 0;
        }else if(comm_error == 2){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_str: memory allocation error\n");
            return 0;
        }
        comm_error = read_str(fin, &input->surname);
        if(comm_error == 1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_str: invalid symbols\n");
            return 0;
        }else if(comm_error == 2){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_str: memory allocation error\n");
            return 0;
        }
        comm_error = read_str(fin, &input->patronymic);
        if(comm_error == 1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_str: invalid symbols\n");
            return 0;
        }else if(comm_error == 2){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_str: memory allocation error\n");
            return 0;
        }
        comm_error = read_int(fin, &input->day, 1);
        if(comm_error == -1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_int: invalid symbols\n");
            return 0;
        }else if(comm_error == 1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error: invalid day\n");
            return 0;
        }
        comm_error = read_int(fin, &input->month, 2);
        if(comm_error == -1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_int: invalid symbols\n");
            return 0;
        }else if(comm_error == 2){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error: invalid month\n");
            return 0;
        }
        comm_error = read_int(fin, &input->year, 3);
        if(comm_error == -1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_int: invalid symbols\n");
            return 0;
        }else if(comm_error == 3){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error: invalid year\n");
            return 0;
        }
        if(check_date(input->day, input->month, input->year)){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error: invalid date of birth\n");
            return 0;
        }
        comm_error = read_str(fin, &gender);
        if(comm_error == 1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_str: invalid symbols\n");
            return 0;
        }else if(comm_error == 2){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_str: memory allocation error\n");
            return 0;
        }
        if(!strcmp(gender, male)) input->gender = 0;
        else if(!strcmp(gender, female)) input->gender = 1;
        else{
            if(!feof(fin)){
                free(gender);
                clear_list(&core);
                fclose(fin);
                printf("Error: invalid gender\n");
                return 0;
            }
        }
        comm_error = read_double(fin, &input->income);
        if(comm_error == 1){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_double: invalid symbols\n");
            return 0;
        }else if(comm_error == 2){
            free(gender);
            clear_list(&core);
            fclose(fin);
            printf("Error -> read_double: memory allocation error\n");
            return 0;
        }
        counter_of_persons++;
        add(&core, counter_of_persons);
    }
    fclose(fin);
    if(core->gender == -1){
        counter_of_persons = 0;
        printf("Warning: List is empty\n");
    }





    list* output = core;
    int n = 1;
    while(1){
        printf("%d) ", n++);
        printf("%s ", output->name);
        printf("%s ", output->surname);
        printf("%s ", output->patronymic);
        if(output->day < 10) printf("0%d.", output->day);
        else printf("%d.", output->day);
        if(output->month < 10) printf("0%d.", output->month);
        else printf("%d.", output->month);
        printf("%d ", output->year);
        if(output->gender) printf("female ");
        else printf("male ");
        printf("%f\n", output->income);
        if(output->next != NULL){
            output = output->next;
        }else{
            break;
        }

    }
    free(gender);
    clear_list(&core);
    return 0;
}