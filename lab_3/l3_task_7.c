#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
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
    list* next = new->next;
    if(count > 2){
        if((((new->year)*10000)+((new->month)*100)+(new->day)) > (((next->year)*10000)+((next->month)*100)+(next->day))){
            previous = new->next;
            next = previous->next;
            *core = previous;
        }else{
            return 0;
        }
        while((((new->year)*10000)+((new->month)*100)+(new->day)) > (((next->year)*10000)+((next->month)*100)+(next->day))){
            if(next->next == NULL){
                previous->next = next;
                next->next = new;
                new->next = NULL;
                return 0;
            }
            previous = previous->next;
            next = previous->next;
        }
        previous->next = new;
        new->next = next;
        return 0;
    }else if(count == 2){
        if((((new->year)*10000)+((new->month)*100)+(new->day)) > (((next->year)*10000)+((next->month)*100)+(next->day))){
            *core = next;
            next->next = new;
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
            free(tmp->name);
            free(tmp->surname);
            free(tmp->patronymic);
            free(tmp);
            printf("\n[ List cleared (dynamic memory) ]\n\n");
            break;
        }
        *core = tmp->next;
        free(tmp->name);
        free(tmp->surname);
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

int print_list(list* core){
    printf("\n");
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
            printf("\n");
            break;
        }
    }
    return 0;
}

int str_valid(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(!isalpha(str[i])){
            free(str);
            return 1;
        }
    }
    return 0;
}

int int_valid(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i])){
            free(str);
            return 1;
        }
    }
    return 0;
}

int d_valid(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i]) && str[i] != '.'){
            free(str);
            return 1;
        }
    }
    return 0;
}

int input_str(char** str){
    fflush(stdin);
    char c;
    int k = 2;
    *str = (char*)malloc(k*sizeof(char));
    char* p_str = *str;
    if(!*str) return 1;
    while((c = getchar()) != '\n'){
        if(p_str - *str == k-1){
            k*=2;
            char* p = (char*)realloc(*str, k*sizeof(char));
            if(!p){
                free(*str);
                return 1;
            }else{
                *str = p;
                p_str = *str + (k/2)-1;
            }
        }
        *p_str++ = c;
    }
    *p_str = 0;
    fflush(stdin);
    return 0;
}

int command_add(list* input){
    int error = 0;
    char* name;
    char* surname;
    char* patronymic;
    char* day;
    char* month;
    char* year;
    int gender;
    char* income;

    printf("\nName:\n");
    error = input_str(&name);
    if(error) return 2;
    if(str_valid(name)) return 1;
    input->name = name;

    printf("Surname:\n");
    error = input_str(&surname);
    if(error) return 2;
    if(str_valid(surname)) return 1;
    input->surname = surname;

    printf("Patronymic:\n");
    error = input_str(&patronymic);
    if(error) return 2;
    if(str_valid(patronymic)) return 1;
    input->patronymic = patronymic;

    printf("Day of birth:\n");
    error = input_str(&day);
    if(error) return 2;
    if(int_valid(day)) return 1;
    if(atoi(day) < 1 || atoi(day) > 31) return 3;
    input->day = atoi(day);

    printf("Month of birth:\n");
    error = input_str(&month);
    if(error) return 2;
    if(int_valid(month)) return 1;
    if(atoi(month) < 1 || atoi(month) > 12) return 3;
    input->month = atoi(month);

    printf("Year of birth:\n");
    error = input_str(&year);
    if(error) return 2;
    if(int_valid(year)) return 1;
    if(atoi(year) < 2000) return 3;
    input->year = atoi(year);

    if(check_date(input->day, input->month, input->year)) return 3;

    printf("Choose a gender:\n");
    printf("1) Male\n");
    printf("2) Female\n");
    scanf("%d", &gender);
    if(gender == 1) input->gender = 0;
    else if(gender == 2) input->gender = 1;
    else{
        fflush(stdin);
        return 4;
    }

    printf("Income (only with dot):\n");
    error = input_str(&income);
    if(error) return 2;
    if(d_valid(income)) return 1;
    input->income = atof(income);

    return 0;
}

int remove_person(list** core, int n, int counter_of_persons){
    list* person;
    list* previous;
    if(counter_of_persons == 1){
        (*core)->name = NULL;
        (*core)->surname = NULL;
        (*core)->patronymic = NULL;
        (*core)->day = -1;
        (*core)->month = -1;
        (*core)->year = -1;
        (*core)->gender = -1;
        (*core)->income = -1.0;
        (*core)->next = NULL;
        return 0;
    }else{
        if(n == 1){
            list* tmp = *core;
            *core = (*core)->next;
            free(tmp->name);
            free(tmp->surname);
            free(tmp->patronymic);
            free(tmp);
            return 0;
        }else{
            person = *core;
            for(int i = 1; i < n; i++){
                previous = person;
                person = person->next;
            }
            previous->next = person->next;
            free(person->name);
            free(person->surname);
            free(person->patronymic);
            free(person);
            return 0;
        }
    }
    return 0;
}

int print_certain_person(list* output, int n){
    printf("%d) ", n);
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
    return 0;
}

int find_name(list* core){
    list* person = core;
    char* name;
    int error = 0;
    error = input_str(&name);
    if(error) return 1;
    error = 0;
    while(person != NULL){
        if(!strcmp(person->name, name)){
            error++;
            print_certain_person(person, error);
        }
        person = person->next;
    }
    if(!error) printf("\nPersons with entered parameter are not found\n\n");
    else printf("\n");
    free(name);
    return 0;
}

int find_surname(list* core){
    list* person = core;
    char* surname;
    int error = 0;
    error = input_str(&surname);
    if(error) return 1;
    error = 0;
    while(person != NULL){
        if(!strcmp(person->surname, surname)){
            error++;
            print_certain_person(person, error);
        }
        person = person->next;
    }
    if(!error) printf("\nPersons with entered parameter are not found\n\n");
    else printf("\n");
    free(surname);
    return 0;
}

int find_patronymic(list* core){
    list* person = core;
    char* patronymic;
    int error = 0;
    error = input_str(&patronymic);
    if(error) return 1;
    error = 0;
    while(person != NULL){
        if(!strcmp(person->patronymic, patronymic)){
            error++;
            print_certain_person(person, error);
        }
        person = person->next;
    }
    if(!error) printf("\nPersons with entered parameter are not found\n\n");
    else printf("\n");
    free(patronymic);
    return 0;
}

int find_day_of_birth(list* core){
    list* person = core;
    char* day;
    char* month;
    char* year;
    int error = 0;

    printf("\nDay of birth:\n");
    error = input_str(&day);
    if(error) return 1;

    printf("Month of birth:\n");
    error = input_str(&month);
    if(error) return 1;

    printf("Year of birth:\n");
    error = input_str(&year);
    if(error) return 1;

    error = 0;
    while(person != NULL){
        if(person->day == atoi(day) && person->month == atoi(month) && person->year == atoi(year)){
            error++;
            print_certain_person(person, error);
        }
        person = person->next;
    }
    if(!error) printf("\nPersons with entered parameter are not found\n\n");
    else printf("\n");
    free(day);
    free(month);
    free(year);
    return 0;
}

int find_gender(list* core){
    list* person = core;
    int gender;
    int error = 0;

    printf("\nChoose a gender:\n");
    printf("1) Male\n");
    printf("2) Female\n");
    scanf("%d", &gender);
    gender -= 1;

    while(person != NULL){
        if(person->gender == gender){
            error++;
            print_certain_person(person, error);
        }
        person = person->next;
    }
    if(!error) printf("\nPersons with entered parameter are not found\n\n");
    else printf("\n");
    return 0;
}

int find_income(list* core){
    list* person = core;
    char* str_income;
    double income;
    int error = 0;

    error = input_str(&str_income);
    if(error) return 1;
    income = atof(str_income);

    error = 0;
    while(person != NULL){
        if(fabs(person->income - income) < EPSILON){
            error++;
            print_certain_person(person, error);
        }
        person = person->next;
    }
    if(!error) printf("\nPersons with entered parameter are not found\n\n");
    else printf("\n");
    free(str_income);
    return 0;
}

int write_list(FILE* fin, list* core){
    list* output = core;
    while(output != NULL){
        for(int i = 0; i < strlen(output->name); i++){
            fputc(*(output->name + i), fin);
        }
        fputc(' ', fin);
        for(int i = 0; i < strlen(output->surname); i++){
            fputc(*(output->surname + i), fin);
        }
        fputc(' ', fin);
        for(int i = 0; i < strlen(output->patronymic); i++){
            fputc(*(output->patronymic + i), fin);
        }
        fputc(' ', fin);
        if(output->day < 10) fprintf(fin, "0%d.", output->day);
        else fprintf(fin, "%d.", output->day);
        if(output->month < 10) fprintf(fin, "0%d.", output->month);
        else fprintf(fin, "%d.", output->month);
        fprintf(fin, "%d ", output->year);
        if(output->gender) fprintf(fin, "female ");
        else fprintf(fin, "male ");
        if(output->next == NULL) fprintf(fin, "%f", output->income);
        else fprintf(fin, "%f\n", output->income);
        output = output->next;
    }
    return 0;
}

int main(int argc, char *argv[]){
    printf("\n --- Check README_l3_task_7.txt before using app. Thank you! ---\n");
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
        if(gender != NULL){
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
        printf("[ Warning: List is empty ]\n\n");
    }
    int command = 0;
    int e = 0;
    while(command != 6){
        printf("Choose a command:\n");
        printf("1: Add a person\n");
        printf("2: Remove a person\n");
        printf("3: Find a person\n");
        printf("4: Print a list\n");
        printf("5: Save a list into file\n");
        printf("6: Exit\n");
        if(!scanf("%d", &command)){
            printf("\nInvalid command\n\n");
            e++;
            if(e == 3){
                printf("\n[Closing app...]\n");
                free(gender);
                clear_list(&core);
                return 0;
            }else{
                fflush(stdin);
                continue;
            }
        }
        if(command == 1){
            if(counter_of_persons == 0) input = core;
            else{
                if(create_new(&core)){
                    free(gender);
                    printf("Error -> create_new: memory allocation error\n");
                    clear_list(&core);
                    return 0;
                }
                input = core;
            }
            comm_error = command_add(input);
            if(comm_error == 1){
                printf("Invalid input!\n\n");
                break;
            }else if(comm_error == 2){
                printf("Memory allocation error!\n\n");
                break;
            }else if(comm_error == 3) {
                printf("Invalid date!");
                break;
            }else if(comm_error == 4) {
                printf("Invalid gender!");
                break;
            }
            counter_of_persons++;
            add(&core, counter_of_persons);
            comm_error = 0;
            printf("\n[ Add ---> done! ]\n\n");
        }else if(command == 2){
            if(counter_of_persons == 0){
                printf("\nList is empty!\n\n");
                continue;
            }
            printf("\nChoose a number of person to delete:\n");
            print_list(core);
            printf("\nNumber:\n");
            int n = 0;
            scanf("%d", &n);
            if(n < 1 || n > counter_of_persons){
                printf("\nInvalid number\n\n");
                fflush(stdin);
                continue;
            }
            remove_person(&core, n, counter_of_persons);
            counter_of_persons--;
            printf("[ Delete ---> done! ]\n\n");
        }else if(command == 3){
            if(counter_of_persons == 0){
                printf("\nList is empty!\n\n");
                continue;
            }
            printf("\nChoose a parameter to find:\n");
            printf("1) Name\n");
            printf("2) Surname\n");
            printf("3) Patronymic\n");
            printf("4) Date of birth\n");
            printf("5) Gender\n");
            printf("6) Income\n");
            int n = 0;
            scanf("%d", &n);
            if(n < 1 || n > 6){
                printf("\nInvalid number of parameter\n\n");
                fflush(stdin);
                continue;
            }
            if(n == 1){
                printf("\nName:\n");
                if(find_name(core)){
                    printf("Memory allocation error!\n\n");
                    break;
                }
            }else if(n == 2){
                printf("\nSurname:\n");
                if(find_surname(core)){
                    printf("Memory allocation error!\n\n");
                    break;
                }
            }else if(n == 3){
                printf("\nPatronymic:\n");
                if(find_patronymic(core)){
                    printf("Memory allocation error!\n\n");
                    break;
                }
            }else if(n == 4){
                if(find_day_of_birth(core)){
                    printf("Memory allocation error!\n\n");
                    break;
                }
            }else if(n == 5){
                find_gender(core);
            }else if(n == 6){
                printf("\nIncome (only with dot):\n");
                if(find_income(core)){
                    printf("Memory allocation error!\n\n");
                    break;
                }
            }
            printf("[ Find ---> done! ]\n\n");
            command = 0;
        }else if(command == 4){
            if(counter_of_persons == 0) printf("\nList is empty!\n\n");
            else print_list(core);
            printf("[ Print ---> done! ]\n\n");
            command = 0;
        }else if(command == 5){
            fin = fopen(argv[1], "w");
            if(!fin){
                printf("Could not open a file\n");
                break;
            }
            if(counter_of_persons) write_list(fin, core);
            fclose(fin);
            printf("\n[ Save ---> done! ]\n\n");
            command = 0;
        }else if(command == 6){
            break;
        }else{
            printf("\nInvalid command\n\n");
            e++;
            if(e == 3){
                printf("\n[Closing app...]\n");
                free(gender);
                clear_list(&core);
                return 0;
            }else{
                fflush(stdin);
                continue;
            }
        }
    }

    free(gender);
    clear_list(&core);
    return 0;
}