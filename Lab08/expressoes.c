#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controle.h"

int main(){
    int i, n;
    scanf("%d ", &n);
    for (i = 0; i < n; i++){
        p_no_p pilha = NULL;
        p_no arvore = NULL;
        arvore = cria_arvore(pilha);
        printa_arvore(arvore);
        printf("\n");
        otimiza_arvore(&arvore);
        printa_arvore(arvore);
        printf("\n");
        printf("\n");
        libera_arvore(arvore);
    }
    return 0;
}
