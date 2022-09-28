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
    int negative = 1;
    while(*buff != 0){
        if(*buff == '-'){
            negative = -1;
            buff++;
        }
        else num = num * 10 + (*buff++ - '0');
    }
    return (num * negative);
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

    printf("\n--- Choose an action ---\n1) numbers in odd positions\n2) even numbers\n3) the farthest number in value\n4) the sum of previous elements\n5) the sum of numbers less than chosen one\n\n6) exit\n");
    scanf("%d", &action);
    printf("\n");


    if(action == 1){
        int odd = 0;

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
                if(odd){
                    odd = 0;
                    num = str_to_int(buff);
                    printf("%d\n", num);
                }else odd = 1;
                k = 4;
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
                        if(odd){
                            odd = 0;
                            num = str_to_int(buff);
                            printf("%d ", num);
                        }else odd = 1;
                        k = 4;
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
                    if(!isdigit(c) && c != '-'){
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
                if(num % 2 == 0) printf("%d\n", num);
                else printf("\n");
                k = 4;
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
                        if(num % 2 == 0) printf("%d ", num);
                        k = 4;
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
                    if(!isdigit(c) && c != '-'){
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


    else if(action == 3){

        int max_diff = 0, max_diff_tmp = 0;
        int index = 0, index_num = 0;
        printf("---Enter an index of number---\n");
        scanf("%d", &index);
        if(index<0){
            printf("\nWrong index!\n");
            fclose(fin);
            return 0;
        }
        printf("\n");


        while(index != -1){
            c = fgetc(fin);
            if(c == EOF){
                printf("Wrong index!\n");
                fclose(fin);
                return 0;
            }
            if(c == ' ' || c == '\n' || c == '\t'){
                if(cp != ' ' && cp != '\n' && cp != '\t'){
                    index--;
                    cp = c;
                }
                else cp = c;
            }
            else{
                if(!index){
                    buff = dynamic_string(&k);
                    if(buff == 0){
                        printf("Malloc Error\n");
                        free(buff);
                        fclose(fin);
                        return 0;
                    }
                    *buff = c;
                    p_buff = buff + 2;


                    while(index != -1){
                        c = fgetc(fin);
                        if(c == ' ' || c == '\n' || c == '\t' || c == EOF){
                            if ((p_buff - buff) == k+1) {
                                if (re_all(&buff, &p_buff, &k)) {
                                    printf("Realloc Error\n");
                                    free(buff);
                                    fclose(fin);
                                    return 0;
                                }
                            }
                            *(p_buff-1) = 0;
                            index_num = str_to_int(buff);
                            fclose(fin);
                            free(buff);
                            fin = fopen(argv[1], "r");
                            if(!fin){
                                printf("File Error: could not open file\n");
                                return 0;
                            }
                            k = 4;
                            c = 0; cp = 0;
                            index--;
                        }else{
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
                else cp = c;
            }
        }

        int max_diff_num = index_num;


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
                if(num != index_num){
                    if((num >= 0 && index_num < 0) || (num < 0 && index_num >= 0)){
                        max_diff_tmp = abs(num) + abs(index_num);
                    }
                    else{
                        if(num > index_num){
                            max_diff_tmp = abs(num - index_num);
                        }
                        else max_diff_tmp = abs(index_num - num);
                    }
                    if(max_diff_tmp > max_diff){
                        max_diff = max_diff_tmp;
                        max_diff_num = num;
                    }
                }
                printf("The farthest number in value for %d is %d\n", index_num, max_diff_num);
                k = 4;
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
                        if(num != index_num){
                            if((num >= 0 && index_num < 0) || (num < 0 && index_num >= 0)){
                                max_diff_tmp = abs(num) + abs(index_num);
                            }
                            else{
                                if(num > index_num){
                                    max_diff_tmp = abs(num - index_num);
                                }
                                else max_diff_tmp = abs(index_num - num);
                            }
                            if(max_diff_tmp > max_diff){
                                max_diff = max_diff_tmp;
                                max_diff_num = num;
                            }
                        }
                        k = 4;
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
                    if(!isdigit(c) && c != '-'){
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


    else if(action == 4){
        int sum = 0;
        int index = 0, index_num = 0;
        printf("---Enter an index of number---\n");
        scanf("%d", &index);
        if(index<0){
            printf("\nWrong index!\n");
            fclose(fin);
            return 0;
        }
        printf("\n");

        int index2 = index;
        if(index == 0){
            printf("There is no previous elements, sum is 0\n");
            fclose(fin);
            return 0;
        }


        while(index != -1){
            c = fgetc(fin);
            if(c == EOF){
                printf("Wrong index!\n");
                fclose(fin);
                return 0;
            }
            if(c == ' ' || c == '\n' || c == '\t'){
                if(cp != ' ' && cp != '\n' && cp != '\t'){
                    index--;
                    cp = c;
                }
                else cp = c;
            }
            else{
                if(!index){
                    buff = dynamic_string(&k);
                    if(buff == 0){
                        printf("Malloc Error\n");
                        free(buff);
                        fclose(fin);
                        return 0;
                    }
                    *buff = c;
                    p_buff = buff + 2;


                    while(index != -1){
                        c = fgetc(fin);
                        if(c == ' ' || c == '\n' || c == '\t' || c == EOF){
                            if ((p_buff - buff) == k+1) {
                                if (re_all(&buff, &p_buff, &k)) {
                                    printf("Realloc Error\n");
                                    free(buff);
                                    fclose(fin);
                                    return 0;
                                }
                            }
                            *(p_buff-1) = 0;
                            index_num = str_to_int(buff);
                            fclose(fin);
                            free(buff);
                            fin = fopen(argv[1], "r");
                            if(!fin){
                                printf("File Error: could not open file\n");
                                return 0;
                            }
                            k = 4;
                            c = 0; cp = 0;
                            index--;
                        }else{
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
                else cp = c;
            }
        }


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
                printf("The sum of previous elements up to %d is %d\n", index_num, sum);
                k = 4;
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
                        if(index2 == 0){
                            printf("The sum of previous elements up to %d is %d\n", index_num, sum);
                            k = 4;
                            free(buff);
                            break;
                        }
                        else{
                            index2--;
                            sum += num;
                            k = 4;
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
                        }
                    }else cp = c;
                }
                else{
                    if(!isdigit(c) && c != '-'){
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


    else if(action == 5){
        int sum = 0;
        int index = 0, index_num = 0;
        printf("---Enter an index of number---\n");
        scanf("%d", &index);
        if(index<0){
            printf("\nWrong index!\n");
            fclose(fin);
            return 0;
        }
        printf("\n");


        while(index != -1){
            c = fgetc(fin);
            if(c == EOF){
                printf("Wrong index!\n");
                fclose(fin);
                return 0;
            }
            if(c == ' ' || c == '\n' || c == '\t'){
                if(cp != ' ' && cp != '\n' && cp != '\t'){
                    index--;
                    cp = c;
                }
                else cp = c;
            }
            else{
                if(!index){
                    buff = dynamic_string(&k);
                    if(buff == 0){
                        printf("Malloc Error\n");
                        free(buff);
                        fclose(fin);
                        return 0;
                    }
                    *buff = c;
                    p_buff = buff + 2;


                    while(index != -1){
                        c = fgetc(fin);
                        if(c == ' ' || c == '\n' || c == '\t' || c == EOF){
                            if ((p_buff - buff) == k+1) {
                                if (re_all(&buff, &p_buff, &k)) {
                                    printf("Realloc Error\n");
                                    free(buff);
                                    fclose(fin);
                                    return 0;
                                }
                            }
                            *(p_buff-1) = 0;
                            index_num = str_to_int(buff);
                            fclose(fin);
                            free(buff);
                            fin = fopen(argv[1], "r");
                            if(!fin){
                                printf("File Error: could not open file\n");
                                return 0;
                            }
                            k = 4;
                            c = 0; cp = 0;
                            index--;
                        }else{
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
                else cp = c;
            }
        }


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
                if(num < index_num) sum += num;
                printf("The sum of numbers less than %d is %d\n", index_num, sum);
                k = 4;
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
                        if(num < index_num) sum += num;
                        k = 4;
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
                    if(!isdigit(c) && c != '-'){
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


    else if(action == 6){
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