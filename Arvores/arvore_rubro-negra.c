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
    // struct no *pai; //fiz cada nó apontar para seu pai, para facilitar. 
} No;

//ASSINATURA DAS FUNÇÕES BÁSICAS DE ÁRVORE
No *inicializaArvore();
No *novoNo(int x);
void mostraArvore(No *raiz);

//ASSINATURA DAS FUNÇÕES DE ROTAÇÃO
No *rotacaoEsquerda(No *raiz);
No *rotacaoDireita(No *raiz);
No *rotacaoDuplaEsquerda(No *raiz);
No *rotacaoDuplaDireita(No *raiz);

//ASSINATURA DAS FUNÇÕES DE ÁRVORE RUBRO-NEGRA
bool insereRN(No **raiz, int x);
void consertaRN(No **raiz, No **filho);

int main() {
    No *arvore = inicializaArvore();
    char operacao;
    int numero;

    while(fscanf(stdin, "%c", &operacao) && !feof(stdin)) {
        switch (operacao) {
        case 'p':
            mostraArvore(arvore);
            printf("\n");
            break;
        case 'i':
            fscanf(stdin, "%d", &numero);
            insereRN(&arvore, numero);
            break;
        default:
            exit(1);
            break;
        }
        getchar();
    }
    return 0;
}

//DEFINIÇÕES DAS FUNÇÕES BÁSICAS DE ÁRVORE
No *inicializaArvore() {
    No *raiz = NULL;
    return raiz;
}

No *novoNo(int x) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {printf("Nao ha memoria, finalizando...\n"); exit(1);}
    novo->chave = x;
    novo->cor = rubro;
    novo->esquerda = NULL;
    novo->direita = NULL;
    // novo->pai = NULL;
    return novo;
}

No *buscaPai(No *raiz, int x) {
    No *pai = NULL;
    No *atual = raiz;

    while(atual != NULL && atual->chave != x) {
        pai = atual;
        if (x < atual->chave) atual = atual->esquerda;
        else atual = atual->direita;  
    }

    return pai;
}

void mostraArvore(No *raiz) {
    if(raiz != NULL) {
        printf("%d%c ", raiz->chave, raiz->cor);
        mostraArvore(raiz->esquerda);
        mostraArvore(raiz->direita);
    }
}

//IMPLEMENTAÇÃO DAS FUNÇÕES DE ROTAÇÃO
No *rotacaoEsquerda(No *raiz) {
    No *raiz_b, *arvore_2;

    raiz_b = raiz->direita;
    arvore_2 = raiz_b->esquerda;

    raiz_b->esquerda = raiz;
    raiz->direita = arvore_2;

    // if(raiz_b->chave < pai->chave) pai->esquerda = raiz_b;
    // else pai->direita = raiz_b;

    // // raiz_b->pai = raiz->pai;
    // // raiz->pai = raiz_b;
    // // if(arvore_2 != NULL) arvore_2->pai = raiz;

    // No *bisavo = buscaPai(raiz, raiz->chave);
    // char direcao = (bisavo->esquerda == raiz) ? 'e' : 'd';

    // No *raiz_b = raiz->direita;
    // No *arvore2 = raiz_b->esquerda;

    // raiz_b->esquerda = raiz;
    // raiz->direita = arvore2;

    // if(direcao == 'e') bisavo->esquerda = raiz_b;
    // else bisavo->direita = raiz_b;
    return raiz_b;
}

No *rotacaoDireita(No *raiz) {
    No *raiz_b, *arvore_2;

    raiz_b = raiz->esquerda;
    arvore_2 = raiz_b->direita;

    raiz_b->direita = raiz;
    raiz->esquerda = arvore_2;

    // raiz_b->pai = raiz->pai;
    // raiz->pai = raiz_b;
    // if(arvore_2 != NULL) arvore_2->pai = raiz;


    return raiz_b;
}

No *rotacaoDuplaEsquerda(No *raiz) {
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
}

No *rotacaoDuplaDireita(No *raiz) {
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
}

//IMPLEMENTAÇÃO DAS FUNÇÕES DE RN
bool insereRN(No **raiz, int x) {
    No *pai = NULL;
    No *filho = (*raiz);

    while(filho != NULL) {
        pai = filho;
        if(x < filho->chave) filho = filho->esquerda;
        else if(x > filho->chave) filho = filho->direita;
        else return false; //Já consta!
    }

    No *novo = novoNo(x);
    
    if(pai == NULL) {
        novo->cor = negro; //A raiz sempre será negra!
        (*raiz) = novo;
        return true;
    }
    else {
        if (x < pai->chave) pai->esquerda = novo;
        else pai->direita = novo;
        // novo->pai = pai;
        consertaRN(&(*raiz), &novo);
    }
    return true;
}

//Provavelmente há como melhorar este código, especialmente na parte da detecção da rotação. 
void consertaRN(No **raiz, No **filho) {
    No *pai = buscaPai(*raiz, (*filho)->chave);

    if (pai == NULL) return; //Estamos na raiz, e não há nada para consertar

    if(((*filho)->cor = rubro) && (pai->cor == rubro)) {
        if(pai == (*raiz)) pai->cor = negro;
        else {
            No *avo = buscaPai(*raiz, pai->chave);
            No *tio = (avo->esquerda == pai) ? avo->direita : avo->esquerda;
            if (tio != NULL && tio->cor == rubro) {
                avo->cor = rubro;
                pai->cor = negro;
                tio->cor = negro;
                if(avo == (*raiz)) avo->cor = negro; //A raiz sempre será negra!
                consertaRN(&(*raiz), &avo);
            }
            else {
                //Detectamos a rotação que deve ser feita, e atualizamos o ponteiro "filho":
                if (avo->direita == pai && pai->direita == *filho) {
                    (*filho) = rotacaoEsquerda(avo);
                    avo->cor = rubro;
                    pai->cor = negro;
                }
                else if (avo->direita == pai && pai->esquerda == *filho) {
                    *filho = rotacaoDuplaEsquerda(avo);
                    avo->cor = rubro;
                    (*filho)->cor = negro;
                }
                else if (avo->esquerda == pai && pai->direita == *filho) {
                    *filho = rotacaoDuplaDireita(avo);
                    avo->cor = rubro;
                    (*filho)->cor = negro;
                }
                else if (avo->esquerda == pai && pai->esquerda == *filho) {
                    *filho = rotacaoDireita(avo);
                    pai->cor = negro;
                    avo->cor = rubro;
                }

                //Tendo rotacionado, pegamos o pai do ponteiro filho, e checamos se "filho" é a raiz. 
                //Se não for, então fazemos o pai do filho apontar para ele.
                // pai = buscaPai(*raiz, (*filho)->chave);
                pai = buscaPai(*raiz, avo->chave); 
                // (*filho)->pai;
                if(pai == NULL) *raiz = *filho;
                else if((*filho)->chave < pai->chave) pai->esquerda = (*filho);
                else pai->direita = (*filho);  

            }
        }    
    }
    else return;   
}