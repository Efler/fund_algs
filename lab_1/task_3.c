#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* dynamic_string(int* k){
    char* buff = (char*)malloc((*k) * sizeof(char));
    if(buff == NULL){
        return 0;
    }
    return buff;
}


int main(int argc, char *argv[]){
    FILE* fin;
    FILE* fout;
    char* str_path;
    int str_path_checker = 0;

    if(argc == 1){
        printf("Invalid Input: no arguments\n");
        return 0;
    }
    if((argv[1][0] != '-')&&(argv[1][0] != '/')){
        printf("Invalid Input: symbol '-' before flag not found\n");
        return 0;
    }
    if(argc > 4 || argc < 3){
        printf("Invalid Input: wrong number of arguments\n");
        return 0;
    }


    if(strlen(argv[1]) == 2){
        if(argc != 3){
            printf("Invalid Input: wrong number of arguments\n");
            return 0;
        }

        char fout_prename[] = "out_";
        int i = strlen(argv[2]) - 1;
        int count_name = 0;
        for(; argv[2][i] != '\\'; i--){
            if(i == 0){
                printf("Invalid Input: path error\n");
                return 0;
            }
            count_name++;
        }
        char str_name[count_name+1];
        int e = i+1;
        int m = 0;
        for(; count_name > 0; count_name--){
            str_name[m] = argv[2][e];
            e++; m++;
        }
        i = i + 2;
        str_path = dynamic_string(&i);
        i -= 1;
        *(str_path + i) = 0;
        strncpy(str_path, argv[2], i);
        strcat(str_path, fout_prename);
        strcat(str_path, str_name);
        printf("%s %s\n", str_path, argv[2]);
        fin = fopen(argv[2], "r");
        if(!fin){
            printf("File Error: could not open file\n");
            free(str_path);
            return 0;
        }
        fout = fopen(str_path, "w");
        if(!fout){
            printf("File Error: could not open file\n");
            fclose(fin);
            free(str_path);
            return 0;
        }
        str_path_checker = 1;

    }else if((strlen(argv[1]) == 3) && (argv[1][1] == 'n')){
        if(argc != 4){
            printf("Invalid Input: wrong number of arguments\n");
            return 0;
        }
        fin = fopen(argv[2], "r");
        if(!fin){
            printf("File Error: could not open file\n");
            return 0;
        }
        fout = fopen(argv[3], "w");
        if(!fout){
            printf("File Error: could not open file\n");
            fclose(fin);
            return 0;
        }
    }else{
        printf("Invalid Input: unexpected flag\n");
        return 0;
    }


    if((strcmp(argv[1], "-d") == 0) || (strcmp(argv[1], "-nd") == 0) || (strcmp(argv[1], "/d") == 0) || (strcmp(argv[1], "/nd")) == 0){
        char c = ' ';
        while(c != EOF){
            c = fgetc((fin));
            if((c < '0' || c > '9') && (c != EOF)){
                fputc(c, fout);
            }
        }
        printf("Done!\n");
    }
    else if((strcmp(argv[1], "-i") == 0) || (strcmp(argv[1], "-ni") == 0) || (strcmp(argv[1], "/i") == 0) || (strcmp(argv[1], "/ni")) == 0){
        int count = 0;
        int count_line = 1;
        char c = ' ';
        while (c != EOF) {
            c = fgetc((fin));
            if (c == EOF || c == '\n') {
                fprintf(fout, "Sum of letters in the line #%d: %d\n", count_line, count);
                count_line++;
                count = 0;
            }
            else if(isalpha(c)){
                count++;
            }
        }
        printf("Done!\n");
    }
    else if((strcmp(argv[1], "-s") == 0) || (strcmp(argv[1], "-ns") == 0) || (strcmp(argv[1], "/s") == 0) || (strcmp(argv[1], "/ns")) == 0){
        int count = 0;
        int count_line = 1;
        char c = ' ';
        while (c != EOF) {
            c = fgetc((fin));
            if (c == EOF || c == '\n') {
                fprintf(fout, "Sum of letters in the line #%d: %d\n", count_line, count);
                count_line++;
                count = 0;
            }
            else if(!(isalpha(c) || isdigit(c) || (c == ' '))){
                count++;
            }
        }
        printf("Done!\n");
    }
    else if((strcmp(argv[1], "-a") == 0) || (strcmp(argv[1], "-na") == 0) || (strcmp(argv[1], "/a") == 0) || (strcmp(argv[1], "/na")) == 0){
        char c;
        while((c=fgetc(fin)) != EOF) {
            if(isdigit(c)){
                fputc(c, fout);
            }else{
                fprintf(fout, "%d", (int)c);
            }
        }
        printf("Done!\n");
    }
    else if((strcmp(argv[1], "-f") == 0) || (strcmp(argv[1], "-nf") == 0) || (strcmp(argv[1], "/f") == 0) || (strcmp(argv[1], "/nf")) == 0){
        int count = 1, inLeksem = 1;
        char c = ' ';

        while (c != EOF) {
            c = fgetc(fin);
            if(c == '\n' || c == '\t' || c == ' ' || c == EOF) {
                if(inLeksem) {
                    count++;
                    inLeksem = 0;
                }
                if(c != EOF) fputc(c,fout);
            }else{
                inLeksem = 1;
                if(count % 2 == 0){
                    if((count % 5 == 0)){
                        if(isalpha(c)){
                            fprintf(fout, "%d", (int)tolower(c));
                        }
                        else{
                            fprintf(fout, "%d", (int)c);
                        }
                    }else{
                        if(isalpha(c)){
                            fputc(tolower(c), fout);
                        }
                        else{
                            fputc(c, fout);
                        }
                    }
                }
                if((count % 5 == 0) && (count % 2 != 0)) {
                    fprintf(fout, "%d", (int)c);
                }
                if((count % 2 != 0) && (count % 5 != 0)){
                    putc(c,fout);
                }
            }
        }
        printf("Done!\n");
    }
    else{
        printf("Invalid Input: unexpected flag\n");
        fclose(fin);
        fclose(fout);
        if(str_path_checker) free(str_path);
        return 0;
    }
    fclose(fin);
    fclose(fout);
    if(str_path_checker) free(str_path);
}