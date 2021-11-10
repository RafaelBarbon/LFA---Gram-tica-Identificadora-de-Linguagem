#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

// Função responsável por ler todo o arquivo e retornar uma lista com os símbolos encontrados
Lista* monta_simbolo(FILE *arq);
// Função que verifica a lista de palavras de acordo com a gramática
bool valida(Lista *simbolos);

int main(int argc, char **argv){
    if(argc < 1){ // Caso não haja o nome de arquivo como parâmetro
        printf("Erro nome de arquivo inexistente.");
        exit(0);
    }
    char c;
    FILE *arq = fopen(argv[1],"r");
    Lista *palavras = Cria();

    if(!arq){ // Caso não consiga abrir o arquivo por conta do nome incorreto
        printf("Erro ao abrir o arquivo.");
        exit(0);
    }
    palavras = monta_simbolo(arq);
    Imprime(palavras); // Para testes
    printf("\n");
    printf("%s", valida(palavras) ? "Aceito" : "Recusado");
    printf("\n");
    fclose(arq);
    Libera(&palavras);
    return 0;
}

// Função que verifica a lista de palavras de acordo com a gramática
bool valida(Lista *simbolos){
    Lista *simbolo = simbolos;
    if(simbolo && !(strcmp(simbolo->string,"main"))){ // Conferência do main(){
        simbolo = simbolo->prox;
        if(simbolo && !(strcmp(simbolo->string, "("))){
            simbolo = simbolo->prox;
            if(simbolo && !(strcmp(simbolo->string, ")"))){
                simbolo = simbolo->prox;
                if(simbolo && !(strcmp(simbolo->string, "{"))){
                    simbolo = simbolo->prox;
                }else return false;
            }else return false;
        }else return false;
    }else return false;

    while(simbolo && strcmp(simbolo->string, "}") != 0){ // Caso algum dos 4 tipos de comandos
        if(!strcmp(simbolo->string,"?")){ // Caso seja um símbolo não mapeado
            return false;
        }else if(!strcmp(simbolo->string,"int")){ // Caso declaração de variáveis
            simbolo = simbolo->prox;
            while(simbolo && !strcmp(simbolo->string,"id") && (strcmp(simbolo->string,";") != 0)){ // Confere o próximo identificador ou o final da declaração
                simbolo = simbolo->prox;
                if(simbolo && !strcmp(simbolo->string,",")){ // Confere se há uma próxima variável
                    simbolo = simbolo->prox;
                    if(simbolo && !strcmp(simbolo->string,";")) // Verifica se termina sem o identificador
                        return false;
                }
            }
        }else if(!strcmp(simbolo->string,"printf") || !strcmp(simbolo->string,"scanf")){ // Caso seja impressão ou coleta de valor de variável
            simbolo = simbolo->prox;
            if(simbolo && !strcmp(simbolo->string,"(")){
                simbolo = simbolo->prox;
                if(simbolo && !strcmp(simbolo->string,"id")){
                    simbolo = simbolo->prox;
                    if(simbolo && !strcmp(simbolo->string,")")){
                        simbolo = simbolo->prox;
                        if(simbolo && !strcmp(simbolo->string,";"))
                            simbolo = simbolo->prox;
                            continue;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        //else if(){ // Caso seja uma expressão (,),+,-,*,/,id,num
            //id=...;
            // Criar pilha para considerar o balanceamento dos parênteses
            // ... => (,),+,-,*,/,id,num
        //}
        if(!simbolo){
            return false;
        }
        simbolo = simbolo->prox;
    }
    if(simbolo && !strcmp(simbolo->string,"}"))
        return true;
    else
        return false;
}

// Função responsável por ler todo o arquivo e retornar uma lista com os símbolos encontrados
Lista* monta_simbolo(FILE *arq){
    char *palavra = NULL,c;
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
            if((strcmp(palavra,"printf") == 0) || (strcmp(palavra,"scanf") == 0) || (strcmp(palavra,"int") == 0) || (strcmp(palavra,"main") == 0)){
                Insere(&l,palavra);//insere na lista a palavra reservada
                //printf("Inseriu: %s\t",palavra);
            }
            else
                Insere(&l,"id");//insere na lista a variável
            flag = false;
            flagTI = true;
        }
        while(c >= 48 && c <= 57){//cadeia de números (Apenas verifica se tem um conjunto de números ou um apenas um número (Nao importa qual é o numero, ou seja não precisa salvar os números))
            c = getc(arq);
            flag = true;
        }
        if(flag){
            Insere(&l,"num");//insere na lista o número
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
            palavra[0] = '?';
            palavra[1] = 0;
            Insere(&l,palavra);//insere na lista o caracter desconhecido
            c = getc(arq);
        }
        flagTI = false;
    }
    return l;
}
