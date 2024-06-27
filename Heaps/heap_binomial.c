//REFAZER, CONSIDERANDO QUE A HEAP DEVE SER UMA ESTRUTURA TAMBÉM, E DEVE CONTER UM CAMPO "MÍNIMO"

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    struct no* primeiro_filho;
    struct no* ultimo_filho;
    struct no* irmao;
    int chave;
    int ordem;
} No;

No * novoNo(int x) {
    No *novo = malloc(sizeof(No));

    if(novo == NULL) {
        printf("Nao ha memoria o bastante!\n");
        return NULL;
    }

    novo->chave = x;
    novo->ordem = 0;
    novo->primeiro_filho = NULL;
    novo->ultimo_filho = NULL;
    novo->irmao = NULL;
}

No * inicializa() {
    return NULL;
}

void subordina(No **h1, No **h2) {
    if((*h1) == NULL || (*h2) == NULL) return;

    No *temporario;
    if((*h1)->chave < (*h2)->chave) {
        temporario = (*h1)->ultimo_filho;
        temporario->irmao = (*h2);
        (*h1)->ultimo_filho = (*h2);
    }
    else {
        temporario = (*h2)->ultimo_filho;
        temporario->irmao = (*h1);
        (*h2)->ultimo_filho = (*h1);
    }

    subordina(&((*h1)), (&(*h2)->irmao));
}

void adiciona(No **heap, int x) {
    No *novo = novoNo(x);

    if((*heap) == NULL) {
        (*heap) = novo;
        return;
    }

    if ((*heap)->ordem != 0) {
        return; 
    }
    
    subordina(&novo, (&(*heap)->irmao));
}

int removeMin(No **heap) {

}

int potencia(int x, int y) {
    int p = 1;
    for(int i = 1; i <= y; i++) {
        p *= x;
    }
    return p;
}

int descobreTamanho(No *heap) {
    No *aux = heap;
    int tamanho = 0;
    while(aux) {
        tamanho += potencia(2, aux->ordem);
        aux = aux->irmao;
    }
    return tamanho;
}

void printaRemovendo(No **heap) {
    int tamanho = descobreTamanho(*heap);
    for(int i = 0; i < tamanho; i++) {

    }
}

int main() {
    No *heap = inicializa();
    
    


    return 0;
}