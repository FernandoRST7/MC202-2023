#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controle.h"

/*ta vazando memoria qnd eu dou malloc em um novo "bloco" e retorno ele.
  n sei pq, se eu retorno e ainda estou usando, e mais pra frente, qnd n for mais usado
  é liberado. aí n sei pq ta vazando. queria ir na monitoria*/

p_no cria_no(char in){
    p_no novo = malloc(sizeof(struct no));
    novo->dado = in;
    if (in >= '0' && in <= '9'){
        novo->tipo = numero;
    } else if (in >= 'a' && in <= 'z'){
        novo->tipo = variavel;
    } else if (in == 'T' || in == 'F'){
        novo->tipo = logico;
    } else {
        novo->tipo = operador;
    }
    novo->prox_e = NULL;
    novo->prox_d = NULL;
    return novo;
}

p_no cria_arvore(p_no_p pilha){
    p_no galho;
    char in;
    while (1){
        scanf("%c", &in);
        if (in == '\n'){
            /*teoricamente, se entrou aqui Ã© pq tbm sÃ³ tem um item na 
              pilha, q Ã© a prÃ³pria Ã¡rvore*/
            pilha = desempilha(pilha);
            return galho;
            break;
        }
        pilha = empilha_entrada(pilha, in);
        
        if (pilha->no->tipo == operador){
            /*criia o galho e dps empilha ele*/
            galho = cria_galho(&pilha);
            pilha = empilha(galho, pilha);
        }
    }
};

p_no cria_galho(p_no_p *pilha){
    p_no novo_galho = malloc(sizeof(struct no));

    novo_galho = (*pilha)->no;
    (*pilha) = desempilha((*pilha));

    novo_galho->prox_d = (*pilha)->no;
    (*pilha) = desempilha((*pilha));

    novo_galho->prox_e = (*pilha)->no;
    (*pilha) = desempilha((*pilha));

    return novo_galho;
}

void libera_arvore(p_no raiz){
    if (raiz != NULL/* && raiz->tipo == operador*/){
        libera_arvore(raiz->prox_e);
        libera_arvore(raiz->prox_d);
        if (raiz->tipo == operador){
            free(raiz);
        }
    }
}

/*pos ordem*/
void otimiza_arvore(p_no *raiz){
    //p_no_p pilha = NULL;
    p_no *aux_e, *aux_d;
    aux_e = &(*raiz)->prox_e;
    aux_d = &(*raiz)->prox_d;

    if ((*raiz) != NULL && (*raiz)->tipo == operador) {
        otimiza_arvore(aux_e);
        otimiza_arvore(aux_d);
        if((*raiz)->tipo == operador){ /* visita raiz */
            (*raiz) = simplifica((*raiz) ,(*raiz)->prox_e, (*raiz)->prox_d);
            //pilha = empilha(raiz, pilha);
        } 
    }
}

//TESTAR ESSA BOSTA
p_no simplifica(p_no raiz, p_no esq, p_no dir){
    p_no novo = malloc(sizeof(struct no));
    novo->tipo = logico;
    novo->prox_e = NULL;
    novo->prox_d = NULL;
    
    //p_no raiz é o operador
    //relacionais
    if (raiz->dado == '>'){
        //casos especiais
        if (esq->tipo != dir->tipo){
            if (esq->tipo == variavel && dir->dado == '9'){
                logico_e_null('F', &novo);
                libera_arvore(raiz);
                return novo;
            } else if (dir->tipo == variavel && esq->dado == '0'){
                logico_e_null('F', &novo);
                libera_arvore(raiz);
                return novo;
            } else {
                //n faxz nada
                free(novo);
                return raiz;
            }
        } else if (esq->tipo == variavel || esq->tipo == logico){
            if(esq->dado == dir->dado){
                logico_e_null('F', &novo);
                libera_arvore(raiz);
                return novo;
            }
        //casos normais
        } else if (esq->dado > dir->dado){
            logico_e_null('T', &novo);
            libera_arvore(raiz);
            return novo;
        } else {
            logico_e_null('F', &novo);
            libera_arvore(raiz);
            return novo;
        }
    } else if (raiz->dado == '<'){
        //casos especiais
        if (esq->tipo != dir->tipo){
            if (esq->tipo == variavel && dir->dado == '0'){
                logico_e_null('F', &novo);
                libera_arvore(raiz);
                return novo;
            } else if (dir->tipo == variavel && esq->dado == '9'){
                logico_e_null('F', &novo);
                libera_arvore(raiz);
                return novo;
            } else {
                //n faxz nada
                free(novo);
                return raiz;
            }
        } else if (esq->tipo == variavel || esq->tipo == logico){
            if(esq->dado == dir->dado){
                logico_e_null('F', &novo);
                libera_arvore(raiz);
                return novo;
            }
        //casos normais
        } else if (esq->dado < dir->dado){
            logico_e_null('T', &novo);
            libera_arvore(raiz);
            return novo;
        } else {
            logico_e_null('F', &novo);
            libera_arvore(raiz);
            return novo;
        }
    } else if (raiz->dado == '{'){
        //casos especiais
        if (esq->tipo != dir->tipo){
            if (esq->tipo == variavel && dir->dado == '9'){
                logico_e_null('T', &novo);
                libera_arvore(raiz);
                return novo;
            } else if (dir->tipo == variavel && esq->dado == '0'){
                logico_e_null('T', &novo);
                libera_arvore(raiz);
                return novo;
            } else {
                //n faxz nada
                free(novo);
                return raiz;
            }
        } else if (esq->tipo == variavel || esq->tipo == logico){
            if(esq->dado == dir->dado){
                logico_e_null('T', &novo);
                libera_arvore(raiz);
                return novo;
            }
        //casos noormais
        } else if (esq->dado <= dir->dado){
            logico_e_null('T', &novo);
            libera_arvore(raiz);
            return novo;
        } else {
            logico_e_null('F', &novo);
            libera_arvore(raiz);
            return novo;
        }
    } else if (raiz->dado == '}'){
        //casos especiais
        if (esq->tipo != dir->tipo){
            if (esq->tipo == variavel && dir->dado == '0'){
                logico_e_null('T', &novo);
                libera_arvore(raiz);
                return novo;
            } else if (dir->tipo == variavel && esq->dado == '9'){
                logico_e_null('T', &novo);
                libera_arvore(raiz);
                return novo;
            } else {
                //n faxz nada
                free(novo);
                return raiz;
            }
        } else if (esq->tipo == variavel || esq->tipo == logico){
            if(esq->dado == dir->dado){
                logico_e_null('T', &novo);
                libera_arvore(raiz);
                return novo;
            }
        //casos normais
        } else if (esq->dado >= dir->dado){
            logico_e_null('T', &novo);
            libera_arvore(raiz);
            return novo;
        } else {
            logico_e_null('F', &novo);
            libera_arvore(raiz);
            return novo;
        }

    //logicos
    } else if (raiz->dado == '|'){
        if (esq->dado == 'T' || dir->dado == 'T'){
            logico_e_null('T', &novo);
            libera_arvore(raiz);
            return novo;
        }else if (esq->tipo != logico || dir->tipo != logico){
            //n faz nada
            free(novo);
            return raiz;
        } else {
            logico_e_null('F', &novo);
            libera_arvore(raiz);
            return novo;
        }
    } else if (raiz->dado == '&'){
        if (esq->dado == 'F' || dir->dado == 'F'){
            logico_e_null('F', &novo);
            libera_arvore(raiz);
            return novo;
        } else if (esq->dado == 'T' && dir->dado == 'T'){
            logico_e_null('T', &novo);
            libera_arvore(raiz);
            return novo;
        } else {
            //n faz nada
            free(novo);
            return raiz;
        }

    //comparação
    } else if (raiz->dado == '='){
        if (esq->tipo == dir->tipo){    
            if (esq->tipo == numero){
                if (esq->dado == dir->dado){
                    logico_e_null('T', &novo);
                    libera_arvore(raiz);
                    return novo;
                } else { //se !=
                    logico_e_null('F', &novo);
                    libera_arvore(raiz);
                    return novo;
                }
            } else if (esq->tipo == variavel) {
                if (esq->dado == dir->dado){
                    logico_e_null('T', &novo);
                    libera_arvore(raiz);
                    return novo;
                } else {
                    //n faz nada
                    free(novo);
                    return raiz;
                }
            } else {
                //n faz nada
                free(novo);
                return raiz;
            } 
        } else {
            //se forem tipos diferentes
            //n faz nada
            free(novo);
            return raiz;
        }
    } else if (raiz->dado == '!'){
        if (esq->tipo == dir->tipo){    
            if (esq->tipo == numero){
                if (esq->dado != dir->dado){
                    logico_e_null('T', &novo);
                    libera_arvore(raiz);
                    return novo;
                } else { //se ==
                    logico_e_null('F', &novo);
                    libera_arvore(raiz);
                    return novo;
                }
            } else if (esq->tipo == variavel || esq->tipo == logico) {
                if (esq->dado == dir->dado){
                    logico_e_null('F', &novo);
                    libera_arvore(raiz);
                    return novo;
                } else {
                    //n faz nada
                    free(novo);
                    return raiz;
                }
            } else {
                //n faz nada
                free(novo);
                return raiz;
            } 
        } else {
            //se forem tipos diferentes
            //n faz nada
            free(novo);
            return raiz;
        }
    }
    free(novo);
    return raiz;
}

void logico_e_null(char log, p_no *no){
    (*no)->dado = log;
    (*no)->prox_e = NULL;
    (*no)->prox_d = NULL;
}

/*inordem*/
void printa_arvore(p_no raiz){
    int abriu = 0;
    if (raiz != NULL) {

        if (raiz->tipo == operador){
            printf("(");
            abriu++;
        } 
        printa_arvore(raiz->prox_e);
        
        /* visita raiz */
        if (raiz->tipo == operador){
            printf(" %c ", raiz->dado);
        } else {
            printf("%c", raiz->dado);
        }

        printa_arvore(raiz->prox_d);
        
        if (raiz->tipo == operador && abriu > 0){
            printf(")");
            abriu--;
        }
    }
}

p_no_p empilha_entrada(p_no_p topo, char in){
    p_no_p novo_pilha = malloc(sizeof(struct no_p));

    p_no novo_no = cria_no(in);
    novo_pilha->no = novo_no;
    novo_pilha->prox = topo;
    topo = novo_pilha;
    return topo;
};

p_no_p desempilha(p_no_p topo){
    p_no_p aux = topo;
    topo = topo->prox;
    free(aux);
    return topo;
}

p_no_p empilha(p_no raiz, p_no_p topo){
    p_no_p novo_pilha = malloc(sizeof(struct no_p));
    novo_pilha->no = raiz;
    novo_pilha->prox = topo;
    topo = novo_pilha;
    return topo;
};