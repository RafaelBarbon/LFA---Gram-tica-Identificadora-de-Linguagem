#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lista.h"

// Criar lista encadeada
Lista* Cria(){
    return NULL;
}

// Conferência de vazia
bool Vazia(Lista *l){
    if(l == NULL)
        return true;
    return false;
}

// Inserção de elementos no início da lista
void Insere(Lista **l, char *v){
    Lista *novo = malloc(sizeof(Lista)), *aux = *l;
    if(!novo){
        printf("Erro: armazenamento insuficiente para alocar");
        exit(1);
    }
    novo->string = malloc((strlen(v)+1)*sizeof(char));
    if(!novo->string){
        printf("Erro: armazenamento insuficiente para alocar");
        exit(1);
    }
    strcpy(novo->string,v);
    if(!(*l)){
        novo->prox = NULL;
        *l = novo;
    }
    else{
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}

// Retirar elemento da lista a partir da posição fornecida
void Retira(Lista **l,int v){
    Lista *aux, *aux2;
    int i;
    for(i = 0, aux = (*l), aux2 = NULL; aux != NULL; i++, aux2 = aux, aux = aux->prox){
        if(i == v){
            if(v == 0)
                (*l) = aux->prox;
            else
                aux2->prox = aux->prox;
            free(aux->string);
            free(aux);
            break;
        }
    }
}

// Busca se o dado existe na lista e retorna a posição deste
int Busca(Lista *l, char *v){
    Lista *aux;
    int i;
    for(i = 0, aux = l; aux != NULL; i++, aux = aux->prox)
        if(strcmp(aux->string,v) == 0)
            return i;
    return -1;
}

// Impressão da lista
void Imprime(Lista *l){
    if(Vazia(l))
        printf("\nLista vazia.");
    else
        for(Lista *aux = l; aux != NULL; aux = aux->prox)
            printf("\n%s",aux->string);
}

// Desalocamento da lista
void Libera(Lista **l){
    Lista *aux = (*l), *aux2;
    while(aux != NULL){
        aux2 = aux->prox;
        free(aux->string);
        free(aux);
        aux = aux2;
    }
    (*l) = NULL;
}
