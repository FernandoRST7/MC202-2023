#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dragao.h"

int main(){
    p_no arvore =   NULL;
    int n = 0; //contador
    int correto = 1;

    char *linha = aloca_palavra(200);

    char *palvra_1 = aloca_palavra(30);
    char *palvra_2 = aloca_palavra(30);
    char *palvra_3 = aloca_palavra(30);
    char *palvra_4 = aloca_palavra(30);
    char *palvra_5 = aloca_palavra(30);
    

    while(1){
        if (feof(stdin)) {
            break;
        }


        n++;
    
        

                                      //tipo      variavel  
        fgets(linha, 200, stdin);     //variavel  sinal     variavel  sinal     variavel

        if (strcmp(linha, "\n") == 0){
            continue;
        }

        sscanf(linha, "%s", palvra_1);

        //se palavra_1 for tipo -> declaração
        if (strcmp(palvra_1, "int" ) == 0 || strcmp(palvra_1, "char") == 0 
            || strcmp(palvra_1, "double") == 0){

            sscanf(linha, "%s %s",palvra_1, palvra_2);  
            
            if (strcmp(palvra_2, "main") != 0 && strcmp(palvra_2, "main()") != 0){
                palvra_2[strlen(palvra_2) - 1] = '\0';
                arvore = inserir(arvore, palvra_2, palvra_1);
            }
                
        //se a palavra_2 for = -> operação
        } else if (strcmp(palvra_1, "\n") != 0){
            sscanf(linha, "%s %s",palvra_1, palvra_2);  

            if (strcmp(palvra_2, "=") == 0){
            sscanf(linha, "%s %s %s %s %s", palvra_1, palvra_2, palvra_3, palvra_4, palvra_5);
            
            palvra_5[strlen(palvra_5) - 1] = '\0';

            p_no operando_1, operando_2, operando_3;
            operando_1 = buscar_iterativo(arvore, palvra_1);
            operando_2 = buscar_iterativo(arvore, palvra_3);
            operando_3 = buscar_iterativo(arvore, palvra_5);
            
            //primeiro erro
            if (operando_1 == NULL){
                printf("Linha %d: o símbolo %s não foi definido.\n", n, palvra_1);
                correto = 0;
            } else if (operando_2 == NULL){
                printf("Linha %d: o símbolo %s não foi definido.\n", n, palvra_3);
                correto = 0;
            } else if (operando_3 == NULL){
                printf("Linha %d: o símbolo %s não foi definido.\n", n, palvra_5);
                correto = 0;
            
            //segundo erro
            } else if (strcmp(operando_2->tipo, operando_3->tipo) != 0){
                printf("Linha %d: tipos incompatíveis: %s (%s) %s %s (%s).\n",
                       n, operando_2->variavel, operando_2->tipo, palvra_4,  
                       operando_3->variavel, operando_3->tipo);
                correto = 0;

            //terceiro erro
            } else if (strcmp(operando_1->tipo, operando_2->tipo) != 0){
                printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n",
                       n, operando_1->variavel, operando_1->tipo, operando_3->tipo);
                correto = 0;
            }
            //se n der nenhum dos 3 n faz nada
            }
        }


    }
    free(palvra_1);
    free(palvra_2);
    free(palvra_3);
    free(palvra_4);
    free(palvra_5);
    if (correto) printf("Não há erros de tipo.\n");


    free(linha);

    printa_arvore(arvore);
    libera_arvore(arvore);
    return 0;
}
