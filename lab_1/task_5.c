#include <stdio.h>
#include <string.h>
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

    int k = 16;

    if(argc == 1){
        printf("Invalid Input: no arguments\n");
        return 0;
    }
    if(argv[1][0] != '-'){
        printf("Invalid Input: symbol '-' before flag not found\n");
        return 0;
    }


    if(strcmp(argv[1], "-fi") == 0){

        int count = 0, e = 0;
        char c = 0;
        char c1 = 0;
        char* buff;
        char* p_buff;


        char fout_name[] = "result_task_5.txt";
        int i = strlen(argv[2]) - 1;
        for(; argv[2][i] != '\\'; i--);
        i  = i + 2 + 9;
        char* str_path = dynamic_string(&i);
        i -= 1 + 9;
        *(str_path + i) = 0;
        strncpy(str_path, argv[2], i);
        strcat(str_path, fout_name);


        FILE* fin = fopen(argv[2], "r");
        if(!fin){
            printf("File Error: could not open file\n");
            return 0;
        }
        FILE* fout = fopen(str_path, "w");
        if(!fout){
            printf("File Error: could not open file\n");
            fclose(fin);
            free(str_path);
            return 0;
        }


        while(c != EOF){
            c = 0;
            buff = dynamic_string(&k);
            if(buff == 0){
                printf("Malloc Error\n");
                fclose(fin);
                fclose(fout);
                remove(str_path);
                free(str_path);
                return 0;
            }
            p_buff = buff + 1;

            while((c != ' ') && (c != '\n') && (c != EOF)){
                c = fgetc(fin);
                if ((p_buff - buff) == k) {
                    if (re_all(&buff, &p_buff, &k)) {
                        printf("Realloc Error\n");
                        free(buff);
                        fclose(fout);
                        fclose(fin);
                        remove(str_path);
                        free(str_path);
                        return 0;
                    }
                }

                if((c == ' ') || (c == '\n') || (c==EOF)){
                    if(c == EOF) e = 1;
                    *(p_buff-1) = 0;
                    k = 16;
                    printf("%s ---> ", buff);
                    FILE* fp = fopen(buff, "r");
                    if(!fp){
                        printf("File Error: could not open file\n");
                        fclose(fin);
                        fclose(fout);
                        free(buff);
                        remove(str_path);
                        free(str_path);
                        return 0;
                    }
                    while(c1!=EOF){
                        c1 = fgetc(fp);
                        if(c1 == EOF){
                            if(e == 0) fputc(' ', fout);
                            fclose(fp);
                            free(buff);
                            count++;
                            printf("Done (%d file)\n", count);
                        }else{
                            fputc(c1, fout);
                        }
                    }
                    c1 = 0;
                }else{
                    *(p_buff-1) = c;
                    p_buff++;
                }
            }
        }
        fclose(fin);
        fclose(fout);
        printf("Flag -fi: done! ---> path: %s\n", str_path);
        free(str_path);



    }else if(strcmp(argv[1], "-cin") == 0){
        char c = 0, c1 = 0;
        int count = 0;
        int k = 16;

        printf("Enter file paths below\nTo finish the program, type 'stop'\n");
        char* buff = dynamic_string(&k);
        if(buff == 0){
            printf("Malloc Error\n");
            return 0;
        }
        char* p_buff = buff + 1;

        while(scanf("%c", &c)){
            if(c == '\n'){
                *(p_buff-1) = 0;
                if(strcmp(buff, "stop") == 0){
                    free(buff);
                    printf("Flag -cin: done!\n");
                    break;
                }
                printf("%s ---> ", buff);
                FILE* fp = fopen(buff, "r");
                if(!fp){
                    printf("File Error: could not open file\n");
                    free(buff);
                    return 0;
                }

                char fout_name[] = "result_task_5.txt";
                int i = strlen(buff) - 1;
                for(; buff[i] != '\\'; i--);
                i  = i + 2 + 9;
                char* str_path = dynamic_string(&i);
                i -= 1 + 9;
                *(str_path + i) = 0;
                strncpy(str_path, buff, i);
                strcat(str_path, fout_name);


                FILE* fout = fopen(str_path, "a");
                if(!fout){
                    printf("File Error: could not open file\n");
                    fclose(fp);
                    free(str_path);
                    free(buff);
                    return 0;
                }

                while(c1!=EOF){
                    c1 = fgetc(fp);
                    if(c1 == EOF){
                        fputc(' ', fout);
                        fclose(fp);
                        free(buff);
                        fclose(fout);
                        free(str_path);
                        k = 16;
                        buff = dynamic_string(&k);
                        if(buff == 0){
                            printf("Malloc Error\n");
                            return 0;
                        }
                        p_buff = buff + 1;
                        count++;
                        printf("Done (%d file)\n", count);
                    }else{
                        fputc(c1, fout);
                    }
                }
                c1 = 0;
            }else{
                if ((p_buff - buff) == k) {
                    if (re_all(&buff, &p_buff, &k)) {
                        printf("Realloc Error\n");
                        free(buff);
                        return 0;
                    }
                }
                *(p_buff-1) = c;
                p_buff++;
            }
        }


    }else if(strcmp(argv[1], "-arg") == 0){
        char c = 0;
        int count = 0, e = 0;

        char fout_name[] = "result_task_5.txt";
        int i = strlen(argv[2]) - 1;
        for(; argv[2][i] != '\\'; i--);
        i  = i + 2 + 9;
        char* str_path = dynamic_string(&i);
        i -= 1 + 9;
        *(str_path + i) = 0;
        strncpy(str_path, argv[2], i);
        strcat(str_path, fout_name);

        FILE* fout = fopen(str_path, "w");
        if(!fout){
            printf("File Error: could not open file\n");
            free(str_path);
            return 0;
        }

        for(int s = 2; s<argc; s++){
            if(s == argc-1) e = 1;
            FILE* fp = fopen(argv[s], "r");
            if(!fp){
                printf("File Error: could not open file\n");
                fclose(fout);
                free(str_path);
                return 0;
            }
            printf("%s ---> ", argv[s]);
            while(c!=EOF){
                c = fgetc(fp);
                if(c == EOF){
                    if(e == 0) fputc(' ', fout);
                    fclose(fp);
                    count++;
                    printf("Done (%d file)\n", count);
                }else{
                    fputc(c, fout);
                }
            }
            c = 0;
        }
        fclose(fout);
        printf("Flag -arg: done! ---> path: %s\n", str_path);
        free(str_path);

    }else{
        printf("Invalid Flag: unexpected flag\n");
        return 0;
    }
}