#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
 
using namespace std;
using namespace std::chrono;
 
// Um intervalo e so um par de numeros: onde comeca e onde termina.
struct Intervalo {
    long long inicio, fim;
};
 
// ---------------------------------------------------------------------------
// PASSO 1: ORDENAR OS INTERVALOS PELO INICIO (Merge Sort)
// Por que ordenar? Com os intervalos em ordem, os candidatos de cada passo ficam
// um ao lado do outro e basta percorrer a lista UMA vez, sem voltar.
// O Merge Sort divide a lista ao meio, ordena cada metade e junta as duas.
// ---------------------------------------------------------------------------
 
// Junta duas metades que ja estao ordenadas.
void intercalar(vector<Intervalo>& v, int inicio, int meio, int fim) {
    vector<Intervalo> esquerda, direita;
    for (int i = inicio; i <= meio; i++) esquerda.push_back(v[i]);
    for (int i = meio + 1; i <= fim; i++) direita.push_back(v[i]);
 
    int i = 0, j = 0, k = inicio;
 
    // Pega sempre o menor entre o primeiro da esquerda e o primeiro da direita.
    while (i < (int)esquerda.size() && j < (int)direita.size()) {
        if (esquerda[i].inicio <= direita[j].inicio) v[k++] = esquerda[i++];
        else v[k++] = direita[j++];
    }
    // Copia o que sobrou de qualquer uma das metades.
    while (i < (int)esquerda.size()) v[k++] = esquerda[i++];
    while (j < (int)direita.size()) v[k++] = direita[j++];
}
 
void mergeSort(vector<Intervalo>& v, int inicio, int fim) {
    if (inicio >= fim) return;  // 0 ou 1 elemento: ja esta ordenado
    int meio = inicio + (fim - inicio) / 2;
    mergeSort(v, inicio, meio);        // ordena a metade da esquerda
    mergeSort(v, meio + 1, fim);       // ordena a metade da direita
    intercalar(v, inicio, meio, fim);  // junta as duas
}
 
int coberturaGulosa(vector<Intervalo> v, long long alvoInicio, long long alvoFim,
                    vector<Intervalo>& solucao, bool mostrarPassos) {
    // 'v' chega como copia, entao ordenar aqui nao mexe na lista original.
    mergeSort(v, 0, (int)v.size() - 1);
    solucao.clear();
 
    long long coberto = alvoInicio;  // ate onde ja cobrimos
    int i = 0;                       // proximo intervalo a olhar (nunca volta para tras)
    int passo = 1;
 
    while (coberto < alvoFim) {
        long long melhorFim = coberto;  // ate onde o melhor candidato chega
        Intervalo melhor = {0, 0};
 
        // Olha todos os candidatos: os que comecam em 'coberto' ou antes.
        while (i < (int)v.size() && v[i].inicio <= coberto) {
            if (mostrarPassos) {
                cout << "   candidato [" << v[i].inicio << ", " << v[i].fim << "]" << endl;
            }
            if (v[i].fim > melhorFim) {  // este vai mais longe que o melhor ate agora?
                melhorFim = v[i].fim;
                melhor = v[i];
            }
            i++;  // quem nao foi escolhido e descartado de vez
        }
 
        // Ninguem passa de 'coberto': existe um buraco, entao e impossivel.
        if (melhorFim == coberto) {
            if (mostrarPassos) cout << "   nenhum candidato passa de " << coberto << ": ha um buraco" << endl;
            solucao.clear();
            return -1;
        }
 
        if (mostrarPassos) {
            cout << "Passo " << passo << ": cobertura em " << coberto << " -> escolhe ["
                 << melhor.inicio << ", " << melhor.fim << "]" << endl;
        }
        solucao.push_back(melhor);  // escolhe o melhor
        coberto = melhorFim;        // agora cobrimos ate o fim dele
        passo++;
    }
    return (int)solucao.size();
}

 
// Sorteia um numero entre minimo e maximo.
long long sorteia(long long minimo, long long maximo) {
    long long parteAlta = rand();
    long long parteBaixa = rand();
    long long numero = parteAlta * ((long long)RAND_MAX + 1) + parteBaixa;
    return minimo + numero % (maximo - minimo + 1);
}
 
// Cria n intervalos com inicio perto do alvo e tamanho entre 1 e tamanhoMax.
// A mesma semente gera sempre os mesmos intervalos (teste reproduzivel).
vector<Intervalo> gerarAleatorio(int n, long long alvoInicio, long long alvoFim,
                                 long long tamanhoMax, unsigned int semente) {
    srand(semente);
    vector<Intervalo> v(n);
    for (int k = 0; k < n; k++) {
        v[k].inicio = sorteia(alvoInicio - tamanhoMax, alvoFim);
        v[k].fim = v[k].inicio + sorteia(1, tamanhoMax);
    }
    return v;
}
 

// CONFERe SE UMA SOLUCAO ESTA CERTA: os intervalos escolhidos realmente cobrem
// o alvo inteiro, sem buracos? (usa a mesma ideia: ordenar e seguir em frente)

bool solucaoCobreAlvo(vector<Intervalo> solucao, long long alvoInicio, long long alvoFim) {
    if (solucao.empty()) return false;
    mergeSort(solucao, 0, (int)solucao.size() - 1);
    long long coberto = alvoInicio;
    for (size_t k = 0; k < solucao.size(); k++) {
        if (solucao[k].inicio > coberto) return false;  // buraco antes deste intervalo
        if (solucao[k].fim > coberto) coberto = solucao[k].fim;
    }
    return coberto >= alvoFim;
}
 

// EXECUTAR UM CASO: mostra a entrada, roda o algoritmo, mede o tempo e mostra


void executar(const string& nome, const vector<Intervalo>& v, long long alvoInicio,
              long long alvoFim, bool mostrarPassos, const string& arquivoSaida = "") {
    cout << "\n=== " << nome << " ===" << endl;
    cout << "Alvo: [" << alvoInicio << ", " << alvoFim << "]" << endl;
    cout << "Intervalos (" << v.size() << ")";
    if (v.size() <= 15) {  // so lista quando e pouco
        cout << ":";
        for (size_t k = 0; k < v.size(); k++) cout << " [" << v[k].inicio << "," << v[k].fim << "]";
    }
    cout << endl;
 
    vector<Intervalo> solucao;
    auto antes = high_resolution_clock::now();
    int qtd = coberturaGulosa(v, alvoInicio, alvoFim, solucao, mostrarPassos);
    auto depois = high_resolution_clock::now();
    duration<double, milli> tempo = depois - antes;
 
    if (qtd < 0) {
        cout << "Resultado: NAO existe cobertura." << endl;
    } else {
        cout << "Resultado: " << qtd << " intervalos escolhidos" << endl;
        if (qtd <= 50) {  // poucos: mostra todos na tela
            for (int k = 0; k < qtd; k++) {
                cout << " [" << solucao[k].inicio << "," << solucao[k].fim << "]";
            }
            cout << endl;
        } else {  // muitos: mostra so os 10 primeiros
            for (int k = 0; k < 10; k++) {
                cout << " [" << solucao[k].inicio << "," << solucao[k].fim << "]";
            }
            cout << " ..." << endl;
        }
        cout << "Cobertura valida? " << (solucaoCobreAlvo(solucao, alvoInicio, alvoFim) ? "sim" : "NAO") << endl;
 
        if (arquivoSaida != "") {  // salva a lista completa
            ofstream arq(arquivoSaida.c_str());
            arq << "Alvo [" << alvoInicio << ", " << alvoFim << "] - " << qtd << " intervalos escolhidos\n";
            for (int k = 0; k < qtd; k++) {
                arq << (k + 1) << ": [" << solucao[k].inicio << ", " << solucao[k].fim << "]\n";
            }
            cout << "Lista completa salva em: " << arquivoSaida << endl;
        }
    }
    cout << "Tempo: " << tempo.count() << " ms" << endl;
}
 

// VALIDACAO: 
// FORCA BRUTA

int minimoForcaBruta(const vector<Intervalo>& v, long long alvoInicio, long long alvoFim) {
    int n = (int)v.size();
    int melhor = -1;  // -1 = ainda nao achou nenhuma cobertura
    for (int mascara = 1; mascara < (1 << n); mascara++) {  // cada mascara = um subconjunto
        vector<Intervalo> subconjunto;
        for (int k = 0; k < n; k++) {
            if (mascara & (1 << k)) subconjunto.push_back(v[k]);
        }
        int qtd = (int)subconjunto.size();
        if ((melhor == -1 || qtd < melhor) && solucaoCobreAlvo(subconjunto, alvoInicio, alvoFim)) {
            melhor = qtd;
        }
    }
    return melhor;
}
 
void validarAlgoritmo() {
    int semCobertura = 0, divergencias = 0;
    for (unsigned int semente = 1; semente <= 300; semente++) {
        vector<Intervalo> v = gerarAleatorio(12, 0, 10, 5, semente);
        vector<Intervalo> solucao;
        int guloso = coberturaGulosa(v, 0, 10, solucao, false);
        int bruto = minimoForcaBruta(v, 0, 10);
        if (bruto == -1) semCobertura++;
        if (guloso != bruto) divergencias++;
    }
    cout << "\n=== Validacao: guloso x forca bruta (300 casos, 12 intervalos cada) ===" << endl;
    cout << "Casos sem cobertura possivel: " << semCobertura << endl;
    cout << "Casos em que guloso e forca bruta discordaram: " << divergencias << endl;
}
 
// ---------------------------------------------------------------------------
// AS OPCOES DO MENU
// ---------------------------------------------------------------------------
 
// Opcao 1: dois exemplos prontos, sem digitar nada.
void exemplosProntos() {
    vector<Intervalo> comSolucao = {{0, 3}, {2, 6}, {1, 4}, {5, 9}, {6, 10}, {8, 12}, {4, 5}};
    executar("Exemplo 1 - com solucao", comSolucao, 0, 12, true);
 
    vector<Intervalo> semSolucao = {{0, 4}, {6, 10}};  // buraco entre 4 e 6
    executar("Exemplo 2 - sem solucao", semSolucao, 0, 10, true);
}
 
// Opcao 2: voce digita o alvo e os intervalos, um por linha.
void digitarCaso() {
    long long alvoInicio, alvoFim;
    cout << "\nO alvo e o trecho que queremos cobrir.\n";
    cout << "Digite onde ele COMECA e onde TERMINA (ex.: 0 12): ";
    if (!(cin >> alvoInicio >> alvoFim) || alvoInicio >= alvoFim) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Valores invalidos: o comeco precisa ser menor que o fim." << endl;
        return;
    }
 
    cout << "Agora digite os intervalos, um por linha: inicio fim (ex.: 2 6).\n";
    cout << "Quando terminar, digite 0 0.\n";
    vector<Intervalo> v;
    while (true) {
        Intervalo novo;
        cout << "> ";
        if (!(cin >> novo.inicio >> novo.fim)) {
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        if (novo.inicio == 0 && novo.fim == 0) break;  // terminou
        if (novo.inicio > novo.fim) {
            cout << "O inicio nao pode ser maior que o fim. Tente de novo." << endl;
            continue;
        }
        v.push_back(novo);
    }
    if (v.empty()) {
        cout << "Nenhum intervalo digitado." << endl;
        return;
    }
    executar("Caso digitado", v, alvoInicio, alvoFim, true);
}
 
// Opcao 3: voce so escolhe a quantidade; o programa sorteia os intervalos.
// O alvo e [0, 2 x quantidade].
void gerarCaso() {
    int n;
    cout << "\nQuantos intervalos quer gerar? ";
    if (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Quantidade invalida." << endl;
        return;
    }
    long long alvoFim = 2LL * n;
    vector<Intervalo> v = gerarAleatorio(n, 0, alvoFim, 20, (unsigned int)time(0));
    executar("Caso aleatorio", v, 0, alvoFim, n <= 15);
}
 
// Opcao 4: os tres testes do relatorio (pequeno, medio e grande).
void rodarTestes() {
    vector<Intervalo> pequeno = {{0, 3}, {2, 6}, {1, 4}, {5, 9}, {6, 10}, {8, 12}, {4, 5}};
    executar("Teste 1 - Pequeno", pequeno, 0, 12, true);
    executar("Teste 2 - Medio", gerarAleatorio(1000, 0, 2000, 100, 42), 0, 2000, false, "solucao_teste2.txt");
    executar("Teste 3 - Grande", gerarAleatorio(1000000, 0, 1000000, 50, 7), 0, 1000000, false, "solucao_teste3.txt");
}
 
int main() {
    while (true) {
        cout << "\n=== Cobertura de Intervalos (algoritmo guloso) ===" << endl;
        cout << "1 - Ver exemplos prontos (com os passos na tela)" << endl;
        cout << "2 - Digitar meu proprio caso" << endl;
        cout << "3 - Gerar intervalos aleatorios (eu escolho a quantidade)" << endl;
        cout << "4 - Rodar os testes (pequeno, medio e grande)" << endl;
        cout << "5 - Validar o algoritmo (guloso x forca bruta)" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: ";
 
        int opcao;
        if (!(cin >> opcao) || opcao == 0) break;
 
        if (opcao == 1) exemplosProntos();
        else if (opcao == 2) digitarCaso();
        else if (opcao == 3) gerarCaso();
        else if (opcao == 4) rodarTestes();
        else if (opcao == 5) validarAlgoritmo();
        else cout << "Opcao invalida." << endl;
    }
    return 0;
}