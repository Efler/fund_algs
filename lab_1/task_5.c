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

        FILE* fin = fopen(argv[2], "r");
        if(!fin){
            printf("File Error: could not open file\n");
            return 0;
        }
        FILE* fout = fopen("D:\\JetBrains\\tester_files_(yan)\\result_task_5.txt", "w");
        if(!fout){
            printf("File Error: could not open file\n");
            fclose(fin);
            return 0;
        }


        while(c != EOF){
            c = 0;
            buff = dynamic_string(&k);
            if(buff == 0){
                printf("Malloc Error\n");
                fclose(fin);
                fclose(fout);
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
                        return 0;
                    }
                }

                if((c == ' ') || (c == '\n') || (c==EOF)){
                    if(c == EOF) e = 1;
                    *(p_buff-1) = 0;
                    k = 16;
                    printf("%s\n", buff);
                    FILE* fp = fopen(buff, "r");
                    if(!fp){
                        printf("File Error: could not open file\n");
                        fclose(fin);
                        fclose(fout);
                        free(buff);
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
        printf("Flag -fi: done!\n");













    }else if(strcmp(argv[1], "-cin") == 0){
        printf("Soon...");
    }else if(strcmp(argv[1], "-arg") == 0){
        printf("Soon...");
    }else{
        printf("Invalid Flag: unexpected flag\n");
        return 0;
    }
}
