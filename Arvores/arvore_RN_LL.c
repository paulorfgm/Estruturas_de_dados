#include <stdio.h>
#include <stdlib.h>

#define rubro 'R'
#define negro 'N'

#define true 1
#define false 0
typedef int bool;

typedef struct no {
    int chave;
    char cor;
    struct no *esquerda, *direita;
} No;


No * inicializa() {
    No *raiz = NULL;
    return raiz;
}

No * novoNo(int x) {
    No *novo = malloc(sizeof(No)); 
    if (novo != NULL) {
        novo->chave = x;
        novo->direita = NULL; novo->esquerda = NULL;
        novo->cor = rubro;
        return novo;
    }
    else {
        printf("Não há memória!");
        return NULL;
    }
}

char COR(No *raiz) {
    if(raiz != NULL && raiz->cor == rubro) return rubro;
    else return negro;
}

void rotacaoDireita(No **raiz) {
    No *b = (*raiz); 
    No *a = (*raiz)->esquerda;
    No *c = a->direita;

    a->direita = b;
    b->esquerda = c;

    a->cor = negro;
    b->cor = rubro;

    (*raiz) = a;
}

void rotacaoEsquerda(No **raiz) {
    No *a = (*raiz);
    No *b = a->direita;
    No *c = b->esquerda;
    char cor_anterior = a->cor;

    a->direita = c;
    b->esquerda = a;

    a->cor = rubro;
    b->cor = cor_anterior;

    (*raiz) = b;
}

void insereRNLL(No **raiz, int x) {
    if (*raiz == NULL) {
        *raiz = novoNo(x);
        return;
    } 

    //Recolore
    if ((*raiz)->cor == negro && COR((*raiz)->esquerda) == rubro && COR((*raiz)->direita) == rubro) {
        (*raiz)->cor = rubro;
        (*raiz)->esquerda->cor = negro;
        (*raiz)->direita->cor = negro; 
    }  
    

    if (x < (*raiz)->chave) insereRNLL(&(*raiz)->esquerda, x);
    else insereRNLL(&(*raiz)->direita, x);

    if (COR((*raiz)->esquerda) == negro && COR((*raiz)->direita) == rubro) {
        rotacaoEsquerda(&(*raiz));
    }

    if (COR((*raiz)->esquerda) == rubro && COR((*raiz)->esquerda->esquerda) == rubro) {
        rotacaoDireita(&(*raiz));
    } 
}

void insereRN(No **raiz, int x) {
    insereRNLL(&(*raiz), x);
    if ((*raiz) != NULL) (*raiz)->cor = negro;
}

void printaSubArvore(No *raiz) {
    if (raiz != NULL) {
        printaSubArvore(raiz->esquerda);
        printf("\t[%d] - [%c]\n", raiz->chave, raiz->cor);
        printaSubArvore(raiz->direita);
    }
}

void printa(No *raiz) {
    printf("Arvore:\n");
    printaSubArvore(raiz);
    printf("\n");
}

int main() {
    No *arvore = inicializa();
    printa(arvore);

    insereRN(&arvore, 10);
    printa(arvore);
    insereRN(&arvore, 20);
    printa(arvore);
    insereRN(&arvore, 30);
    printa(arvore);
    insereRN(&arvore, 40);
    printa(arvore);
    insereRN(&arvore, 50);
    printa(arvore);
    insereRN(&arvore, 25);
    printa(arvore);
    insereRN(&arvore, 35);
    printa(arvore);
    insereRN(&arvore, 32);
    printa(arvore);
    insereRN(&arvore, 45);
    printa(arvore);
}
