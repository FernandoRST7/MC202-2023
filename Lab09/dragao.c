/*ARRUMAR:
  na hora de liberar a arvore o free(raiz) em vez de liberar a 
  struct no está liberando de novo a raiz->variavel e a raiz->tipo
  resultando em dois erros: 
    - liberando algo não alocado 
    - não liberando os blocos struct no
  mas ainda ta sem monitoria*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dragao.h"

int ehVermelho(p_no x) {
    if (x == NULL)
        return 0;
    return x->cor == VERMELHO;
}

int ehPreto(p_no x) {
    if (x == NULL)
        return 1;
    return x->cor == PRETO;
}

p_no rotaciona_para_esquerda(p_no raiz) {
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no rotaciona_para_direita(p_no raiz) {
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

void sobe_vermelho(p_no raiz) {
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

p_no inserir_rec(p_no raiz, char *variavel, char *tipo) {
    p_no novo;
    if (raiz == NULL) {
            novo = malloc(sizeof(struct no));
            novo->esq = novo->dir = NULL;

            novo->variavel = aloca_palavra(30);
            strcpy(novo->variavel, variavel);

            novo->tipo = aloca_palavra(10);
            strcpy(novo->tipo, tipo);

            novo->cor = VERMELHO;
        return novo;
    }
    if (strcmp(variavel, raiz->variavel) < 0)
        raiz->esq = inserir_rec(raiz->esq, variavel, tipo);
    else
        raiz->dir = inserir_rec(raiz->dir, variavel, tipo);
    /* corrige a árvore */
    if (ehVermelho(raiz->dir) && ehPreto(raiz->esq))
        raiz = rotaciona_para_esquerda(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
        raiz = rotaciona_para_direita(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
        sobe_vermelho(raiz);
    return raiz;
}

p_no inserir(p_no raiz, char *variavel, char *tipo) {
    raiz = inserir_rec(raiz, variavel, tipo);
    raiz->cor = PRETO;
    return raiz;
}

p_no buscar_iterativo(p_no raiz, char *variavel) {
    while (raiz != NULL && strcmp(variavel, raiz->variavel) != 0)
        if (strcmp(variavel, raiz->variavel) < 0)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    return raiz;
}

void printa_arvore(p_no raiz){
    if (raiz != NULL) {
        printa_arvore(raiz->esq);
        /* visita raiz */
        printf("%s %s\n", raiz->variavel, raiz->tipo);
        printa_arvore(raiz->dir);
    }
}

char * aloca_palavra(int n){
    char *p = malloc(n * sizeof(char));
    return p;
}

void libera_arvore(p_no raiz){
    if (raiz != NULL) {
        libera_arvore(raiz->esq);
        libera_arvore(raiz->dir);
        /* visita raiz */
        free(raiz->variavel);
        free(raiz->tipo);
        free(raiz);
        
    }
}