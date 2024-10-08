#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

p_pilha cria_pilha(int tamanho){
    p_pilha p;
    p = malloc(sizeof(struct pilha));
    p->usado = 0;
    p->tamanho = tamanho;
    p->topo = NULL;
    p->entrou = FALSE;
    return p;
}

void libera_pilha(p_no no){
    if (no != NULL) {
        libera_pilha(no->prox);
    //free(no->peca); é pra n ter peça nenhuma qnd isso fou usado
    free(no);
    }
}

void empilhar(p_pilha pilha , p_peca peca) {
    if (pilha->usado < pilha->tamanho){
        p_no novo = malloc(sizeof(struct no));
        novo->peca = peca;
        novo->prox = pilha->topo;
        pilha->topo = novo;
        pilha->usado++;
    } else {
        //cpa vai ter q fzr algo qnd tiver cheia
    }
}

void desempilha(p_pilha pilha, p_trabalhador embalador){
    p_no aux;
    embalador->ocupado = 1;
    embalador->peca = pilha->topo->peca;
    embalador->tempo = pilha->topo->peca->tempo_emb;
    embalador->progresso = 0;
    aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(aux); //n sei se isso vai dar certo
    pilha->usado--;
}