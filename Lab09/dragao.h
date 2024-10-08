enum cor {VERMELHO , PRETO};

typedef struct no *p_no;
struct no {
    char *variavel;
    char *tipo;
    enum cor cor;
    p_no esq, dir;
};

int ehVermelho(p_no x);

int ehPreto(p_no x);

p_no rotaciona_para_esquerda(p_no raiz);

p_no rotaciona_para_direita(p_no raiz);

void sobe_vermelho(p_no raiz);

p_no inserir_rec(p_no raiz, char *variavel, char *tipo);

p_no inserir(p_no raiz, char *variavel, char *tipo);

p_no buscar_iterativo(p_no raiz, char *variavel);

void printa_arvore(p_no raiz);

char * aloca_palavra(int n);

void libera_arvore(p_no raiz);
