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
    cout << "n\tBubbleSort(s)\tInsertionSort(s)" << endl;

    // Primeiro caso: arrays aleatórios
    for (int n : tamanhos) {
        vector<int> dados(n);
        for (int i = 0; i < n; i++) {
            dados[i] = rand() % 10501; // valores até 10500
        }

        double tempoBubble = medirTempo(bubbleSort, dados);
        double tempoInsertion = medirTempo(insertionSort, dados);

        cout << n << "\t" << tempoBubble << "\t\t" << tempoInsertion << endl;
    }

    cout << "\n=== Arrays Já Ordenados ===" << endl;
    cout << "n\tBubbleSort(s)\tInsertionSort(s)" << endl;

    // Segundo caso: arrays já ordenados
    for (int n : tamanhos) {
        vector<int> dados(n);
        for (int i = 0; i < n; i++) {
            dados[i] = i; // vetor já ordenado
        }

        double tempoBubble = medirTempo(bubbleSort, dados);
        double tempoInsertion = medirTempo(insertionSort, dados);

        cout << n << "\t" << tempoBubble << "\t\t" << tempoInsertion << endl;
    }

    return 0;
}

