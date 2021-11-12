#ifndef _LISTA_H_
#define _LISTA_H_
#include <stdbool.h>

typedef struct lista{
    char *string;
    struct lista *prox;
}Lista;

// Criar lista encadeada
Lista* Cria();

// Conferência de vazia
bool Vazia(Lista *l);

// Inserção de elementos no final da lista
void Insere(Lista **l, char *v);

// Retirar elemento da lista a partir da posição fornecida
void Retira(Lista **l,int v);

// Busca se o dado existe na lista e retorna a posição deste
int Busca(Lista *l, char *v);

// Impressão da lista para testes
void Imprime(Lista *l);

// Desalocamento da lista
void Libera(Lista **l);

#endif