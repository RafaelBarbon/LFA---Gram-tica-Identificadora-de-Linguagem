#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


void monta_simbolo(FILE *arq);

int main(int argc, char **argv){
    if(argc < 1){
        printf("Erro nome de arquivo inexistente.");
        exit(0);
    }

    FILE *arq = fopen(argv[1],"r");
    
    if(!arq){
        printf("Erro ao abrir o arquivo.");
        exit(0);
    }
    monta_simbolo(arq);
    fclose(arq);
    return 0;
}

void monta_simbolo(FILE *arq){
    char c;
    c = getc(arq);
    while( c != EOF){
       



       c = getc(arq);
    }

}