#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esteira.h"

p_esteira cria_esteira(int tamanho){
    p_esteira e;
    e = malloc(sizeof(struct esteira));
    e->vetor = malloc(tamanho * sizeof(struct esteira));
    e->ini = 0;
    e->fim = 0;
    e->tamanho = tamanho;
    e->usado = 0;
    e->entrou = FALSE;
    return e;
}

void libera_esteira(p_esteira esteira){
    int i;
    /*teoricamente esse for nunca vai ser usado, pq a esteira
      vai estar livre no fim do loop*/
    if (esteira->usado > 0){
        for (i = 0; i < esteira->usado; i++){
            libera_peca(esteira->vetor[i]);
        }
    }
    free(esteira->vetor);
    free(esteira);
}

void enfileira(p_esteira esteira) {
    p_peca peca  = cria_peca();
    esteira->vetor[esteira->fim] = peca;
    esteira->fim = (esteira->fim + 1) % esteira->tamanho;
    esteira->usado++;
}

p_peca desenfileira(p_esteira esteira) {
    p_peca peca = esteira->vetor[esteira->ini];
    esteira->ini = (esteira->ini + 1) % esteira->tamanho;
    esteira->usado --;
    return peca;
}