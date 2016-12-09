#include <stdio.h>
#include <string.h>

#include <iostream>

#include <limits.h>
#define INFINITO INT_MAX

using namespace std;

void WordWrap();
void imprimeResultado (int* posicao, int n, char** palavra);

void DEBUG(int L, int N, char** palavras, int* tamPal, int** espacoEntre, int** custoLinha, int* custo, int* anterior);

int main(){
    WordWrap();

    return 0;
}

void WordWrap(){
    int L;              // Tamanho máximo de uma linha
    int N;              // Nº de palavras

    char**  palavras;   // Array de palavras
    int*    tamPal;     // Array com o tamanho de cada palavra

    int*    custo;          // Custo do subproblema '0' a 'i'
    int*    posicao;        // Usada para calcular a linha em que cada palavra está presente

    // Lê tamanho da linha e nº de palavras
    scanf("%d%d", &L, &N);

    // Inicializar estruturas
    palavras = new char*[N];
    tamPal   = new int[N];

    custo   = new int[N+1];
    posicao = new int[N];

    for (int i = 0; i < N; i++){
        // Lê palavra da entrada e conta o nº de letras
        palavras[i] = new char[L+1];

        scanf("%s%n", palavras[i], &tamPal[i]);
        tamPal[i]--;
    }

    // Calcular vetor 'custo'
    custo[0] = 0;
    for (int j = 0; j < N; j++){
        custo[j+1] = INFINITO;

        for (int i = 0; i <= j; i++){
            // Calcula quantos espaços haveria no fim de uma linha formada pelas palavras de 'i' a 'j'
            int espacoEntre = 0;

            for (int n = i; n <= j; n++) espacoEntre -= tamPal[n];
            espacoEntre += L - (j - i);

            // Calcula o custo de uma linha formada pelas palavras de 'i' a 'j'
            int custoLinha;

            if (espacoEntre < 0)                      custoLinha = INFINITO;
            else if (j == (N-1) && espacoEntre >= 0)  custoLinha = 0;
            else                                      custoLinha = espacoEntre*espacoEntre;


            //
            if (custo[i] != INFINITO &&
                custoLinha != INFINITO &&
                (custo[i] + custoLinha < custo[j+1]))
            {
                custo[j+1] = custo[i] + custoLinha;
                posicao[j] = i;
            }
        }
    }

    // Imprimir resultado
    imprimeResultado(posicao, N-1, palavras);

    //DEBUG(L, N, palavras, tamPal, espacoEntre, CustoLinha, custo, posicao);
}

void imprimeResultado (int* posicao, int n, char** palavra){
    if (posicao[n] != 0)
        imprimeResultado (posicao, posicao[n]-1, palavra);

    for (int i = posicao[n]; i <= n; i++){
        printf("%s", palavra[i]);

        if (i < n)  printf(" ");
        else        printf("\n");
    }
}


/*/void DEBUG(int L, int N, char** palavras, int* tamPal, int** espacoEntre, int** custoLinha, int* custo, int* anterior){
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
*/
