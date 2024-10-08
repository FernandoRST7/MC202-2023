#include "peca.h"

typedef struct trabalhador *p_trabalhador;
struct trabalhador {
    int tipo, ocupado, progresso, tempo, saiu;
    p_peca peca;
};

p_trabalhador cria_trabalhador(int diff);