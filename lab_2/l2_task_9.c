#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>



char* sum_in_base(int base, int count, ...){
    va_list l;
    va_start(l, count);
    char* res = (char*)malloc(sizeof(char)*4);
    if(!res){
        printf("Malloc error\n");   //!!!!!!!!!!!!!!!!!!!!!!!!!!!
        return 0;
    }







    va_end(l);
}


int main(int argc, char *argv[]){

}