#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "pilha.h"

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
    palavras = monta_simbolo(arq); // Lista de símbolos (referente a gramática) encontrados no arquivo
    //Imprime(palavras); // Para testes
    //printf("\n");
    printf("%s\n", valida(palavras) ? "Aceito" : "Recusado");
    fclose(arq);
    Libera(&palavras);
    return 0;
}

// Função que verifica a lista de palavras de acordo com a gramática
bool valida(Lista *simbolos){
    Lista *simbolo = simbolos;
    Pilha *parenteses = CriaP();
    bool flagOp = false; // Utilizada para intercalação entre num|id e op, abertura de parênteses e detecção de fechamento com op
    // Conferência do main(){
    if(simbolo && !(strcmp(simbolo->string,"main"))){
        simbolo = simbolo->prox;
        if(simbolo && !(strcmp(simbolo->string, "("))){
            simbolo = simbolo->prox;
            if(simbolo && !(strcmp(simbolo->string, ")"))){
                simbolo = simbolo->prox;
                if(simbolo && !(strcmp(simbolo->string, "{"))){
                    simbolo = simbolo->prox;
                }else{
                    LiberaP(&parenteses);
                    return false;
                }
            }else{
                LiberaP(&parenteses);
                return false;
            }
        }else{
            LiberaP(&parenteses);
            return false;
        }
    }else{
        LiberaP(&parenteses);
        return false;
    }
    //Conferência do corpo do programa (4 possibilidades de comandos - declaração de variáveis, coleta de valor de varíavel, exibição de valor de variável e atribuição de valor para variável)
    while(simbolo && strcmp(simbolo->string, "}") != 0){
        if(!strcmp(simbolo->string,"?")){ // Caso seja um símbolo não mapeado, já recusa o programa
            LiberaP(&parenteses);
            return false;
        }else if(!strcmp(simbolo->string,"int")){ // Caso declaração de variáveis
            simbolo = simbolo->prox;
            while(simbolo && !strcmp(simbolo->string,"id") && (strcmp(simbolo->string,";") != 0)){ // Confere o próximo identificador ou o final da declaração
                simbolo = simbolo->prox;
                if(simbolo && !strcmp(simbolo->string,",")){ // Confere se há uma próxima variável a partir da vírgula
                    simbolo = simbolo->prox;
                    if(simbolo && !strcmp(simbolo->string,";")){ // Verifica se termina sem o identificador (id,;)
                        LiberaP(&parenteses);
                        return false;
                    }
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
                        if(simbolo && !strcmp(simbolo->string,";")){
                            simbolo = simbolo->prox;
                            continue;
                        }else{
                            LiberaP(&parenteses);
                            return false;
                        }
                    }else{
                        LiberaP(&parenteses);
                        return false;
                    }
                }else{
                    LiberaP(&parenteses);
                    return false;
                }
            }else{
                LiberaP(&parenteses);
                return false;
            }
        }else if(simbolo && !strcmp(simbolo->string,"id")){ // Caso seja uma expressão (,),+,-,*,/,id,num
            simbolo = simbolo->prox;
            if(simbolo && !strcmp(simbolo->string,"=")){
                simbolo = simbolo->prox;
                flagOp = false; // Flag para contar com que o próximo símbolo seja um operador (desconsiderando parênteses)
                while(simbolo && strcmp(simbolo->string,";")){//Detecta expressão
                    if(simbolo && (!strcmp(simbolo->string,"(")) && (!flagOp)){ // Verifica se não é do tipo "num ( op"
                        Push(parenteses, '('); //joga na pilha
                    }else if(simbolo && !strcmp(simbolo->string,")") && flagOp){
                        if(Pop(parenteses) == -1){ // Verifica se foi possível realizar o pop (caso nao a pilha esta vazia)
                            LiberaP(&parenteses);
                            return false;
                        }
                    }else if(simbolo && (!strcmp(simbolo->string,"num")||!strcmp(simbolo->string,"id")) && !flagOp){
                         // Espera-se um operador aritmético no próximo símbolo
                        flagOp = true;
                    }else if(simbolo && (!strcmp(simbolo->string,"op")) && flagOp){
                        // Já foi identificado um operador aritmético neste símbolo
                        flagOp = false;
                    }else{ // Caso seja um símbolo inválido para a expressão ou símbolo
                        LiberaP(&parenteses);
                        return false;
                    }
                    simbolo = simbolo->prox;
                }
                if(!VaziaP(parenteses) || !flagOp){ // Verifica o balanceamento dos parênteses e o fechamento com op
                    LiberaP(&parenteses);
                    return false;
                }
            }else{ // Se não houver "=" como segundo símbolo do comando
                LiberaP(&parenteses);
                return false;
            }
        }else{ // Caso o comando inicie com um símbolo terminal, porém não válido para iniciar o comando
            LiberaP(&parenteses);
            return false;
        }
        simbolo = simbolo->prox;
    }
    if(simbolo && !strcmp(simbolo->string,"}")){
        LiberaP(&parenteses);
        return true;
    }
    LiberaP(&parenteses);
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
        //são letras -> cadeia de letras
        while(c >= 97 && c <= 122){
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
            palavra[i] ^= palavra[i]; // Atribuir \0 no final da cadeia de caracteres
            i ^= i; // Reinicializa o index
            // Verifica se a palavra formada é uma das reservadas
            if((strcmp(palavra,"printf") == 0) || (strcmp(palavra,"scanf") == 0) || (strcmp(palavra,"int") == 0) || (strcmp(palavra,"main") == 0)){
                Insere(&l,palavra);//insere na lista a palavra reservada
                //printf("Inseriu: %s\t",palavra);
            }
            else
                Insere(&l,"id");//insere na lista a variável
            flag = false;
            flagTI = true; // Booleano que identifica se é uma palavra que entrou para colocar na lista posteriormente
        }
        //cadeia de números (Apenas verifica se tem um conjunto de números ou um apenas um número (Nao importa qual é o numero, ou seja não precisa salvar os números))
        while(c >= 48 && c <= 57){
            c = getc(arq);
            flag = true;
        }
        if(flag){
            Insere(&l,"num");//insere na lista o número
            flag = false;
            flagTI = true; // Booleano que identifica se é uma palavra que entrou para colocar na lista posteriormente
        }
        if((c == '(') || (c == ')') ||(c == '{') ||( c == '}') || (c == ';') || (c == ',') || (c == '=' )){ // Detecta símbolo
            palavra = realloc(palavra,2);
            if(!palavra){
                printf("Erro: armazenamento insuficiente para alocar");
                exit(1);
            }
            palavra[0] = c;
            palavra[1] = 0;
            Insere(&l,palavra);//insere na lista o símbolo detectado
            c = getc(arq);
            flagTI = true; // Booleano que identifica se é uma palavra que entrou para colocar na lista posteriormente
        }
        if((c == '/') || (c == '+') ||(c == '-')|| (c == '*')){ // Detecta um operador aritmético
            Insere(&l,"op");//insere na lista o operador aritmético
            c = getc(arq);
            flagTI = true; // Booleano que identifica se é uma palavra que entrou para colocar na lista posteriormente
        }
        if(c == ' ' || c == '\n' || c == '\t'){// Caso haja espaço vazio, ignora o caractere e coleta o próximo
            c = getc(arq);
            flagTI = true; // Booleano que identifica se é uma palavra que entrou para colocar na lista posteriormente
        }
        if(!flagTI){ // Caso seja um caractere desconhecido
            Insere(&l,"?");//insere na lista
            c = getc(arq);
        }
        flagTI = false;
    }
    free(palavra);
    return l;
}
