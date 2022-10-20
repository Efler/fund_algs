#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>



char* sum_in_base(int base, int count, ...){
    char* num;
    int len; int len_pr;
    char* res;
    char* p_res;
    char* p;
    char s1, s2, s3;
    int d1, d2, d3, buff, buff_curr;
    int buff_next = 0;

    va_list l;
    va_start(l, count);
    for(int i = count-1; i >= 0; i--){
        if(i == count-1){
            num = va_arg(l, char*);
            len = strlen(num);
            res = (char*)malloc(sizeof(char)*len+1);
            if(!res){
                printf("Malloc error\n");   //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                return 0;
            }
            p_res = res;
            for(int k = len-1; k >= 0; k--){
                *p_res++ = num[k];
            }
            *p_res = 0;
            p_res = res;
        }
        else{
            num = va_arg(l, char*);
            len = strlen(num);
            len_pr = strlen(res);
            if(len > len_pr){
                p = (char*)realloc(res, sizeof(char)*len+1);
                if(!p){
                    printf("Realloc error\n");   //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    free(res);
                    return 0;
                }
                res = p;
                p_res = p;
                *(p_res+len) = '0';
                *(p_res+len+1) = 0;

            }
            for(int k = len-1; k >= 0; k--){
                s1 = *p_res;
                s2 = num[k];
                if((p_res-res) > len){
                    s3 = *p_res;
                }
                else{
                    s3 = '0';
                }

                if(isdigit(s1)) d1 = atoi(&s1);
                else if(isalpha(s1)){
                    d1 = s1 - 55;
                    if(d1 < 10 || d1 > 32){
                        printf("Unexpected number\n");
                        free(res);
                        return 0;
                    }
                }
                else{
                    printf("Unexpected number\n");
                    free(res);
                    return 0;
                }

                if(isdigit(s2)) d2 = atoi(&s2);
                else if(isalpha(s2)){
                    d2 = s2 - 55;
                    if(d2 < 10 || d2 > 32){
                        printf("Unexpected number\n");
                        free(res);
                        return 0;
                    }
                }
                else{
                    printf("Unexpected number\n");
                    free(res);
                    return 0;
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
                    *(p_res+1) = 0;
                }
                else{
                    *p_res++ = buff_curr + 48;
                    *(p_res+1) = 0;
                }
            }
            while(1){
                if(buff_next){
                    if((p_res-res) == len){
                        p = (char*)realloc(res, sizeof(char)*len_pr+1);
                        if(!p){
                            printf("Realloc error\n");   //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                            free(res);
                            return 0;
                        }
                        res = p;
                        p_res = p+len_pr;
                        *p_res = '0';
                        *(p_res+1) = 0;
                        len_pr = strlen(res);
                    }
                    if(isdigit(s1)) d1 = atoi(&s1);
                    else if(isalpha(s1)){
                        d1 = s1 - 55;
                        if(d1 < 10 || d1 > 32){
                            printf("Unexpected number\n");
                            free(res);
                            return 0;
                        }
                    }
                    else{
                        printf("Unexpected number\n");
                        free(res);
                        return 0;
                    }

                    if(isdigit(s2)) d2 = atoi(&s2);
                    else if(isalpha(s2)){
                        d2 = s2 - 55;
                        if(d2 < 10 || d2 > 32){
                            printf("Unexpected number\n");
                            free(res);
                            return 0;
                        }
                    }
                    else{
                        printf("Unexpected number\n");
                        free(res);
                        return 0;
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
                        *(p_res+1) = 0;
                    }
                    else{
                        *p_res++ = buff_curr + 48;
                        *(p_res+1) = 0;
                    }
                }
                else{
                    break;
                }
            }
        }
    }
    va_end(l);
    return res;
}


int main(int argc, char *argv[]){
    char* res = sum_in_base(10, 2, "54321", "11");
    char* p_res = res+strlen(res)-1;
    while(p_res != res){
        printf("%c", *p_res);
        p_res--;
    }
    printf("%c\n", *res);
    free(res);
}