#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

    // Bubble Sort
    void bubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (arr[j] > arr[j + 1]) {
                        swap(arr[j], arr[j + 1]);
                    }
                }
            }
        }
    


    // Insertion Sort
    void insertionSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
            arr[j + 1] = key;
    }
}

    // Shell Sort
    void shellSort(vector<int>& arr) {
        int n = arr.size();

        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j = i;

            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

                arr[j] = temp;
        }
    }
}

    // Função auxiliar do Quick Sort
    int particionar(vector<int>& arr, int inicio, int fim) {

        int meio = inicio + (fim - inicio) / 2;
        int pivo = arr[meio];

        int i = inicio;
        int j = fim;

        while (i <= j) {

            while (arr[i] < pivo) {
            i++;
        }

        while (arr[j] > pivo) {
            j--;
        }

            if (i <= j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
        }
    }

    return i;
}

    // Quick Sort
    void quickSortRecursivo(vector<int>& arr, int inicio, int fim) {
        if (inicio < fim) {
            int posicaoPivo = particionar(arr, inicio, fim);

            quickSortRecursivo(arr, inicio, posicaoPivo - 1);
            quickSortRecursivo(arr, posicaoPivo, fim);
    }
}

    // Função que será usada pela medição
    void quickSort(vector<int>& arr) {
        if (!arr.empty()) {
            quickSortRecursivo(arr, 0, arr.size() - 1);
    }
}

    // Função auxiliar do Merge Sort
    void intercalar(vector<int>& arr, int inicio, int meio, int fim) {
        vector<int> esquerda;
        vector<int> direita;

        for (int i = inicio; i <= meio; i++) {
            esquerda.push_back(arr[i]);
    }

        for (int i = meio + 1; i <= fim; i++) {
            direita.push_back(arr[i]);
    }

    int i = 0;
    int j = 0;
    int k = inicio;

    while (i < esquerda.size() && j < direita.size()) {
        if (esquerda[i] <= direita[j]) {
            arr[k] = esquerda[i];
            i++;
        } else {
            arr[k] = direita[j];
            j++;
        }
        k++;
    }

    while (i < esquerda.size()) {
        arr[k] = esquerda[i];
        i++;
        k++;
    }

    while (j < direita.size()) {
        arr[k] = direita[j];
        j++;
        k++;
    }
}

    // Merge Sort
    void mergeSortRecursivo(vector<int>& arr, int inicio, int fim) {
        if (inicio < fim) {
            int meio = inicio + (fim - inicio) / 2;

            mergeSortRecursivo(arr, inicio, meio);
            mergeSortRecursivo(arr, meio + 1, fim);

            intercalar(arr, inicio, meio, fim);
    }
}

    // Função que será usada pela medição
    void mergeSort(vector<int>& arr) {
        if (!arr.empty()) {
            mergeSortRecursivo(arr, 0, arr.size() - 1);
    }
}

    // Função para medir tempo
    double medirTempo(void (*algoritmo)(vector<int>&), vector<int> arr) {
        auto inicio = high_resolution_clock::now();
        algoritmo(arr);
        auto fim = high_resolution_clock::now();
        duration<double> duracao = fim - inicio;
    return duracao.count(); // segundos
}

int main() {

    srand(time(0));

    vector<int> tamanhos = {1000, 5000, 10000, 50000, 100000, 200000};

    cout << "=== Arrays Aleatórios ===" << endl;

    // Primeiro caso: arrays aleatórios

    for (int n : tamanhos) {

        vector<int> dados(n);

        for (int i = 0; i < n; i++) {

            dados[i] = rand() % 10501;
        }

        double tempoBubble = medirTempo(bubbleSort, dados);
        double tempoInsertion = medirTempo(insertionSort, dados);
        double tempoShell = medirTempo(shellSort, dados);
        double tempoQuick = medirTempo(quickSort, dados);
        double tempoMerge = medirTempo(mergeSort, dados);

            cout << "n = " << n << endl;
            cout << "Bubble Sort: " << tempoBubble << " s" << endl;
            cout << "Insertion Sort: " << tempoInsertion << " s" << endl;
                cout << "Shell Sort: " << tempoShell << " s" << endl;
            cout << "Quick Sort: " << tempoQuick << " s" << endl;
            cout << "Merge Sort: " << tempoMerge << " s" << endl;
            cout << "-----------------------------" << endl;
    }

    cout << "\n=== Arrays Ja Ordenados ===" << endl;

    // Segundo caso: arrays já ordenados

    for (int n : tamanhos) {

        vector<int> dados(n);

        for (int i = 0; i < n; i++) {

            dados[i] = i;
        }

        double tempoBubble = medirTempo(bubbleSort, dados);
        double tempoInsertion = medirTempo(insertionSort, dados);
        double tempoShell = medirTempo(shellSort, dados);
        double tempoQuick = medirTempo(quickSort, dados);
        double tempoMerge = medirTempo(mergeSort, dados);

            cout << "n = " << n << endl;
            cout << "Bubble Sort: " << tempoBubble << " s" << endl;
            cout << "Insertion Sort: " << tempoInsertion << " s" << endl;
            cout << "Shell Sort: " << tempoShell << " s" << endl;
            cout << "Quick Sort: " << tempoQuick << " s" << endl;
            cout << "Merge Sort: " << tempoMerge << " s" << endl;
            cout << "-----------------------------" << endl;
    }

    return 0;
}
