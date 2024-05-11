//Definições da estrutura de árvore binária de busca
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

typedef struct no{
    int chave;
    struct no *esquerda;
    struct no *direita;
    int soma_prefixo;
} No;

No *inicializaArvore() {
    No *raiz = NULL;
    return raiz;
}

//Função que mostra uma sub-árvore em ordem
void mostraSubArvoreEmOrdem(No *raiz) {
    if(raiz) {
        mostraSubArvoreEmOrdem(raiz->esquerda);
        printf(" [%d] ", raiz->chave);
        mostraSubArvoreEmOrdem(raiz->direita);
    }
}

//Função que imprime a palavra "Arvore" e chama a função de imprimir sub-árvores
void mostraArvoreEmOrdem(No *raiz) {
    printf("Arvore: ");
    mostraSubArvoreEmOrdem(raiz);
    printf("\n");
}

//Função que cria um novo nó, para facilitar a inserção. Supondo que sempre há memória
No *novoNo(int x) {
    No *temporario = (No *) malloc(sizeof(No));
    temporario->chave = x;
    temporario->esquerda = NULL;
    temporario->direita = NULL;
    return temporario;
}

//Função que insere de forma recursiva
void insere(No **raiz, int x) {
    if((*raiz) == NULL) {
        No *novo = novoNo(x);
        *raiz = novo;
    }
    else if (x < (*raiz)->chave) {
        insere(&(*raiz)->esquerda, x); 
    }
    else if (x > (*raiz)->chave){
        insere(&(*raiz)->direita, x);
    }
    else {
        return;
    }
}

//Função que busca uma raiz, retornando também seu pai, para propósitos de remoção
bool busca(No *raiz, No **filho, No **pai, int x) {
    *filho = NULL;
    *pai = NULL;

    while(raiz) {
        if(raiz->chave == x) {
            //Achei!
            *filho = raiz;
            return true;
        }

        *pai = raiz;

        if (x < raiz->chave) {
            raiz = raiz->esquerda;
        }
        else {
            raiz = raiz->direita;
        }
    }
    return false;
}

//Função que remove. Ela checa a quantidade de filhos, e realiza as operações de acordo
bool removeClaudson(No **raiz, int x) {
    No *pai = NULL, *filho = *raiz;
    if(busca(*raiz, &filho, &pai, x)) { //Achou       
        No *auxiliar = NULL;

        int numero_de_filhos = 0;    
        if(filho->esquerda) { numero_de_filhos++; auxiliar = filho->esquerda; }
        if(filho->direita) { numero_de_filhos++; auxiliar = filho->direita; }

        if(numero_de_filhos < 2) {
            if(pai == NULL) *raiz = auxiliar;
            else if (pai->esquerda == filho) pai->esquerda = auxiliar;
            else pai->direita = auxiliar;
            free(filho);
        }
        else { //numero_de_filhos == 2
            No *pai = filho;
            No *sucessor = filho->direita;

            while(sucessor->esquerda) {
                pai = sucessor;
                sucessor = sucessor->esquerda;
            }

            filho->chave = sucessor->chave;
            if(pai->direita == sucessor) pai->direita = sucessor->direita;
            else pai->esquerda = sucessor->direita;

            free(sucessor); 

        }
        return true;

    }
    else return false; //Não achou
}

int main() {
    No *raiz = inicializaArvore();

    mostraArvoreEmOrdem(raiz);

    insere(&raiz, 55);
    insere(&raiz, 10);
    insere(&raiz, 3);
    insere(&raiz, 25);
    insere(&raiz, 63);
    insere(&raiz, 60);
    insere(&raiz, 77);
    insere(&raiz, 59);
    insere(&raiz, 100);

    mostraArvoreEmOrdem(raiz);

    return 0;
}