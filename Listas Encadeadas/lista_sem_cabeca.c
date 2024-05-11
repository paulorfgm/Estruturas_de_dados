//Lista ordenada, sem nó cabeça

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

typedef struct no {
    int chave;
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
} Lista;

Lista * inicializaLista() {
    Lista *inicio = NULL;
    return inicio;
}

void mostraLista(Lista *cabeca) {
    No *atual = cabeca->inicio;
    printf("Lista:");
    while(atual != NULL) {
        printf(" [%d] ", atual->chave);
        atual = atual->proximo;
    }
    printf("\n");
}

bool buscaLista(Lista *lista, No **anterior, No **posicao, int x) {
    *anterior = NULL;
    if(lista == NULL) return false;
    else {
        *posicao = lista->inicio;
        while((*posicao) && (*posicao)->chave < x) {
            *anterior = *posicao;
            *posicao = (*posicao)->proximo;
        }

        if((*posicao) && (*posicao)->chave == x) return true;
        else return false;
    }
}

bool insereLista(Lista *lista, int x) {
    No *anterior = NULL, *posicao = NULL;
    if(!buscaLista(lista, &anterior, &posicao, x)) {
        No *novo = malloc(sizeof(No));
        novo->chave = x;
        if(posicao == lista->inicio) {
            novo->proximo = NULL;
            lista->inicio = novo;
        }
        else {
            novo->proximo = posicao;
            anterior->proximo = novo;
        }
        return true;
    }
    return false;
}

bool removeLista(Lista *cabeca, int x) {
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
    Lista *ptlista = inicializaLista();

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