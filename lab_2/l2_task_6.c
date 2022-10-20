#include <stdio.h>
#include <stdarg.h>
#include <string.h>


typedef struct path_matches{
    int checker;
    int matches;
    char* path;
} path_matches;


void matches_in_files(path_matches res[], char str[], int count_files, ...){
    va_list l;
    va_start(l, count_files);
    int len = strlen(str);
    char c;

    for(int i = 0; i < count_files; i++){
        char* file_name = va_arg(l, char*);
        FILE* fin = fopen(file_name, "r");
        if(!fin){
            printf("File Error: could not open file\n");
            res[i].checker = 0;
            res[i].matches = 0;
            res[i].path = file_name;
            continue;
        }
        int index = 0;
        int good_symbols = 0;
        int checker = 0;
        int matches = 0;
        while((c = fgetc(fin)) != EOF){
            if(c == str[index]){
                good_symbols++;
                checker = 1;
                index++;
                if(good_symbols == len){
                    matches++;
                    good_symbols = 0;
                    checker = 0;
                    index = 0;
                }
            }else{
                if(checker){
                    good_symbols = 0;
                    checker = 0;
                    index = 0;
                }
            }
        }
        res[i].checker = 1;
        res[i].matches = matches;
        res[i].path = file_name;
        fclose(fin);
    }
}


int main(int argc, char *argv[]){
    printf("\n");

    int count_files = 3;
    char path1[] = "D:\\JetBrains\\tester_files_(yan)\\l2_task_6_tester1.txt";
    char path2[] = "D:\\JetBrains\\tester_files_(yan)\\l2_task_6_tester2.txt";
    char path3[] = "D:\\JetBrains\\tester_files_(yan)\\l2_task_6_tester3.txt";
    char str[] = "33";

    path_matches res[count_files];
    matches_in_files(res, str, count_files, path1, path2, path3);
    for(int i = 0; i < count_files; i++){
        if(res[i].checker){
            printf("Substring '%s' in file '%s' ---> %d matches\n", str, res[i].path, res[i].matches);
        }
        else{
            printf("Substring '%s' in file '%s' ---> could not open a file\n", str, res[i].path);
        }
    }
}