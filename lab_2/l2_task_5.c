#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void swap(int* max, int* min){
    int tmp = *max;
    *max = *min;
    *min = tmp;
}


int main(int argc, char *argv[]){
    srand(time(NULL));
    int size;
    int a, b;
    int act;

    printf("\nEnter a size of array:");
    scanf("%d", &size);
    if(size < 1){
        printf("Unexpected size\n");
        return 0;
    }
    int arr[size];
    printf("Enter the range of numbers [a, b]\na:");
    scanf("%d", &a);
    printf("b:");
    scanf("%d", &b);

    if(a>b){
        printf("\nThe range is invalid, swapping a and b\n");
        swap(&a, &b);
    }

    printf("\nGenerated array:\n");
    for(int i = 0; i < size; i++){
        arr[i] = rand() % (b - a + 1) + a;
        printf("%d ", arr[i]);
    }

    printf("\n\nEnter an action:\n1) Swap min and max elements\n2) Make an array of unique elements\n");
    scanf("%d", &act);
    if(act == 1){
        int max = 0, min = 0;
        for(int i = 0; i < size; i++){
            if(arr[i] > arr[max]) max = i;
            if(arr[i] < arr[min]) min = i;
        }
        swap(&arr[max], &arr[min]); // arr + max
        printf("\nSwapped min and max:\n");
        for(int i = 0; i < size; i++){
            printf("%d ", arr[i]);
        }
    }
    else if(act == 2){
        int arr2[size];
        int count = 0;
        for(int i = 0; i < size; i++){
            int checker = 1;
            for(int k = 0; k < size; k++){
                if(arr[i] == arr2[k]){
                    checker = 0;
                    break;
                }
            }
            if(checker){
                arr2[count++] = arr[i];
            }
        }
        printf("\nArray of unique elements:\n");
        for(int i = 0; i < count; i++){
            printf("%d ", arr2[i]);
        }
    }
    else{
        printf("Unexpected action\n");
        return 0;
    }
}