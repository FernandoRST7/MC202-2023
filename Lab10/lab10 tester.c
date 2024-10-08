#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAI(i) ((i-1)/2)
#define F_ESQ(i) (2*i+1) /*Filho esquerdo de i*/
#define F_DIR(i) (2*i+2) /*Filho direito de i*/

typedef struct {
char *nome;
int prioridade, id, pos_heap;
} Sobrevivente;

typedef struct {
char *nome;
int prioridade, id;
} Item;

typedef struct {
Sobrevivente *s; //vetor com os sobreviventes
Item *v; // vetor de Items alocado dinamicamente
int n_s, n, tamanho; // n: qtde de elementos , tamanho: qtde alocada
} FP;

typedef FP * p_fp;

Sobrevivente* cria_sobrevivente(char *nome, int dias, int id);

Item* cria_item(char *nome, Sobrevivente s);

p_fp criar_filaprio(int tam);

void insere(p_fp fprio, Item item, int id);

void sobe_no_heap(p_fp fprio, int k, int id);

void desce_no_heap(p_fp fprio, int k, int id);

Item extrai_maximo(p_fp fprio);

void muda_prioridade(p_fp fprio, int k, int valor);

void troca(Item *a, Item *b);

char * aloca_palavra(int n);

//n tinha no slide, dps eu vejo se vou usar msm ou n
int vazia(p_fp fprio);

int cheia(p_fp fprio);

int main(){
    int n_panelas, n_sobreviventes, dias, id_out, N =1, valor;

    //pega os 2 primeiros números
    scanf("%d %d", &n_panelas, &n_sobreviventes);

    char *nome = aloca_palavra(16);
    char *sobrenome = aloca_palavra(16);
    char *comando = aloca_palavra(16);
    char *prato = aloca_palavra(34);

    p_fp prior_sobrev = criar_filaprio(n_sobreviventes);

    /*salva os sobreviventes*/
    for (id_out = 0; id_out < n_sobreviventes; id_out++){
            scanf("%s %s %d", nome, sobrenome, &dias);
            //juntar os nomes, passar ele, número do sobrevivente e id
            char *nome_final = aloca_palavra(34);
            strcat(nome_final, nome);
            strcat(nome_final, " ");
            strcat(nome_final, sobrenome);

            Sobrevivente* temp_s = cria_sobrevivente(nome_final, dias, id_out);
            prior_sobrev->s[id_out] = *temp_s;
            prior_sobrev->s[id_out].nome = strdup(temp_s->nome);

            /*strcpy(prior_sobrev->s[id_out].nome, nome_final);
            prior_sobrev->s[id_out].prioridade = dias;
            prior_sobrev->v[id_out].id = id_out;*/
            prior_sobrev->n_s++;

            /* prior_sobrev->v[id].prioridade = dias;
            strcpy(prior_sobrev->v[id].nome, nome_final);
            prior_sobrev->v[id].id = id;
            prior_sobrev->n++; */
            free(temp_s->nome);
            free(temp_s);
            free(nome_final);
    }

    /*começa o loop*/
    int rodada = 1;
    while (1) {
        scanf("%d", &N);
        if(N == 0) break;

        // fzr uma função que reseta o valor das prioridades originais antes da rodada começar
        for (int i = 0; i < n_sobreviventes; i++){

        }

        for(int i = 0; i < N; i++){
            scanf("%s %d ", comando, &id_out);
            comando[strcspn(comando, "\n")] = 0;
            

            if (strcmp(comando, "novo") == 0){
                //funciona, mas tem q tirar o /n do fainal dps
                fgets(prato, 34, stdin); 
                prato[strcspn(prato, "\n")] = 0;

                Item *temp = cria_item(prato, prior_sobrev->s[id_out]);

                //adiciona o prato no heap
                insere(prior_sobrev, *temp, id_out);

            } else if (strcmp(comando, "altera") == 0){
                scanf("%d", &valor);
                //primeiro vai ter q achar o ID (ou n), dps:
                muda_prioridade(prior_sobrev, id_out, valor);
            }
        }

        printf("---- rodada %d ----\n", rodada);
        rodada++;
        for (int i = 0; i < n_panelas; i++){
            Item temp = extrai_maximo(prior_sobrev);
            printf("%s %s %d\n", 
                    prior_sobrev->s[temp.id].nome, temp.nome, temp.prioridade);
        }
    }

    /*qnd acaba o loop acaba os faltaram*/
    while(prior_sobrev->n > 0){
        printf("---- rodada %d ----\n", rodada);
        rodada++;
        Item temp = extrai_maximo(prior_sobrev);
            printf("%s %s %d\n", 
                    prior_sobrev->s[temp.id].nome, temp.nome, temp.prioridade);
    }
    
}

Sobrevivente* cria_sobrevivente(char *nome, int dias, int id){
    Sobrevivente *S = malloc(sizeof(Sobrevivente));
    S->nome = aloca_palavra(34);
    strcpy(S->nome, nome);
    S->prioridade = dias;
    S->id = id;
    return S;
}

/*isso aqui ta beeeeeem estranho*/
Item* cria_item(char *nome, Sobrevivente sobrev){
    Item *I = malloc(sizeof(Item));
    I->nome = aloca_palavra(34);
    strcpy(I->nome, nome);
    I->prioridade = sobrev.prioridade;
    I->id = sobrev.id;

    return I;
}

p_fp criar_filaprio(int tam) {
    p_fp fprio = malloc(sizeof(FP));
    fprio->v = malloc(tam * sizeof(Item));
    fprio->s = malloc(tam * sizeof(Sobrevivente));
    fprio->n_s = 0;
    fprio->n = 0;
    fprio->tamanho = tam;
    return fprio;
}

void insere(p_fp fprio, Item item, int id/*isso aqui tbm*/) {
    fprio->v[fprio->n] = item;
    fprio->v[fprio->n].nome = strdup(item.nome);
    fprio->v[fprio->n].id = id; //tvz tire, eu q inventei î

    /*salva no vetor estático a posição do ítem no heap:*/
    fprio->s[id].pos_heap = fprio->n;

    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1, id);
    
}



void sobe_no_heap(p_fp fprio, int k, int id) {
    //k é a pos no heap
    if (k > 0 && fprio->v[PAI(k)].prioridade < fprio->v[k].prioridade) {
        // salva o valor antes de trocar
        // * int a = fprio->v[PAI(k)].id; -> tentar isso caso o método da troca n de certo
        troca(&fprio->v[k], &fprio->v[PAI(k)]);
        /*se trocar de posição, salva no vetor estático a nova posição*/
        fprio->s[id].pos_heap = k;
        fprio->s[fprio->v[PAI(k)].id].pos_heap = PAI(k); //trocado [v]

        sobe_no_heap(fprio, PAI(k), id);
    }
}

Item extrai_maximo(p_fp fprio) {
    Item item = fprio->v[0];
    troca(&fprio->v[0], &fprio->v[fprio->n - 1]);
    // TODO: trocar os = e colocar dentro do troca
    fprio->s[fprio->v[0].id].pos_heap = 0;
    fprio->s[fprio->v[fprio->n - 1].id].pos_heap = fprio->n - 1; //trocado [v]

    fprio->n--;
    desce_no_heap(fprio, 0, fprio->v[0].id);
    return item;
}



void desce_no_heap(p_fp fprio, int k, int id) {
    int maior_filho;
    if (F_ESQ(k) < fprio->n) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n &&
             fprio->v[F_ESQ(k)].prioridade < fprio->v[F_DIR(k)].prioridade)
            maior_filho = F_DIR(k);
        if (fprio->v[k].prioridade < fprio->v[maior_filho].prioridade) {
            troca(&fprio->v[k], &fprio->v[maior_filho]);

            fprio->s[id].pos_heap = k;
            fprio->s[fprio->v[maior_filho].id].pos_heap = maior_filho; //trocado [v]
            
            desce_no_heap(fprio, maior_filho, id);
        }
    }
}

void muda_prioridade(p_fp fprio, int k, int valor) {
    // k aqui é o id
    // fprio->s[k].pos_heap é onde ta no heap o bagulho de id=k

    
    if (valor > 0) { 
        fprio->v[fprio->s[k].pos_heap].prioridade += valor;
        sobe_no_heap(fprio, fprio->s[k].pos_heap, k); //arrumar!
    } else {
        fprio->v[fprio->s[k].pos_heap].prioridade += valor;
        desce_no_heap(fprio, fprio->s[k].pos_heap, k);
    }
}

void troca(Item *a, Item *b) {
    Item t = *a;
    *a = *b;
    *b = t;
}

char * aloca_palavra(int n){
    char *p = malloc(n * sizeof(char));
    p[0] = '\0';
    return p;
}