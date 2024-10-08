#include "pilha.h"

typedef struct esteira *p_esteira;
struct esteira {
    int ini, fim, tamanho, usado, entrou;
    p_peca *vetor;
};

p_esteira cria_esteira(int tamanho);

void libera_esteira(p_esteira esteira);

void enfileira(p_esteira esteira);

p_peca desenfileira(p_esteira esteira);