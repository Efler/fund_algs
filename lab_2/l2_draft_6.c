#include <stdio.h>
#include <stdarg.h>
#include <string.h>


typedef struct path_matches1{
    int checker;
    int matches;
    char* path;
} path_matches1;


path_matches1* matches_in_files(char str[], int count_files, ...){
    va_list l;
    va_start(l, count_files);
    int len = strlen(str);
    char c;
    path_matches1 res[count_files-1];

    for(int i = 0; i < count_files; i++){
        char* file_name = va_arg(l, char*);
        FILE* fin = fopen(file_name, "r");
        if(!fin){
            printf("File Error: could not open file\n");
            res[i].checker = 0;
            res[i].matches = 0;
            res[i].path = file_name;
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
//        printf("Substring '%s' in file '%s' ---> %d matches\n", str, file_name, matches);
        res[i].checker = 1;
        res[i].matches = matches;
        res[i].path = file_name;
        fclose(fin);
    }
    return res;
}


int main(int argc, char *argv[]){
    printf("\n");
    int count_files = 3;
    char path1[] = "D:\\JetBrains\\tester_files_(yan)\\l2_task_6_tester1.txt";
    char path2[] = "D:\\JetBrains\\tester_files_(yan)\\l2_task_6_tester2.txt";
    char path3[] = "D:\\JetBrains\\tester_files_(yan)\\l2_task_6_tester3.txt";
    path_matches1 res[count_files-1];
    res = matches_in_files("33", count_files, path1, path2, path3);
    printf("%d", res[1].matches);
}