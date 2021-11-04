#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#define MAX 50

Lista* monta_simbolo(FILE *arq);

int main(int argc, char **argv){
    if(argc < 1){
        printf("Erro nome de arquivo inexistente.");
        exit(0);
    }
    char c;
    FILE *arq = fopen(argv[1],"r");
    Lista *palavras = Cria();

    if(!arq){
        printf("Erro ao abrir o arquivo.");
        exit(0);
    }
    palavras = monta_simbolo(arq);
    fclose(arq);
    return 0;
}

Lista* monta_simbolo(FILE *arq){
    char *palavra,c;
    int i = 0;
    bool flag = false, flagTI = false;
    Lista *l = Cria();
    c = getc(arq);
    while(c != EOF){
        while(c >= 97 && c <= 122){//são letras
            palavra = realloc(palavra,i+1); // Realoca espaço para o novo caractere
            if(!palavra){ // Caso não haja memória disponível retornará NULL no realloc
                printf("Erro: armazenamento insuficiente para alocar");
                exit(1);
            }

            palavra[i++] = c; // Adiciona o novo caractere na palavra a ser identificada

            c = getc(arq); // Lê o próximo caractere do arquivo
            flag = true; // Booleano que identifica se é uma palavra que entrou para colocar na lista posteriormente
        }
        if(flag){
            palavra[i] ^= palavra[i];
            i ^= i;
            Insere(&l,palavra);//insere na lista
            flag = false;
            flagTI = true;
        }
        while(c >= 48 && c <= 57){//cadeia de números
            palavra = realloc(palavra,i+1);
            if(!palavra){
                printf("Erro: armazenamento insuficiente para alocar");
                exit(1);
            }

            palavra[i++] = c;

            c = getc(arq);
            flag = true;
        }
        if(flag){
            palavra[i] ^= palavra[i];
            i ^= i;
            Insere(&l,palavra);//insere na lista
            flag = false;
            flagTI = true;
        }
        if(c == '('){
            Insere(&l,"(");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == ')'){
            Insere(&l,")");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == '{'){
            Insere(&l,"{");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == '}'){
            Insere(&l,"}");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == ';'){
            Insere(&l,";");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == ','){
            Insere(&l,",");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == '='){
            Insere(&l,"=");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == '+'){
            Insere(&l,"+");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == '-'){
            Insere(&l,"-");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == '*'){
            Insere(&l,"*");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == '/'){
            Insere(&l,"/");//insere na lista
            c = getc(arq);
            flagTI = true;
        }
        if(c == ' ' || c == '\n' || c == '\t'){// Caso haja espaço vazio, ignora o caractere e coleta o próximo
            c = getc(arq);
            flagTI = true;
        }
        if(!flagTI){
            palavra = realloc(palavra,2);
            if(!palavra){
                printf("Erro: armazenamento insuficiente para alocar");
                exit(1);
            }
            palavra[0] = c;
            palavra[1] = 0;
            Insere(&l,palavra);//insere na lista o caracter desconhecido
            c = getc(arq);
        }
        flagTI = false;
    }

}
