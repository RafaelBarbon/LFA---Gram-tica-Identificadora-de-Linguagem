#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct lista{
    char *string;
    struct lista *prox;
}Lista;

Lista* Cria();
bool Vazia(Lista *l);
void Insere(Lista **l, char *v);
void Retira(Lista **l,int v);
int Busca(Lista *l, char *v);
void Imprime(Lista *l);
void Libera(Lista **l);
#endif