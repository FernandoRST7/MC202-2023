#define TRUE 1;
#define FALSE 0;


typedef struct peca *p_peca;
struct peca {
    char *tamanho_peca;
    int classe_peca, tempo_class, tempo_emb, minuto;
};

p_peca cria_peca();

void libera_peca(p_peca peca);