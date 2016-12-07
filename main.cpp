#include <iostream>

#include <limits.h>
#define INFINITO INT_MAX

using namespace std;

void WordWrap();
int imprimeResultado (int* posicao, int n, string* palavra);

void DEBUG(int L, int N, string* palavras, int* tamPal, int** espacoEntre, int** custoLinha, int* custo, int* anterior);

int main(){
    WordWrap();

    return 0;
}

void WordWrap(){
    int L;              // Tamanho máximo de uma linha
    int N;              // Nº de palavras

    string* palavras;   // Array de palavras
    int*    tamPal;     // Array com o tamanho de cada palavra

    int**   espacoEntre;    // Espaços vazios no fim de uma linha formada pelas palavras de 'i' a 'j'
    int**   custoLinha;     // Custo de uma linha formada pelas palavras de 'i' a 'j'
    int*    custo;          // Custo do subproblema '0' a 'i'
    int*    posicao;       //

    // Entrada de dados
    cin >> L;
    cin >> N;

    palavras = new string[N];
    tamPal = new int[N];

    for (int i = 0; i < N; i++){
        cin >> palavras[i];
        tamPal[i] = palavras[i].length();
    }

    // Inicializar estruturas auxiliares
    espacoEntre = new int*[N];
    custoLinha  = new int*[N];

    custo   = new int[N+1];
    posicao = new int[N];

    for (int i = 0; i < N; i++){
        espacoEntre[i]  = new int[N-i];
        custoLinha[i]   = new int[N-i];
    }

    // Calcular matriz 'espacoEntre'
    for (int i = 0; i < N; i++){
        espacoEntre[i][i] = L - tamPal[i];
        for (int j = i+1; j < N; j++)
            espacoEntre[i][j] = espacoEntre[i][j-1] - tamPal[j] - 1;
    }

    // Calcular matriz 'custoLinha'
    for (int i = 0; i < N; i++){
        for (int j = i; j <= N; j++){
            if (espacoEntre[i][j] < 0)                      custoLinha[i][j] = INFINITO;
            else if (j == (N-1) && espacoEntre[i][j] >= 0)  custoLinha[i][j] = 0;
            else                                            custoLinha[i][j] = espacoEntre[i][j]*espacoEntre[i][j];
        }
    }

    // Calcular vetor 'custo'
    custo[0] = 0;
    for (int j = 0; j < N; j++){
        custo[j+1] = INFINITO;

        for (int i = 0; i <= j; i++){
            if (custo[i] != INFINITO &&
                custoLinha[i][j] != INFINITO &&
                (custo[i] + custoLinha[i][j] < custo[j+1]))
            {
                custo[j+1] = custo[i] + custoLinha[i][j];
                posicao[j] = i;
            }
        }
    }

    // Imprimir resultado
    imprimeResultado(posicao, N-1, palavras);

    //DEBUG(L, N, palavras, tamPal, espacoEntre, custoLinha, custo, posicao);
}

int imprimeResultado (int* posicao, int n, string* palavra){
    int k;
    if (posicao[n] == 0)
        k = 0;
    else
        k = imprimeResultado (posicao, posicao[n]-1, palavra) + 1;

    for (int i = posicao[n]; i <= n; i++){
        cout << palavra[i];

        if (i < n)  cout << ' ';
        else        cout << '\n';
    }

    return k;
}

void DEBUG(int L, int N, string* palavras, int* tamPal, int** espacoEntre, int** custoLinha, int* custo, int* anterior){
    cout << "\nL: " << L << "\nn: " << N << "\n\nPalavras:\n";
    for (int i = 0; i < N; i++){
        cout << palavras[i] << "\n";
    }

    cout << "\nTamanho das palavras: ";
    for (int i = 0; i < N; i++){
        cout << tamPal[i] << "  ";
    }

    cout << "\n\nEspaço entre:\n";
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (j >= i) cout << espacoEntre[i][j] << "\t";
            else        cout << "-\t";
        }
        cout << "\n";
    }

    cout << "\nCusto Linha:\n";
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (custoLinha[i][j] == INFINITO) cout << "(inf)\t";

            else if (j >= i)    cout << custoLinha[i][j] << "\t";
            else                cout << "-\t";
        }
        cout << "\n";
    }

    cout << "\nCusto: ";
    for (int i = 0; i <= N; i++){
        cout << custo[i] << "  ";
    }

    cout << "\nAnterior: ";
    for (int i = 0; i < N; i++){
        cout << anterior[i] << "  ";
    }
}
