#ifndef _PILHA_H_
#define _PILHA_H_
#include <stdbool.h>
#include <stdlib.h>

// Nós para fila e pilha com os 4 tipos de dados
typedef struct no{
    char parentese;
    struct no *prox;
}No;

typedef struct pilha{
    No *no;
}Pilha;

// Criar pilha
Pilha* CriaP();

// Verificação se está vazia
bool VaziaP(Pilha *p);

// Push para a pilha
No* InsertP(No *n, char p);

void Push(Pilha *p, char pa);

// Pop para a pilha
No* RemoveP(No *n);

// Retorna o elemento que foi retirado ou -1 caso a pilha esteja vazia
char Pop(Pilha *p);

// Impressão da pilha
void ImprimeP(Pilha *p);

// Desalocamento de memória da pilha
void LiberaP(Pilha **p);
#endif