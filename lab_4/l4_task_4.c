#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#define EPSILON 1e-7

typedef struct count_el{
    int num;
    int count;
}count_el;

typedef struct arr{
    char name;
    int* value;
    int value_buff;
    int count_of_el;
}arr;

int clear_specific_array(arr* arrays, char Name){
    for(int i = 0; i < 26; i++){
        if(arrays[i].name == toupper(Name)){
            free(arrays[i].value);
            arrays[i].value_buff = 4;
            arrays[i].count_of_el = 0;
            arrays[i].value = (int*)malloc(arrays[i].value_buff * sizeof(int));
            if(!arrays[i].value){
                return 1;
            }
            return 0;
        }
    }
    return 1;
}

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
    printf("[App: clearing arrays]");
}

int create_arrays(arr* arrays, int* checker){
    for(int i = 0; i < 26; i++){
        arrays[i].name = (char)(65 + i);
        arrays[i].value_buff = 1;
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
        if(arrays[i].name == toupper(Name)) return i;
    }
}

void print_array(arr* arrays, int a, int b, int index, char Name){
    printf("%c:  ", Name);
    if(b != -1) {
        while (a <= b) {
            printf("%d ", *(arrays[index].value + a));
            a++;
        }
    }
    printf("\n");
}

int print(FILE* fin, char* comm, arr* arrays, char* name_out){
    char c;
    char Name = fgetc(fin);
    *name_out = Name;
    if(!isalpha(Name)){
        return 1;
    }
    if(toupper(Name) < 65 || toupper(Name) > 90){
        return 1;
    }
    c = fgetc(fin);
    if(c != '\n' && c != ',' && c != EOF){
        return 1;
    }
    c = fgetc(fin);
    int index = find_array(arrays, Name);
    int k = 4;
    char* buff = (char*)malloc((k) * sizeof(char));
    if(!buff){
        return 2;
    }
    char* p_buff = buff;
    while(!feof(fin)){
        c = fgetc(fin);
        if(c == ','){
            if((p_buff - buff) == k){
                char* p = (char*)realloc(buff, (k+1)*sizeof(char));
                if(!p){
                    free(buff);
                    return 2;
                }else{
                    buff = p;
                    p_buff = p + k;
                }
            }
            *p_buff = 0;
            int a = atoi(buff);
            free(buff);
            c = fgetc(fin);
            int pr_digit = 0;
            int b = 0;
            while(!feof(fin)){
                c = fgetc(fin);
                if(c == '\n' || c == EOF){
                    if(a < 0 || b < 0) return 5;
                    else if(a > b) return 4;
                    else if(a > (arrays[index].count_of_el - 1) || b > (arrays[index].count_of_el - 1)) return 6;
                    else{
                        print_array(arrays, a, b, index, Name);
                        return 0;
                    }
                }else{
                    b = (pr_digit * 10) + (c - '0');
                    pr_digit = b;
                }
            }
        }else if(c == '\n' || c == EOF){
            if((p_buff - buff) == k){
                char* p = (char*)realloc(buff, (k+1)*sizeof(char));
                if(!p){
                    free(buff);
                    return 2;
                }else{
                    buff = p;
                    p_buff = p + k;
                }
            }
            *p_buff = 0;
            if(!strcmp(buff, "all")){
                print_array(arrays, 0, arrays[index].count_of_el - 1, index, Name);
                free(buff);
                return 0;
            }else{
                free(buff);
                return 3;
            }
        }else{
            if((p_buff - buff) == k){
                k *= 2;
                char* p = (char*)realloc(buff, (k)*sizeof(char));
                if(!p){
                    free(buff);
                    return 2;
                }else{
                    buff = p;
                    p_buff = p + k/2;
                }
            }
            *p_buff++ = c;
        }
    }

}

int command_free(FILE* fin, arr* arrays, char* comm, char* name_out){
    char c;
    char Name = fgetc(fin);
    *name_out = Name;
    if(!isalpha(Name)){
        return 1;
    }
    if(toupper(Name) < 65 || toupper(Name) > 90){
        return 1;
    }
    c = fgetc(fin);
    c = fgetc(fin);
    int index = find_array(arrays, Name);
    if(arrays[index].count_of_el){
        if(clear_specific_array(arrays, Name)){
            return 2;
        }
    }
    return 0;
}

int create_rand_array(arr* arrays, int index, int count, int a, int b){
    srand(time(NULL));
    arrays[index].value_buff = count;
    free(arrays[index].value);
    arrays[index].value = (int*)malloc(arrays[index].value_buff * sizeof(int));
    if(!arrays[index].value){
        return 1;
    }
    while(arrays[index].count_of_el != count){
        *(arrays[index].value + arrays[index].count_of_el) = rand()%(b-a+1) + a;
        arrays[index].count_of_el++;
    }
    return 0;
}

int copy_array(arr* arrays, int index1, int index2, int a, int b){
    int count = b - a + 1;
    arrays[index2].value_buff = count;
    free(arrays[index2].value);
    arrays[index2].value = (int*)malloc(arrays[index2].value_buff * sizeof(int));
    if(!arrays[index2].value){
        return 1;
    }
    while(arrays[index2].count_of_el != count){
        *(arrays[index2].value + arrays[index2].count_of_el) = *(arrays[index1].value + a);
        arrays[index2].count_of_el++;
        a++;
    }
    return 0;
}

int remove_from_array(arr* arrays, int index, int a, int count){
    int k = arrays[index].count_of_el - (count);
    int* buff = (int*)malloc(k * sizeof(int));
    if(!buff){
        return 1;
    }
    int n = 0;
    while(n != a){
        *(buff + n) = *(arrays[index].value + n);
        n++;
    }
    int sch = n;
    n += count;
    while(n < arrays[index].count_of_el){
        *(buff + sch) = *(arrays[index].value + n);
        n++;
        sch++;
    }
    arrays[index].count_of_el = k;
    arrays[index].value_buff = k;
    free(arrays[index].value);
    arrays[index].value = buff;
    return 0;
}

int concat_arrays(arr* arrays, int index1, int index2){
    int k = arrays[index1].count_of_el + arrays[index2].count_of_el;
    int* p = (int*)realloc(arrays[index1].value, (k)*sizeof(int));
    if(!p){
        return 1;
    }else{
        arrays[index1].value = p;
    }
    for(int i = 0; i < arrays[index2].count_of_el; i++){
        *(arrays[index1].value + arrays[index1].count_of_el + i) = *(arrays[index2].value + i);
    }
    arrays[index1].value_buff = k;
    arrays[index1].count_of_el = k;
    return 0;
}

int concat(FILE* fin, arr* arrays, char* comm){
    char c;
    char Name1 = fgetc(fin);
    if(!isalpha(Name1)){
        return 1;
    }
    if(toupper(Name1) < 65 || toupper(Name1) > 90){
        return 1;
    }
    c = fgetc(fin);
    c = fgetc(fin);
    char Name2 = fgetc(fin);
    if(!isalpha(Name2)){
        return 1;
    }
    if(toupper(Name2) < 65 || toupper(Name2) > 90){
        return 1;
    }
    c = fgetc(fin);
    int index1 = find_array(arrays, Name1);
    int index2 = find_array(arrays, Name2);
    if(arrays[index2].count_of_el == 0){
        return 0;
    }else if(arrays[index1].count_of_el == 0 && arrays[index2].count_of_el != 0){
        if(copy_array(arrays, index2, index1, 0, arrays[index2].count_of_el - 1)){
            return 2;
        }
    }else{
        if(concat_arrays(arrays, index1, index2)){
            return 3;
        }
    }
    return 0;
}

int command_remove(FILE* fin, arr* arrays, char* comm, char* name_out){
    char c;
    char Name = fgetc(fin);
    *name_out = Name;
    if(!isalpha(Name)){
        return 1;
    }
    if(toupper(Name) < 65 || toupper(Name) > 90){
        return 1;
    }
    c = fgetc(fin);
    c = fgetc(fin);
    int minus = 1;
    int pr_digit = 0;
    int a = 0;
    while(c != ','){
        c = fgetc(fin);
        if(c == ','){
            continue;
        }else if(c == '-'){
            minus = -1;
        }else{
            a = (pr_digit * 10) + (c - '0');
            pr_digit = a;
        }
    }
    a *= minus;
    c = fgetc(fin);
    if(a < 0){
        return 2;
    }
    minus = 1;
    pr_digit = 0;
    int count = 0;
    while(c != '\n' && c != EOF){
        c = fgetc(fin);
        if(c == '\n' || c == EOF){
            continue;
        }else if(c == '-'){
            minus = -1;
        }else{
            count = (pr_digit * 10) + (c - '0');
            pr_digit = count;
        }
    }
    count *= minus;
    if(count < 1){
        return 3;
    }
    int index = find_array(arrays, Name);
    if((a + count) > arrays[index].count_of_el){
        return 4;
    }
    if(remove_from_array(arrays, index, a, count)){
        return 5;
    }
    return 0;
}

int copy(FILE* fin, arr* arrays, char* comm){
    char c;
    char Name = fgetc(fin);
    if(!isalpha(Name)){
        return 1;
    }
    if(toupper(Name) < 65 || toupper(Name) > 90){
        return 1;
    }
    c = fgetc(fin);
    c = fgetc(fin);
    int minus = 1;
    int pr_digit = 0;
    int a = 0;
    while(c != ','){
        c = fgetc(fin);
        if(c == ','){
            continue;
        }else if(c == '-'){
            minus = -1;
        }else{
            a = (pr_digit * 10) + (c - '0');
            pr_digit = a;
        }
    }
    a *= minus;
    c = fgetc(fin);
    if(a < 0){
        return 3;
    }
    minus = 1;
    pr_digit = 0;
    int b = 0;
    while(c != ','){
        c = fgetc(fin);
        if(c == ','){
            continue;
        }else if(c == '-'){
            minus = -1;
        }else{
            b = (pr_digit * 10) + (c - '0');
            pr_digit = b;
        }
    }
    b *= minus;
    c = fgetc(fin);
    if(a > b){
        return 4;
    }
    char Name2 = fgetc(fin);
    if(!isalpha(Name2)){
        return 1;
    }
    if(toupper(Name2) < 65 || toupper(Name2) > 90){
        return 1;
    }
    c = fgetc(fin);
    if(c != '\n' && c != EOF){
        return 1;
    }
    int index1 = find_array(arrays, Name);
    int index2 = find_array(arrays, Name2);
    if(arrays[index2].count_of_el){
        if(clear_specific_array(arrays, Name)){
            return 2;
        }
    }
    if(copy_array(arrays, index1, index2, a, b)){
        return 5;
    }
    return 0;
}

int command_rand(FILE* fin, arr* arrays, char* comm, char* name_out){
    char c;
    char Name = fgetc(fin);
    *name_out = Name;
    if(!isalpha(Name)){
        return 1;
    }
    if(toupper(Name) < 65 || toupper(Name) > 90){
        return 1;
    }
    c = fgetc(fin);
    c = fgetc(fin);
    int index = find_array(arrays, Name);
    if(arrays[index].count_of_el){
        if(clear_specific_array(arrays, Name)){
            return 2;
        }
    }
    int minus = 1;
    int pr_digit = 0;
    int count = 0;
    while(c != ','){
        c = fgetc(fin);
        if(c == ','){
            continue;
        }else if(c == '-'){
            minus = -1;
        }else{
            count = (pr_digit * 10) + (c - '0');
            pr_digit = count;
        }
    }
    count *= minus;
    c = fgetc(fin);
    if(count <= 0){
        return 3;
    }
    minus = 1;
    pr_digit = 0;
    int a = 0;
    while(c != ','){
        c = fgetc(fin);
        if(c == ','){
            continue;
        }else if(c == '-'){
            minus = -1;
        }else{
            a = (pr_digit * 10) + (c - '0');
            pr_digit = a;
        }
    }
    a *= minus;
    c = fgetc(fin);
    minus = 1;
    pr_digit = 0;
    int b = 0;
    while(c != '\n' && c != EOF){
        c = fgetc(fin);
        if(c == '\n' || c == EOF){
            continue;
        }else if(c == '-'){
            minus = -1;
        }else{
            b = (pr_digit * 10) + (c - '0');
            pr_digit = b;
        }
    }
    b *= minus;
    if(a > b){
        return 4;
    }
    if(create_rand_array(arrays, index, count, a, b)){
        return 5;
    }
    return 0;
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

int save(FILE* fin, char* comm, arr* arrays, char* name_out){
    char Name;
    int k = 6;
    char* file = (char*)malloc((k) * sizeof(char));
    int error = load_args(fin, &file, &Name, &k);
    *name_out = Name;
    if(error == 1){
        free(file);
        return 1;
    }else if(error == 2){
        free(file);
        return 2;
    }else if(error == 3){
        free(file);
        return 3;
    }
    FILE* file_save = fopen(file, "w");
    if(!file_save){
        free(file);
        return 4;
    }
    int index = find_array(arrays, Name);
    char* num;
    int n;
    int count_digits;
    int count = arrays[index].count_of_el;
    while(count != 0){
        count_digits = 0;
        n = *(arrays[index].value + (arrays[index].count_of_el - count));
        while(n){
            count_digits++;
            n /= 10;
        }
        num = (char*)malloc((count_digits + 1) * sizeof(char));
        if(!num){
            fclose(file_save);
            free(file);
            return 3;
        }
        itoa(*(arrays[index].value + (arrays[index].count_of_el - count)), num, 10);
        fputs(num, file_save);
        fputc(' ', file_save);
        count--;
        free(num);
    }
    fclose(file_save);
    free(file);
    return 0;
}

int load(FILE* fin, char* comm, arr* arrays, int* che, char* name_out){
    char Name;
    int k = 6;
    char* file = (char*)malloc((k) * sizeof(char));
    int error = load_args(fin, &file, &Name, &k);
    *name_out = Name;
    if(error == 1){
        free(file);
        return 1;
    }else if(error == 2){
        free(file);
        return 2;
    }else if(error == 3){
        free(file);
        return 3;
    }
    FILE* file_load = fopen(file, "r");
    if(!file_load){
        free(file);
        return 4;
    }
    int index = find_array(arrays, Name);
    if(*che){
        if(arrays[index].count_of_el){
            if(clear_specific_array(arrays, Name)){
                fclose(file_load);
                free(file);
                return 7;
            }
        }
    }else *che = 1;
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
        }else if(!isdigit(c) && c != '-'){
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

int compare_up(const void* x_void, const void* y_void){
    int x = *(int*)x_void;
    int y = *(int*)y_void;
    return x - y;
}

int compare_down(const void* x_void, const void* y_void){
    int x = *(int*)x_void;
    int y = *(int*)y_void;
    return y - x;
}

int compare_shuffle(const void* x_void, const void* y_void){
    return (rand()%3 - 1);
}

int sort(FILE* fin, char* comm, arr* arrays, char* sign, char* name_out){
    char c;
    char Name = fgetc(fin);
    *name_out = Name;
    if(!isalpha(Name)){
        return 1;
    }
    if(toupper(Name) < 65 || toupper(Name) > 90){
        return 1;
    }
    int index = find_array(arrays, Name);
    *sign = fgetc(fin);
    if(arrays[index].count_of_el == 0){
        c = fgetc(fin);
        return 0;
    }
    if(*sign == '+'){
        if(arrays[index].value_buff != arrays[index].count_of_el){
            int* p = (int*)realloc(arrays[index].value, (arrays[index].count_of_el)*sizeof(int));
            if(!p){
                return 3;
            }else{
                arrays[index].value = p;
            }
        }
        qsort(arrays[index].value, arrays[index].count_of_el, sizeof(int), compare_up);
    }else if(*sign == '-'){
        if(arrays[index].value_buff != arrays[index].count_of_el){
            int* p = (int*)realloc(arrays[index].value, (arrays[index].count_of_el)*sizeof(int));
            if(!p){
                return 3;
            }else{
                arrays[index].value = p;
            }
        }
        qsort(arrays[index].value, arrays[index].count_of_el, sizeof(int), compare_down);
    }else{
        return 2;
    }
    c = fgetc(fin);
    return 0;
}

int shuffle(FILE* fin, char* comm, arr* arrays, char* name_out){
    srand(time(NULL));
    char c;
    char Name = fgetc(fin);
    *name_out = Name;
    if(!isalpha(Name)){
        return 1;
    }
    if(toupper(Name) < 65 || toupper(Name) > 90){
        return 1;
    }
    int index = find_array(arrays, Name);
    c = fgetc(fin);
    if(arrays[index].count_of_el == 0){
        return 0;
    }
    if(arrays[index].value_buff != arrays[index].count_of_el){
        int* p = (int*)realloc(arrays[index].value, (arrays[index].count_of_el)*sizeof(int));
        if(!p){
            return 2;
        }else{
            arrays[index].value = p;
        }
    }
    qsort(arrays[index].value, arrays[index].count_of_el, sizeof(int), compare_shuffle);
    return 0;
}

int stats(FILE* fin, char* comm, arr* arrays, int* max, int* min, int* index_max, int* index_min, int* max_count, double* middle, double* max_differ, int* max_differ_num, int* count, char* name_out, int* count_of_elements){
    char c;
    char Name = fgetc(fin);
    *name_out = Name;
    if(!isalpha(Name)){
        return 1;
    }
    if(toupper(Name) < 65 || toupper(Name) > 90){
        return 1;
    }
    int index = find_array(arrays, Name);
    c = fgetc(fin);
    if(arrays[index].count_of_el == 0){
        return 3;
    }
    int k = 4;
    int n = 1;
    int checkup1 = 0;
    int checkup2 = 0;
    int checkup3 = 1;
    int often = 1;
    *max = *(arrays[index].value);
    *min = *(arrays[index].value);
    count_el* mass = (count_el*)malloc(k * sizeof(count_el));
    mass[0].num = *(arrays[index].value);
    mass[0].count = 1;
    for(int i = 0; i < arrays[index].count_of_el; i++){
        if(*(arrays[index].value + i) < *min){
            *min = *(arrays[index].value + i);
            *index_min = i;
        }
        if(*(arrays[index].value + i) > *max){
            *max = *(arrays[index].value + i);
            *index_max = i;
        }
        *middle += *(arrays[index].value + i);
        for(int s = 0; s < n; s++){
            checkup3 = 1;
            if(!checkup1){
                checkup1 += 1;
                break;
            }else if(*(arrays[index].value + i) == mass[s].num){
                mass[s].count++;
                if(mass[s].count > often){
                    often = mass[s].count;
                }
                break;
            }else{
                checkup3 = 0;
            }
        }
        if(!checkup3){
            if((k - n) == 0){
                k *= 2;
                count_el* p = (count_el*)realloc(mass, k * sizeof(count_el));
                if(!p){
                    free(mass);
                    return 2;
                }else{
                    mass = p;
                }
            }
            n++;
            mass[n-1].num = *(arrays[index].value + i);
            mass[n-1].count = 1;
        }
    }
    for(int s = 0; s < n; s++){
        if(often == mass[s].count){
            if(!checkup2){
                *max_count = mass[s].num;
                checkup2++;
            }else{
                if(*max_count < mass[s].num) *max_count = mass[s].num;
            }
        }
    }
    free(mass);
    *middle /= arrays[index].count_of_el;
    *count = often;
    *count_of_elements = arrays[index].count_of_el;
    if(fabs(*middle - *min) - fabs(*middle - *max) > EPSILON){
        *max_differ = fabs(*middle - *min);
        *max_differ_num = *min;
    }else{
        *max_differ = fabs(*middle - *max);
        *max_differ_num = *max;
    }
    return 0;
}

int main(int argc, char *argv[]){
    printf("\n");
    if(argc != 2){
        printf("Wrong number of arguments\n\n");
        return 0;
    }
    FILE* fin = fopen(argv[1], "r");
    if(!fin){
        printf("Could not open a file\n\n");
        return 0;
    }
    char* comm;
    int check_comm = 0;
    int error;
    int checker = 0;
    int che = 0;
    char sign;
    char name_out;
    arr arrays[26];
    if(create_arrays(arrays, &checker)){
        printf("Memory Allocation Error: arrays\n\n");
        clear_arrays_value(arrays, &checker);
        if(check_comm) free(comm);
        else check_comm++;
        fclose(fin);
        return 0;
    }
    while(!feof(fin)){
        error = 0;
        comm = write_command(fin, &error);
        if(!comm){
            printf("Memory Allocation Error: command\n\n");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }
        if(error == 1){
            printf("Wrong format of a command\n\n");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }
        int comm_error;
        if(!strcmp(comm, "Load")){
            comm_error = load(fin, comm, arrays, &che, &name_out);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Load %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Wrong syntax of arguments: Load %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Memory Allocation Error: Load %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 4){
                printf("Could not open a file: Load %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 5){
                printf("Invalid numbers in file: Load %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 6) {
                printf("Memory Allocation Error: Load %c ---> arrays\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            else if(comm_error == 7) {
                printf("Memory Allocation Error: Load %c ---> clear_specific_array\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Load %c ---> Done!\n\n", name_out);
        }else if(!strcmp(comm, "Save")){
            comm_error = save(fin, comm, arrays, &name_out);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Save %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Wrong syntax of arguments: Save %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Memory Allocation Error: Save %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 4){
                printf("Could not open a file: Save %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Save %c ---> Done!\n\n", name_out);
        }else if(!strcmp(comm, "Rand")){
            comm_error = command_rand(fin, arrays, comm, &name_out);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Rand %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Memory Allocation Error: rand %c ---> clear_specific_array\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Rand %c arguments error: count < 1\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 4){
                printf("Rand %c borders error: a > b\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 5){
                printf("Memory Allocation Error: rand %c ---> create_rand_array\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Rand %c ---> Done!\n\n", name_out);
        }else if(!strcmp(comm, "Concat")){
            comm_error = concat(fin, arrays, comm);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Concat\n\n");
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Memory Allocation Error: concat ---> copy_array\n\n");
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Memory Allocation Error: concat ---> concat_arrays\n\n");
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Concat ---> Done!\n\n");
        }else if(!strcmp(comm, "Free")){
            comm_error = command_free(fin, arrays, comm, &name_out);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Free %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Memory Allocation Error: free %c ---> clear_specific_array\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Free %c ---> Done!\n\n", name_out);
        }else if(!strcmp(comm, "Remove")){
            comm_error = command_remove(fin, arrays, comm, &name_out);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Remove %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Remove %c arguments error: index < 0\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Remove %c arguments error: count < 1\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 4){
                printf("Remove %c error: request to delete non-existent elements\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 5){
                printf("Memory Allocation Error: remove %c ---> remove_from_array\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Remove %c ---> Done!\n\n", name_out);
        }else if(!strcmp(comm, "Copy")){
            comm_error = copy(fin, arrays, comm);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Copy\n\n");
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Memory Allocation Error: copy ---> clear_specific_array\n\n");
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Copy borders error: at least one of borders is less than 0\n\n");
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 4){
                printf("Copy borders error: a > b\n\n");
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 5){
                printf("Memory Allocation Error: copy ---> copy_array\n\n");
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Copy ---> Done!\n\n");
        }else if(!strcmp(comm, "Sort")){
            comm_error = sort(fin, comm, arrays, &sign, &name_out);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Sort %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Sort %c error: wrong syntax of a sign\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Memory Allocation Error: Sort %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Sort %c(%c) ---> Done!\n\n", name_out, sign);
        }else if(!strcmp(comm, "Shuffle")){
            comm_error = shuffle(fin, comm, arrays, &name_out);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Shuffle %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Memory Allocation Error: Shuffle %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Shuffle %c ---> Done!\n\n", name_out);
        }else if(!strcmp(comm, "Stats")){
            int max = 0;
            int min = 0;
            int index_max = 0;
            int index_min = 0;
            int max_count = 0;
            double middle = 0.0;
            double max_differ = 0.0;
            int max_differ_num = 0;
            int count = 0;
            int count_of_elements = 0;

            comm_error = stats(fin, comm, arrays, &max, &min, &index_max, &index_min, &max_count, &middle, &max_differ, &max_differ_num, &count, &name_out, &count_of_elements);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Stats %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Memory Allocation Error: Stats %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Stats error: array %c is empty\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("--- Stats %c ---\n", name_out);
            printf("1) Size: %d\n", count_of_elements);
            printf("2) Min element: %d (index %d)\n", min, index_min);
            printf("3) Max element: %d (index %d)\n", max, index_max);
            printf("4) Most common element: %d (%d times)\n", max_count, count);
            printf("5) Arithmetic mean of elements: %f\n", middle);
            printf("6) Maximum deviation from the arithmetic mean: %f (element %d)\n", max_differ, max_differ_num);
            printf("--- Stats done! ---\n\n");
        }else if(!strcmp(comm, "Print")){
            comm_error = print(fin, comm, arrays, &name_out);
            if(comm_error == 1){
                printf("Wrong syntax of arguments: Print %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 2){
                printf("Memory Allocation Error: Print %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 3){
                printf("Wrong syntax of arguments: Print %c\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 4){
                printf("Print %c ---> Range error: a > b\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 5){
                printf("Print %c ---> Range error: at least one of borders less than 0\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }else if(comm_error == 6){
                printf("Print %c ---> Range error: at least one of borders points to a non-existent element\n\n", name_out);
                checker = -1;
                clear_arrays_value(arrays, &checker);
                free(comm);
                fclose(fin);
                comm_error = 0;
                return 0;
            }
            printf("Print %c ---> Done!\n\n", name_out);
        }else{
            printf("Wrong command\n\n");
            checker = -1;
            clear_arrays_value(arrays, &checker);
            free(comm);
            fclose(fin);
            return 0;
        }
    }
    checker = -1;
    clear_arrays_value(arrays, &checker);
    free(comm);
    fclose(fin);
    return 0;
}