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

//Função que mostra uma árvore em pre-ordem
void mostraArvoreEmPreOrdem(No *raiz) {
    if(raiz) {
        printf("%d ", raiz->chave);
        mostraArvoreEmPreOrdem(raiz->esquerda);
        mostraArvoreEmPreOrdem(raiz->direita);
    }
}

//Função que cria um novo nó, para facilitar a inserção. Supondo que sempre há memória
No *novoNo(int x) {
    No *temporario = (No *) malloc(sizeof(No));
    if (temporario == NULL) {
        printf("\nNao tem memoria!\n");
        exit(1);
    }
    temporario->chave = x;
    temporario->esquerda = NULL;
    temporario->direita = NULL;
    return temporario;
}

//Função que insere de forma recursiva
void insereNo(No **raiz, int x) {
    if((*raiz) == NULL) {
        No *novo = novoNo(x);
        *raiz = novo;
    }
    else if (x < (*raiz)->chave) {
        insereNo(&(*raiz)->esquerda, x); 
    }
    else if (x > (*raiz)->chave){
        insereNo(&(*raiz)->direita, x);
    }
    else {
        return;
    }
}

//Função que busca uma raiz, retornando também seu pai, para propósitos de remoção
bool buscaNo(No *raiz, No **filho, No **pai, int x) {
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
bool removeNo(No **raiz, int x) {
    No *pai = NULL, *filho = *raiz;
    if(buscaNo(*raiz, &filho, &pai, x)) { //Achou       
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
    No *arvore = inicializaArvore();
    char operacao;
    int numero;

    while(fscanf(stdin, "%c", &operacao) && !feof(stdin)) {
        switch (operacao) {
        case 'p':
            mostraArvoreEmPreOrdem(arvore);
            printf("\n");
            break;
        case 'i':
            fscanf(stdin, "%d", &numero);
            insereNo(&arvore, numero);
            break;
        case 'r':
            fscanf(stdin, "%d", &numero);
            removeNo(&arvore, numero);
            break;
        default:
            exit(1);
            break;
        }
        getchar();
    }
    return 0;
}