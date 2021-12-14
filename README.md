# LFA Gramática Identificadora de Linguagem
![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)
![MAC](https://img.shields.io/badge/MAC-000000?style=for-the-badge&logo=macos&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

![Visual Studio Code](https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white)

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)

## Como executar
### Windows
Compile o programa com `.\exec.bat` e execute usando `.\identificador <nome do arquivo>.txt`
### Linux
Atribua a permissão de execução do script usando `chmod +x exec.sh`
Compile o programa com `./exec.sh` e execute usando `./identificador <nome do arquivo>.txt`
### MAC
Atribua a permissão de execução do script usando `chmod +x exec.command`
Compile o programa com `./exec.command` e execute usando `./identificador <nome do arquivo>.txt`
## Descrição
Este projeto consiste em validar a **sintaxe** de uma simples linguagem de programação realizada a partir de uma gramática, e retornando se aceita ou rejeita o código analisado. Sendo que esta linguagem possui 4 palavras reservadas (`main`, `printf`, `scanf` e `int`).
A sintaxe em questão é composta por um cabeçalho
```
main(){
```
E dentro deste, pode-se haver 4 diferentes comandos:

Comando | Descrição
:---:|:---:
```int variável,variável;``` | Declaração de variáveis, sendo um int seguido por uma ou mais variáveis separadas por vírgula.
```printf(variável);``` | Exibição de valor de uma variável.
```scanf(variável);``` | Coleta de valor para uma variável.
```variável = exp;``` | Atribuição de valor a uma variável segundo uma expressão.

Para finalizar o programa, há o fechamento do mesmo com o símbolo `}`.

Todos os comandos têm seu fechamento com o símbolo `;`.

A expressão propriamente dita pode ser constituída de números, variáveis, operadores aritméticos e parênteses (balanceados).

Uma variável é constituída somente de letras minúsculas, assim como as palavras reservadas.

Para mais informações acerca do projeto, consulte o [enunciado](Trabalho%20LFA%202021.pdf) e/ou o [relatório](Relatório.pdf).

## Autores
- [Henrique Siqueira](https://github.com/h-ssiqueira)
- [Jemis Dievas](https://github.com/jamesdievas)
- [Rafael Barbon](https://github.com/RafaelBarbon)