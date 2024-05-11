#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100 //Tamanho máximo da expressao

//Definição de tipo booleano
#define true 1
#define false 0
typedef int bool;

//Definição de pilhas
typedef struct {
    char valores[MAX];
    int topo;
    int tamanho;
} Pilha;

Pilha* inicializaPilha() {
    Pilha *p = malloc(sizeof(Pilha));
    p->topo = 0;
    p->tamanho = MAX;
    return p; 
}

void mostraPilha(Pilha *p) {
    printf("Pilha: ");
    for(int i = 0; i < p->topo; i++) {
        printf(" [%d] ", p->valores[i]);
    } printf("\n");
}

bool push(char valor, Pilha *p) { //Coloca um elemento no topo da pilha
    //Se a pilha estiver cheia:
    if(p->topo == p->tamanho) {
        return false;
    }
    //Se a pilha não estiver nem cheia nem vazia:
    else {
        p->valores[p->topo] = valor;
        p->topo++;
        return true;
    }
}

int main() {
    Pilha *p = inicializaPilha();
    mostraPilha(p);
    push(5, p);
    mostraPilha(p);
    push(10, p);
    mostraPilha(p);
    push(15, p);
    mostraPilha(p);
    return 0;
}