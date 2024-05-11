//A lista implementada aqui tem nó cabeça, é simplesmente encadeada, e ordenada em ordem crescente.

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

typedef struct no {
    int chave;
    struct no *proximo;
} No;

No * inicializaLista() {
    No *cabeca = malloc (sizeof(No));
    cabeca->proximo = NULL;
    return cabeca;
}

void mostraLista(No *cabeca) {
    No *atual = cabeca->proximo;
    printf("Lista:");
    while(atual != NULL) {
        printf(" [%d] ", atual->chave);
        atual = atual->proximo;
    }
    printf("\n");
}

bool buscaLista(No *cabeca, No **anterior, No **atual, int x) {
    *anterior = cabeca;
    *atual = cabeca->proximo;

    while((*atual) && (*atual)->chave < x) {
        *anterior = *atual;
        *atual = (*atual)->proximo;
    }

    if ((*atual) != NULL && (*atual)->chave == x) return true;
    else return false;
}

bool insereLista(No *cabeca, int x) {
    No *anterior = cabeca;
    No *posicao = cabeca->proximo;

    if(!buscaLista(cabeca, &anterior, &posicao, x)) {
        // Cria um novo nó e insere na posição correta
        No *novo = malloc(sizeof(No));
        novo->chave = x;
        novo->proximo = posicao;
        anterior->proximo = novo;
        return true;
    }
    else return false;
}

bool removeLista(No *cabeca, int x) {
    No *anterior = NULL;
    No *apagar = NULL;

    if(buscaLista(cabeca, &anterior, &apagar, x)) {
        anterior->proximo = apagar->proximo;
        free(apagar);
        return true;
    }
    else return false;
}

int main() {
    No *ptlista = inicializaLista();

    mostraLista(ptlista);

    insereLista(ptlista, 1);
    insereLista(ptlista, 100);
    insereLista(ptlista, 10);
    insereLista(ptlista, 1);

    mostraLista(ptlista);

    removeLista(ptlista, 10); 
    removeLista(ptlista, 100);   

    mostraLista(ptlista);

    removeLista(ptlista, 1);

    mostraLista(ptlista);

    return 0;
}