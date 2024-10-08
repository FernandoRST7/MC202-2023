
enum tipo {
    numero,
    variavel,
    logico,
    operador
};

/*struct para Ã¡rvore*/
typedef struct no *p_no;
struct no {
    enum tipo tipo;
    char dado;
    p_no prox_e, prox_d;
};

/*struct pra pilha*/
typedef struct no_p *p_no_p;
struct no_p {
    p_no no; /*pode ser uma arvore, galho ou folha*/
    p_no_p prox;
};

/*função auxiliar com nome obvio*/
p_no cria_no(char in);

/*cria arvore com base nas entradas*/
p_no cria_arvore(p_no_p pilha);

/*auxiliar da cria arvore*/
p_no cria_galho(p_no_p *pilha);

void libera_arvore(p_no raiz);

/*recursivamente orienta a simplificação, vai até o galho mais longe
  até achar um operador*/
void otimiza_arvore(p_no *arvore);

void printa_arvore(p_no raiz);

/*chamada pela otimiza_arvore(), ve o operador e os operandos, se der para
  simplificar retorna um "bloco" com F ou T, se n der retorna a propria raiz*/
p_no simplifica(p_no raiz, p_no esq, p_no dir);

/*coloca F ouy T no bloco que será retornado*/
void logico_e_null(char log, p_no *no);

/*chama a cria_no para criar um novo nó a partir da entrada e empilha 
  ele em seguida.*/
p_no_p empilha_entrada(p_no_p topo, char in);

/*sempilha e libera o que tiver no topo*/
p_no_p desempilha(p_no_p topo);

/*empilha no topo*/
p_no_p empilha(p_no raiz, p_no_p topo);
