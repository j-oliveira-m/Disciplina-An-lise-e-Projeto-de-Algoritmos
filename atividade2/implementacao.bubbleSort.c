#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000

    void gerarArray(int arr[], int n) {
        for ( int i = 0; i < n; i++){
            arr[i] = rand() % 10500;
        }
           printf("Array gerado:\n");

        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }



    void ordenar(int arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Array ordenado (ordem crescente):\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
}


int main() {

    int n;
    scanf("%d", &n);

    int array[n];


        srand(time(NULL));



    return 0;
}