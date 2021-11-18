#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Criar pilha
Pilha* CriaP(){
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->no = NULL;
    return p;
}

// Verificação se está vazia
bool VaziaP(Pilha *p){
    if(p->no == NULL)
        return true;
    return false;
}

// Push para a pilha
No* InsertP(No *n, char p){
    No *novo = (No*)malloc(sizeof(No));
    novo->parentese = p;
    novo->prox = n;
    return novo;
}

void Push(Pilha *p, char pa){
    p->no = InsertP(p->no,pa);
}

// Pop para a pilha
No* RemoveP(No *n){
    No *nn = n->prox;
    free(n);
    return nn;
}

// Retorna o elemento que foi retirado ou -1 caso a pilha esteja vazia
char Pop(Pilha *p){
    if(VaziaP(p)){
        printf("\nPilha vazia."); // Para debug
        return -1;
    }
    char v = p->no->parentese;
    p->no = RemoveP(p->no);
    return v;
}

// Impressão da pilha para debug
void ImprimeP(Pilha *p){
    if(VaziaP(p))
        printf("\nPilha Vazia.");
    else
        for(No *aux = p->no; aux != NULL; aux = aux->prox)
            printf("\n%c", aux->parentese);
}

// Desalocamento de memória da pilha
void LiberaP(Pilha **p){
    No *aux = ((*p)->no), *aux2;
    while(aux != NULL){
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(*p);
    (*p) = NULL;
}