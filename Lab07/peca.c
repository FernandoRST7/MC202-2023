#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peca.h"

p_peca cria_peca(){
    p_peca p;
    p = malloc(sizeof(struct peca));
    p->tamanho_peca = malloc(10 * sizeof(char));
    scanf("%s %d", p->tamanho_peca, &p->classe_peca);
    p->minuto = 0; //qnd tiver ficado 1 min na pilha vira 1
    if (strcmp(p->tamanho_peca, "pequena") == 0){
        p->tempo_class = 1;
        if (p->classe_peca == 1){
            p->tempo_emb =1; 
        } else {
            p->tempo_emb = 2;
        }
    } else if (strcmp(p->tamanho_peca, "media") == 0){
        p->tempo_class = 2;
        if (p->classe_peca == 1){
            p->tempo_emb =2; 
        } else {
            p->tempo_emb = 3;
        }
    } else {
        p->tempo_class = 3;
        if (p->classe_peca == 1){
            p->tempo_emb =2; 
        } else {
            p->tempo_emb = 3;
        }
    }
    return p;
}

void libera_peca(p_peca peca){
    free(peca->tamanho_peca);
    free(peca);
}