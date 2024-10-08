#include <stdio.h>
int mais_consecutivas(int vendas1[], int n_vendas, int diferencial);


int main(){
    int i = 0, saladas, cinco = 0, sete = 0, dez = 0, repeticoes, numero_repetido;  //número de saladas
    scanf("%d", &saladas);
    int vendas[saladas];  //lista com os valores das vendas

    //adiciona os pix à lista de vendas
    for (i = 0; i<saladas; i++) {
        scanf("%d", &vendas[i]);
    }

    for (i = 0; i<saladas; i++) {
        if (vendas[i] == 5) {
            cinco++;
        } else if (vendas[i] == 7) {
            sete++;
        } else {
            dez++;
        }
    }
    repeticoes = mais_consecutivas(vendas, saladas, 0);
    numero_repetido = mais_consecutivas(vendas, saladas, 9);
    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais.\n", cinco, sete, dez);
    printf("James vendeu %d saladas de %d reais", repeticoes, numero_repetido);
}


int mais_consecutivas(int vendas1[], int n_vendas, int diferencial) {
    /* função que checa o maior número de sequência de algum número,
       o diferencial serve para escolher entre o numero de sequencias
       ou qual o numero da maior sequencia: ==0-->sequencia, !=0-->valor */
    int aux_5 = 0, aux_7 = 0, aux_10 = 0, i = 0, sequencia_max = 0, valor_max;
    
    while (i < n_vendas) {
        if (vendas1[i] == vendas1[i+1]) {
            if (vendas1[i] == 5) {
                aux_5++;
                do {
                    aux_5++;
                    i++;
                } while (vendas1[i] == vendas1[i+1]);
                if (aux_5 > sequencia_max) {
                    sequencia_max = aux_5;
                    valor_max = 5;
                }
                aux_5 = 0;

            } else if (vendas1[i] == 7) {
                aux_7++;
                do {
                    aux_7++;
                    i++;
                } while (vendas1[i] == vendas1[i+1]);
                if (aux_7 > sequencia_max) {
                    sequencia_max = aux_7;
                    valor_max = 7;
                }
                aux_7 = 0;

            } else if (vendas1[i] == 10) {
                do {
                    aux_10++;
                    i++;
                } while (vendas1[i] == vendas1[i+1]);
                if (aux_10 > sequencia_max) {
                    sequencia_max = aux_10;
                    valor_max = 10;
                }
                aux_10 = 0;
            }
        } else {
        i++;
        }
    }
    if (diferencial == 0) {
        return sequencia_max;
    } else {
        return valor_max;
    }
}   