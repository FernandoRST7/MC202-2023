#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livraria.h"

void criar_lista(p_lista lista) {
    lista->inicio = NULL;
    lista->fim = NULL;   
    lista->meio_e = NULL;
    lista->meio_d = NULL;
}

void libera_lista(p_no lista) { //tem q mudar dps
    if (lista != NULL) {
        libera_lista(lista->prox);
    free(lista->livro);
    free(lista);
    }
}

p_no remove_item(p_no no, char *obra, p_lista lista){
    //CONSERTAR OS MEIO_E E MEIO_D
    p_no aux;
    if (strcmp(no->livro, obra) == 0){
        aux = no->prox;
        if (lista->meio_e == no){ //se remover o meio_e
            lista->meio_e = NULL;
        } else if(lista->meio_d == no){ //se remover o meio_d
            lista->meio_d = no->prox; //conserta o meio_d
        } else if (no->prox == NULL){ //se remover o último
            lista->fim = NULL;
        }
        no->prox = NULL;
        free(no->livro);
        free(no);
        return aux;
    } else {
        no->prox = remove_item(no->prox, obra, lista);
        if (lista->meio_e == NULL){
            lista->meio_e = no; //conserta o meio_e
        } else if (lista->fim == NULL){
            lista->fim = no; //conserta o fim
        }
        return no;
    }
}

void adiciona(p_lista lista, int diff){
    if (lista->inicio == NULL && lista->fim == NULL){ //primeira add
        lista->inicio = adicionar_item(lista->inicio, diff, lista);
        lista->fim = lista->inicio;
    } else {
        if (diff == 0){
            /*obs: se o diff == 0, vai add entre o meio_e e o meio_d*/
            if (lista->inicio == NULL){ //primeira add no inicio, n tem um meio_e
                lista->inicio = adicionar_item(lista->inicio, diff, lista);
            } else { //aqui é qnd tiver
                lista->inicio = adicionar_item(lista->meio_e, diff, lista);
            }
        } else {
            lista->inicio = adicionar_item(lista->fim, diff, lista);
        }
    } 
    
}

p_no adicionar_item(p_no no, int diff, p_lista lista) {
    p_no novo, aux2;

    if (no == NULL){ //primeira add
        novo = malloc(sizeof(struct no));
        novo->livro = malloc(55 * sizeof(char));
        fgets(novo->livro, 55, stdin);
        novo->livro[strcspn(novo->livro, "\n")] = '\0';
        novo->prox = no;
        if (lista->fim != NULL){ //mas já tem algo no final/depois
            novo->prox = lista->meio_d;
            lista->meio_e = novo;
        }
        return novo;
    } else {
        if (no->prox != NULL){ //n é o último
            if (diff == 0){ //pra add no inicio semp vai ter prox
                no->prox = NULL;
                aux2 = adicionar_item(no, diff, lista);
            } else {
                aux2 = adicionar_item(no->prox, diff, lista);
            }
            aux2 = NULL;
            free(aux2);
            return lista->inicio;
        } else { //é o último
            novo = malloc(sizeof(struct no));
            novo->livro = malloc(55 * sizeof(char));
            fgets(novo->livro, 55, stdin);
            novo->livro[strcspn(novo->livro, "\n")] = '\0';
            if (diff == 0){
                novo->prox = lista->meio_d;
                lista->meio_e = novo;
                no->prox = novo;
            } else {
                novo->prox = NULL;
                no->prox = novo;
                lista->fim = novo;
            }
            return lista->inicio;
        }
    }    
}

void imprime_lista(p_no lista) {
    if (lista != NULL){
        printf("%s", lista ->livro);
        if (lista->prox != NULL){
            printf(", ");
        }
    imprime_lista(lista->prox);
    }
}

