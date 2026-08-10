
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


    void gerarArray(int arr[], int n) {
        for ( int i = 0; i < n; i++){
            arr[i] = rand() % 15001;
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

    int ehPrimo(int n) {
        if (n < 2) return 0;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
    
}

    void mostrarPrimos(int arr[], int n) {
        printf("Numeros primos encontrados no array:\n");
    for (int i = 0; i < n; i++) {
        if (ehPrimo(arr[i])) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
    
}


int main() {
    int array[10000];
    int n = 10000;
    int opcao;

        srand(time(NULL));

    while (1) {
        printf("1 - Gerar array\n");
        printf("2 - Ordenar array\n");
        printf("3 - Verificar primos\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            gerarArray(array, n);
        } else if (opcao == 2) {
            ordenar(array, n);
        } else if (opcao == 3) {
            mostrarPrimos(array, n);
        }
    }

    return 0;
}


