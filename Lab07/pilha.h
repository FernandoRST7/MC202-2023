#include "trabalhador.h"

typedef struct no *p_no;
struct no {
    p_peca peca;
    p_no prox;
};

typedef struct pilha *p_pilha;
struct pilha {
    p_no topo;
    int tamanho, usado, entrou;
};

p_pilha cria_pilha(int tamanho);

void libera_pilha(p_no no);

void empilhar(p_pilha pilha , p_peca peca);

void desempilha(p_pilha pilha, p_trabalhador embalador);
