#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalhador.h"

p_trabalhador cria_trabalhador(int diff){
    p_trabalhador t;
    t = malloc(sizeof(struct trabalhador));
    t->tipo = diff; //0 é class, 1 é embalar
    t->ocupado = 0; //0 é livre, 1 é ocupado
    t->progresso = 0;
    t->tempo = 0; /*vai ser atribuido dps de ver
                    em qual peça vai trabalhar*/
    t->saiu = FALSE;
    return t;
}