#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controle.h"

void embala(p_trabalhador embalador, p_pilha pilha){
    if (embalador->ocupado == 0){ //embalador livre
        if (pilha->topo != NULL){
            desempilha(pilha, embalador);//tira peça do topo e vai pro embalador
            //colocar coisa do tempo
        }
    } else { //ja esta com uma peça atribuida (ocupado)
        if (embalador->progresso < embalador->tempo){
            embalador->progresso++;
        }
        if (embalador->progresso == embalador->tempo){ //acabou
            libera_peca(embalador->peca); //n ta liberando td, ARRUMAR
            embalador->saiu = TRUE;
            embalador->ocupado = 0; //agr ta livre
            embalador->progresso = 0;
            embala(embalador, pilha);
        }
    }
}
void classifica(p_trabalhador classificador, p_esteira esteira, 
                p_pilha pilha, int *inputs, int n, int *atraso){

    if (classificador->ocupado == 0){ //classificador livre
        if (esteira->usado != 0){ //se tiver algo na esteira
            classificador->peca = desenfileira(esteira); //obs: diminui um usado
            classificador->ocupado = 1;
            classificador->progresso = 0;
            classificador->tempo = classificador->peca->tempo_class;
        }
        /*obs: se esteira tiver vazia ou tiver espaço e tiver algo pra 
          pegar ele pega, se n tiver mais nada pra pegar nem da produção
          nem da esteira n faz nada.*/

    } else { //ja esta com uma peça atribuida (ocupado)
        if (classificador->progresso < classificador->tempo){
            classificador->progresso++;
        }
        if (classificador->progresso == classificador->tempo && 
            pilha->usado < pilha->tamanho){ //acabou e tem espaço na pilha
            //empilha peça classificada
            empilhar(pilha, classificador->peca);
            pilha->entrou = TRUE;
            classificador->ocupado = 0; //agr ta livre
            classificador->progresso = 0;

            if (esteira->usado > 0){ //se ainda tiver coisa na esteira
                //já pega de lá mesmo
                classificador->peca = desenfileira(esteira);
                classificador->ocupado = 1; //n ta mais livre
                classificador->tempo = classificador->peca->tempo_class;
            }
        }
    }

    //se cabe algo na esteira e ainda tiver algo p/ pegar
    if (esteira->usado < esteira->tamanho && (*inputs) < n){
        enfileira(esteira); //pega a prox, //obs: aumenta 1 o usado
        (*inputs)++;
        esteira->entrou = TRUE;

    //quer add mas ta cheio: atraso.
    } else if (esteira->usado == esteira->tamanho && (*inputs) < n){
        (*atraso)++;
    }

}
