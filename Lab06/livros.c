#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livraria.h"

int main(){
    p_lista lista;
    lista = malloc(4 * sizeof(p_no));
    criar_lista(lista);
    char *comando, *obra;
    int diff = 1;
    comando = malloc(10 * sizeof(char));
    obra = malloc(55 * sizeof(char));
    while (scanf("%s ", comando) != EOF){
        if (strcmp(comando, "adicionar") == 0){
            adiciona(lista, diff);
        } else if (strcmp(comando, "inicio") == 0){
            diff = 0;
            lista->meio_e = lista->inicio;
            lista->meio_d = lista->inicio;
            lista->inicio = NULL;
        } else if (strcmp(comando, "final") == 0){
            diff = 1;
        } else if (strcmp(comando, "remover") == 0){
            fgets(obra, 55, stdin);
            obra[strcspn(obra, "\n")] = '\0';
            lista->inicio = remove_item(lista->inicio, obra, lista);
        } else if (strcmp(comando, "imprimir") == 0){
            imprime_lista(lista->inicio);
            printf("\n");
        }
    }
    libera_lista(lista->inicio);
    free(lista);
    free(comando);
    free(obra);
    return 0;
}