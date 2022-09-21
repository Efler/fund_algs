#include <stdio.h>
#include <stdlib.h>



int re_all(char** buff, char** p_buff, int* k){
    *k *= 2;
    char* p = (char*)realloc(*buff, (*k)*sizeof(char));
    if(p != NULL){
        *buff = p;
        *p_buff = p + ((*k)/2);
        return 0;
    }else{
        return 1;
    }
}



char* dynamic_string(int* k){
    char* buff = (char*)malloc((*k) * sizeof(char));
    if(buff == NULL){
        return 0;
    }
    return buff;
}



int main(int argc, char *argv[]){

//    char fin_path[] = "D:\\JetBrains\\CLion 2022.2.3\\CLionProjects\\fund_algs\\lab_1\\tester_task_7.txt";
//    char ftmp_path[] = "D:\\JetBrains\\CLion 2022.2.3\\CLionProjects\\fund_algs\\lab_1\\tester_task_7.txt";

    char* buff1;
    char* buff2;
    char* buff3;
    char* p_buff1;
    char* p_buff2;
    char* p_buff3;
    char c = 0;
    int k = 16;


    if(argc != 1){
        printf("Input Error: wrong number of arguments\n");
        return 0;
    }
    FILE* fin = fopen("D:\\JetBrains\\CLion 2022.2.3\\CLionProjects\\fund_algs\\lab_1\\tester_task_7.txt", "r");
    if(!fin){
        printf("File Error: could not open file\n");
        return 0;
    }
    FILE* ftmp = fopen("D:\\JetBrains\\CLion 2022.2.3\\CLionProjects\\fund_algs\\lab_1\\tmp.txt", "w");
    if(!ftmp){
        printf("File Error: could not create a temporary file\n");
        fclose(fin);
        return 0;
    }



    while(c!=EOF){
        c = 0;
        buff1 = dynamic_string(&k);
        if(buff1 == 0){
            printf("Malloc Error\n");
            free(buff1);
            fclose(fin);
            fclose(ftmp);
            return 0;
        }
        p_buff1 = buff1 + 1;
        while(c!=' '){
            c = fgetc(fin);
            if(c!=' '){
                if(c == '\n' || c == EOF){
                    printf("File Error: string is short\n");
                    free(buff1);
                    fclose(fin);
                    fclose(ftmp);
                    return 0;
                }
                if ((p_buff1 - buff1) == k) {
                    if (re_all(&buff1, &p_buff1, &k)) {
                        printf("Realloc Error\n");
                        free(buff1);
                        fclose(fin);
                        fclose(ftmp);
                        return 0;
                    }
                }
                *(p_buff1-1) = c;
                p_buff1++;
            }else{
                *(p_buff1-1) = 0;
                k = 16;
            }
        }
        c = 0;



        buff2 = dynamic_string(&k);
        if(buff2 == 0){
            printf("Malloc Error\n");
            free(buff1);
            free(buff2);
            fclose(fin);
            fclose(ftmp);
            return 0;
        }
        p_buff2 = buff2 + 1;
        while(c!=' '){
            c = fgetc(fin);
            if(c!=' '){
                if(c == '\n' || c == EOF){
                    printf("File Error: string is too short\n");
                    free(buff1);
                    free(buff2);
                    fclose(fin);
                    fclose(ftmp);
                    return 0;
                }
                if ((p_buff2 - buff2) == k) {
                    if (re_all(&buff2, &p_buff2, &k)) {
                        printf("Realloc Error\n");
                        free(buff1);
                        free(buff2);
                        fclose(fin);
                        fclose(ftmp);
                        return 0;
                    }
                }
                *(p_buff2-1) = c;
                p_buff2++;
            }else{
                *(p_buff2-1) = 0;
                k = 16;
            }
        }
        c = 0;


        buff3 = dynamic_string(&k);
        if(buff3 == 0){
            printf("Malloc Error\n");
            free(buff1);
            free(buff2);
            free(buff3);
            fclose(fin);
            fclose(ftmp);
            return 0;
        }
        p_buff3 = buff3 + 1;
        while(c!='\n' && c!=EOF){
            c = fgetc(fin);
            if(c!='\n'){
                if(c==' '){
                    printf("File Error: string is too long\n");
                    free(buff1);
                    free(buff2);
                    free(buff3);
                    fclose(fin);
                    fclose(ftmp);
                    return 0;
                }
                if(c==EOF){
                    if ((p_buff3 - buff3) == k) {
                        if (re_all(&buff3, &p_buff3, &k)) {
                            printf("Realloc Error\n");
                            free(buff1);
                            free(buff2);
                            free(buff3);
                            fclose(fin);
                            fclose(ftmp);
                            return 0;
                        }
                    }
                    *(p_buff3-1) = 0;
                    fprintf(ftmp, "%s %s %s", buff3, buff1, buff2);
                    free(buff1);
                    free(buff2);
                    free(buff3);
                    fclose(fin);
                    fclose(ftmp);
                    printf("Done!\n");
                }else{
                    if ((p_buff3 - buff3) == k) {
                        if (re_all(&buff3, &p_buff3, &k)) {
                            printf("Realloc Error\n");
                            free(buff1);
                            free(buff2);
                            free(buff3);
                            fclose(fin);
                            fclose(ftmp);
                            return 0;
                        }
                    }
                    *(p_buff3-1) = c;
                    p_buff3++;
                }
            }else{
                *(p_buff3-1) = 0;
                fprintf(ftmp, "%s %s %s\n", buff3, buff1, buff2);
                free(buff1);
                free(buff2);
                free(buff3);
                k = 16;
            }
        }
    }
}