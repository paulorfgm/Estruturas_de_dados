//Arvore utilizada para uma série de exercícios, e pode ser desconsiderada

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

typedef struct no
{
    int chave;
    struct no *esquerda;
    struct no *direita;
    int soma_prefixo;
    int produto;
    struct no *sucessor;
    struct no *predecessor;
} No;

No *inicializaArvore() {
    No *raiz = NULL;
    return raiz;
}

void mostraSubArvore(No *raiz) {
    if(raiz) {
        mostraSubArvore(raiz->esquerda);
        printf("Valor: [%d], produto_prefixo: [%d] \n", raiz->chave, raiz->soma_prefixo);
        mostraSubArvore(raiz->direita);
    }
}

void mostraArvoreSoma(No *raiz) {
    int static soma = 0;
    if(raiz) {
        soma += raiz->chave;
        mostraArvoreSoma(raiz->esquerda);
        printf("Valor: [%d], Soma: [%d] \n", raiz->chave, soma);
        mostraArvoreSoma(raiz->direita);
    }
}

void mostraArvore(No *raiz) {
    printf("Arvore: ");
    mostraSubArvore(raiz);
    printf("\n");
}

No *novoNo(int x) {
    No *temporario = (No *) malloc(sizeof(No));
    temporario->chave = x;
    temporario->esquerda = NULL;
    temporario->direita = NULL;
    return temporario;
}

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

int quantidadeDeFilhos(No *raiz) {
    int quantidade = 0;
    if(raiz && raiz->esquerda) quantidade++;
    if(raiz && raiz->direita) quantidade++;
    return quantidade;
}

No *antecessor(No *raiz, No **pai) {
    while(raiz->direita) { *pai = raiz, raiz = raiz->direita; }
    return raiz;
}

bool removeRUIM(No *raiz, int x) {
    No *filho = NULL;
    No *pai = NULL;

    if(busca(raiz, &filho, &pai, x)) {
        int quantidade_de_filhos = quantidadeDeFilhos(filho);
        // printf("A quantidade de filhos do no [%d] eh: %d\n", filho->chave, quantidade_de_filhos);
        
        if(quantidade_de_filhos == 0) {
            if(pai->esquerda && pai->esquerda->chave == x) pai->esquerda = NULL;
            else pai->direita = NULL;
            free(filho);
            return true;
        }

        else if(quantidade_de_filhos == 1) {
            if(filho->esquerda) {
                if(pai->esquerda && pai->esquerda->chave == x) pai->esquerda = filho->esquerda;
                else pai->direita = filho->esquerda;
            }
            else {
                if(pai->esquerda && pai->esquerda->chave == x) pai->esquerda = filho->direita;
                else pai->direita = filho->direita;
            }
            // free(filho);
            return true;
        }

        else { //filhos == 2
            No *p = filho;
            No *ant = antecessor(filho->esquerda, &p);
            filho->chave = ant->chave;

            if(ant != (filho->esquerda)) {
                if(ant->esquerda) p->direita = ant->esquerda;
                else p->direita = NULL;
            }

            else {
                if(ant->esquerda) p->esquerda = ant->esquerda;
                else p->esquerda = NULL;
            }

            free(ant);
            return true;
        }

    }
    else return false;
}

bool remove2(No **raiz, int x) {
    No *pai = NULL, *filho = *raiz;
    if(busca(*raiz, &filho, &pai, x)) { //Achou
        //Remover chave do filho:
        
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

int somaPreFixo(No *raiz) {
    int static somatorio = 0;
    if(raiz) {
        somaPreFixo(raiz->esquerda);
        somatorio += raiz->chave;
        raiz->soma_prefixo = somatorio;
        somaPreFixo(raiz->direita);
    }
    else return 0;
}

int produto(No *raiz) {
    long long static produtorio = 1;
    if(raiz) {
        produtorio = produto(raiz->esquerda);
        produtorio *= raiz->chave;
        produto(raiz->direita);
        return produtorio;

        produto(raiz->esquerda);
        produtorio *= raiz->chave;
        raiz->produto = produtorio;
        produto(raiz->direita);
    }
    else return 1;
}

int Produtorio(No *raiz) {
    if(raiz == NULL) return 1;
    else {
        raiz->produto = raiz->chave * Produtorio(raiz->esquerda);
        if(raiz->esquerda) {
            raiz->produto *= Produtorio(raiz->esquerda->direita);
        }
        return raiz->chave;
    }
}

int Produtorio2(No *raiz) {
    int static produtorio = 1;
    if(raiz) {
        raiz->produto = Produtorio2(raiz->esquerda) * raiz->chave;
        if(raiz->esquerda != NULL) {
            raiz->produto *= Produtorio2(raiz->esquerda->direita);
        }
        Produtorio2(raiz->direita);
        return raiz->produto;
    }
    else return 1;
}



int main() {
    No *raiz = inicializaArvore();

    mostraArvore(raiz);

    insere(&raiz, 55);
    insere(&raiz, 10);
    insere(&raiz, 3);
    insere(&raiz, 25);
    insere(&raiz, 63);
    insere(&raiz, 60);
    insere(&raiz, 77);
    insere(&raiz, 59);
    insere(&raiz, 100);

    somaPreFixo(raiz);

    mostraArvore(raiz);

    return 0;
}