#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>


char* sum_in_base(int base, int count, ...){
    char* res;
    char* p_res;
    char* num;
    int len, len_pr;
    char s1, s2;
    int d1, d2, buff, buff_curr;
    int buff_next = 0;

    va_list l;
    va_start(l, count);
    for(int i = 0; i < count; i++){
        if(!i){
            num = va_arg(l, char*);
            len = strlen(num);
            res = (char*)malloc(sizeof(char)*len+2);
            if(!res){
                free(res);
                return NULL;
            }
            p_res = res;
            for(int k = len-1; k >= 0; k--){
                *p_res++ = num[k];
            }
            *p_res++ = '0';
            *p_res = 0;
            p_res = res;
        }
        else{
            num = va_arg(l, char*);
            len = strlen(num);
            len_pr = strlen(res);
            if((len_pr-len) <= 0){
                char* p = (char*)realloc(res, sizeof(char)*len+2);
                if(!p){
                    free(res);
                    return NULL;
                }
                res = p;
                p_res = p;
                for(int s = (len_pr); s < (len+2); s++){
                    if(s != (len+1)) {
                        *(p_res + s) = '0';
                    }
                    else *(p_res + s) = 0;
                }
            }
            for(int k = len-1; k >= 0; k--){
                s1 = *p_res;
                s2 = num[k];

                if(isdigit(s1)) d1 = s1-48;
                else if(isalpha(s1)){
                    d1 = s1 - 55;
                    if(d1 < 10 || d1 >= base){
                        free(res);
                        return NULL;
                    }
                }
                else{
                    free(res);
                    return NULL;
                }

                if(isdigit(s2)) d2 = s2 - 48;
                else if(isalpha(s2)){
                    d2 = s2 - 55;
                    if(d2 < 10 || d2 >= base){
                        free(res);
                        return NULL;
                    }
                }
                else{
                    free(res);
                    return NULL;
                }

                buff = d1+d2+buff_next;
                if(buff >= base){
                    buff_curr = buff % base;
                    buff_next = buff / base;
                }
                else{
                    buff_curr = buff;
                    buff_next = 0;
                }
                if(buff_curr > 9){
                    *p_res++ = buff_curr + 55;
                }
                else{
                    *p_res++ = buff_curr + 48;
                }
            }
            while(buff_next){
                s1 = *p_res;
                if(isdigit(s1)) d1 = s1-48;
                else if(isalpha(s1)){
                    d1 = s1 - 55;
                    if(d1 < 10 || d1 >= base){
                        free(res);
                        return NULL;
                    }
                }
                else{
                    free(res);
                    return NULL;
                }

                buff = d1+buff_next;
                if(buff >= base){
                    buff_curr = buff % base;
                    buff_next = buff / base;
                }
                else{
                    buff_curr = buff;
                    buff_next = 0;
                }
                if(buff_curr > 9){
                    *p_res++ = buff_curr + 55;
                }
                else{
                    *p_res++ = buff_curr + 48;
                }
            }
            p_res = res;
        }
    }
    va_end(l);
    return res;
}


int main(int argc, char *argv[]){

    int base = 16;
    char* res = sum_in_base(base, 3, "16A", "B2", "39D");
    printf("\nSum in base %d: ", base);
    if(!res){
        printf("ERROR\n");
        return 0;
    }
    int len = strlen(res);
    char* p_res = res + len - 1;
    while(p_res != res){
        if(p_res == res + len - 1 && *p_res == '0'){
            p_res--;
            continue;
        }else{
            printf("%c", *p_res--);
        }
    }
    printf("%c\n", *res);
}