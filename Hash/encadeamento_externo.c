#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_HASH 5

#define true 1
#define false 0
typedef int bool;

typedef struct no {
    int chave;
    struct no *proximo;
} No;

typedef No ** Hash;

Hash inicializa(int tamanho) {
    Hash hash = (Hash) malloc(sizeof(No *) * tamanho);
    for (int i = 0; i < tamanho; i++) {
        hash[i] = NULL;
    }
    return hash;
}

No *novoNo(int x) {
    No *novo = (No *) malloc(sizeof(No));
    novo->chave = x;
    novo->proximo = NULL;
    return novo;
}

int funcaoHash(int x) {
    return x;
}

int h(int x) {
    return funcaoHash(x) % TAMANHO_HASH;
}

No * busca(Hash hash, int x) {
    int posicao = h(x);
    No *atual = hash[posicao];

    while(atual != NULL && atual->chave != x) {
        atual = atual->proximo;
    }

    if(atual != NULL) return atual;
    else return NULL;
}

bool insere(Hash hash, int x) {
    int posicao = h(x);
    No *atual = hash[posicao];

    while (atual != NULL && atual->chave != x) {
        atual = atual->proximo;
    }

    if (atual != NULL) {
        return false;
    }

    No *novo = novoNo(x);
    novo->proximo = hash[posicao];
    hash[posicao] = novo;

    return true;
}

bool remover(Hash hash, int x) {
    int posicao = h(x);
    No *atual = hash[posicao];
    No *anterior = NULL;

    while (atual != NULL && atual->chave != x) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (anterior != NULL) {
            anterior->proximo = atual->proximo;
        } else {
            hash[posicao] = atual->proximo;
        }
        free(atual);
        return true;
    } else {
        return false;
    }
}

void printa(Hash hash) {
    No *atual;
    printf("\nHash: \n");
    for (int i = 0; i < TAMANHO_HASH; i++) {
        printf("\tPosicao %d: ", i);
        atual = hash[i];
        while (atual != NULL) {
            printf(" [%d] ", atual->chave);
            atual = atual->proximo;
        }
        printf("\n");
    }
    printf("Fim da Hash\n");
}

int main() {
    Hash hash = inicializa(TAMANHO_HASH);

    char operacao;
    int numero;

    while(fscanf(stdin, "%c", &operacao) && !feof(stdin)) {
        switch (operacao) {
        case 'p':
            printa(hash);
            printf("\n");
            break;
        case 'i':
            fscanf(stdin, "%d", &numero);
            insere(hash, numero);
            break;
        case 'r':
            fscanf(stdin, "%d", &numero);
            remover(hash, numero);
            break;
        default:
            exit(1);
            break;
        }
        getchar();
    }
    return 0;
}
