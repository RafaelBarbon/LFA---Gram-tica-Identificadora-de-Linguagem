gcc -c pilha.c -o pilha.o && gcc -c lista.c -o lista.o && gcc -c main.c -o main.o
gcc lista.o pilha.o main.o -o identificador