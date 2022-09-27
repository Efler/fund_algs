#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[]){
    FILE* fin;
    FILE* fout;

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

        fin = fopen(argv[2], "r");
        if(fin == NULL){
            printf("File Error: could not open file\n");
            return 0;
        }


        char fout_prename[] = "out_";
        int count_name = 0;
        int i = strlen(argv[2]) - 1;
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
        int l = 0;
        for(; count_name > 0; count_name--){
            str_name[m] = argv[2][e];
            e++; m++;
        }
        int r = strlen(argv[2])+5;
        char str_path[r];
        for(; l <= i; l++){
            str_path[l] = argv[2][l];
        }
        m = 0;
        r = l + 4;
        for(; l<r; l++){
            str_path[l] = fout_prename[m];
            m++;
        }
        m = 0;
        r = l + strlen(str_name);
        for(; l < r; l++){
            str_path[l] = str_name[m];
            m++;
        }
        str_path[l] = 0;


        fout = fopen(str_path, "w");
        if(fout == NULL){
            printf("File Error: could not open file\n");
            fclose(fin);
            return 0;
        }


    }else if((strlen(argv[1]) == 3) && (argv[1][1] == 'n')){
        if(argc != 4){
            printf("Invalid Input: wrong number of arguments\n");
            return 0;
        }
        fin = fopen(argv[2], "r");
        if(fin == NULL){
            printf("File Error: could not open file\n");
            return 0;
        }
        fout = fopen(argv[3], "w");
        if(fout == NULL){
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
                fprintf(fout, "Sum of special symbols in the line #%d: %d\n", count_line, count);
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
            if(isdigit(c) || c == '\n'){
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
        return 0;
    }
    fclose(fin);
    fclose(fout);
}