#include <stdio.h>
#define MAX 301

void le_matriz (char M[][MAX], int l, int c);
void printa_matriz(char M[][MAX], int l, int c);
int procura_palavra (char palavra[], char M[][MAX], int l, int c);
int contar(char palavra[]);


int main(){
    int linhas, colunas, palavras;
    scanf("%d %d %d", &linhas, &colunas, &palavras);
    char quadro[MAX][MAX];
    le_matriz(quadro, linhas, colunas);
    int i;
    char palavra[MAX];
     for (i = 0; i < palavras; i++){
        scanf("%s", palavra);
        if (procura_palavra(palavra, quadro, linhas, colunas) == 0){
            printf("A palavra %s está no texto!\n", palavra);
        } else {
            printf("A palavra %s não está no texto!\n", palavra);
        }
    }
    return 0;
}


//leitor/criador de matrizes
void le_matriz (char M[][MAX], int l, int c) {
    int i, j;
    for (i = 0; i < l; i++){
        for (j = 0; j < c; j++){
            scanf("%s", &M[i][j]);
        }
    }
}


int procura_palavra(char palavra[], char M[][MAX], int l, int c){
    int k, i, j, tamanho, aux = 0, f;
    tamanho = contar(palavra);
    for (i = 0; i < l;i++){
        for (j = 0; j < c; j++){
            if (palavra[0] == M[i][j]){
                //procura na direita
                if (j != c-1 && aux != tamanho){ //se n for a último coluna
                    aux = 1;
                    k = 0;
                    f = j;
                    while (f+1 <= c && aux != tamanho && palavra[k+1] == M[i][f+1]){
                        aux++;
                        k++;
                        f++;
                    }
                }
                //procura em cima
                if (i != 0 && aux != tamanho) { //se n for a primeira linha
                    aux = 1;
                    k = 0;
                    f = i;
                    while (f-1 >= 0 && aux != tamanho && palavra[k+1] == M[f-1][j]){
                        aux++;
                        k++;
                        f--;
                    }
                }
                //procura na esquerda
                if (j != 0 && aux != tamanho) { //se n for a primeira coluna
                    aux = 1;
                    k = 0;
                    f = j;
                    while (f-1 >= 0 && aux != tamanho && palavra[k+1] == M[i][f-1]){
                        aux++;
                        k++;
                        f--;
                    }
                }
                //procura em baixo
                if (i != l-1 && aux != tamanho) { //se n for a ultima linha
                    aux = 1;
                    k = 0;
                    f = i;
                    while (f+1 <= l && aux != tamanho && palavra[k+1] == M[f+1][j]){ // ta aqui o problema do valgrind!!!!!!
                        aux++;
                        k++;
                        f++;
                    }
                }
            if (aux == tamanho) {
                return 0;
            }
            }
        }
    }
    return 69;
}


int contar(char palavra[]){
    int aux = 0, i;
    for(i = 0; palavra[i] != '\0'; i++){
        aux++;
    }
    return aux;
}