typedef struct no *p_no;

struct no {
    char *livro;
    p_no prox;
};

typedef struct lista *p_lista;

struct lista {
    p_no inicio, fim, meio_e, meio_d;
};

/*cria uma variavel do tipo lista*/
void criar_lista(p_lista lista);

/*libera a lista inteira 
  obs: a partir de onde for enviado, mas aí é só enviar o inicio*/
void libera_lista(p_no lista);

/*remove da lista o livro q for pra "obra"*/
p_no remove_item(p_no no, char *obra, p_lista lista);

/*orienta a adição de elementos*/
void adiciona(p_lista lista, int diff);

/*adiciona um elemento*/
p_no adicionar_item(p_no no, int diff, p_lista lista);

/*imprime a lista inteira, mas n da "\n"
  obs: a partir de onde for enviado, mas aí é só enviar o inicio*/
void imprime_lista(p_no lista);