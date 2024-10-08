#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controle.h"

/*obs: fizemos um roteirinho de lógica no papel*/

int main(){
  p_pilha pilha;
  p_esteira esteira;
  p_trabalhador classificador, embalador;

  int tamanho_esteira, tamanho_pilha, n;
  int minuto = 0, atraso = 0, inputs = 0;

  //pega os dados da segunda linha
  scanf("%d %d", &tamanho_esteira, &tamanho_pilha);

  //usa p/ criar a pilha e a lista
  pilha = cria_pilha(tamanho_pilha);
  esteira = cria_esteira(tamanho_esteira);

  classificador = cria_trabalhador(0);
  embalador = cria_trabalhador(1);

  //pega info dos input
  scanf("%d", &n);
  printf("##### Simulação\n");

  while (1){
  /*apenas n vezes precisara verificar a entrada de novas pecas,
    depois é só continuar executando o sistema*/

    esteira->entrou = FALSE;
    pilha->entrou = FALSE;
    embalador->saiu = FALSE;

    /*primeira parte: embalador/pilha*/
    embala(embalador, pilha);
    
    /*segunda parte: classificador/esteira*/
    classifica(classificador, esteira, pilha, &inputs, n, &atraso);

    /*terceira parte: print*/
    minuto++;
    printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", 
    minuto, esteira->entrou, pilha->entrou, pilha->entrou, embalador->saiu);
 
    if (inputs == n && esteira->usado == 0 && classificador->ocupado == 0 && 
        pilha->usado == 0 && embalador->ocupado == 0){
      break;
    }
  }
  printf("Tempo atraso: %d.", atraso);
  libera_pilha(pilha->topo);
  free(pilha);
  libera_esteira(esteira);
  free(classificador);
  free(embalador);
  return 0;
}