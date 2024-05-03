//A lista implementada aqui tem nó cabeça, é circular e duplamente encadeada, e ordenada em ordem crescente. 


#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

typedef struct no {
    int chave;
    struct no *proximo;
    struct no *anterior;
} No;

No *inicializaLista() {
    No *cabeca = malloc (sizeof(No));
    cabeca->proximo = cabeca;
    cabeca->anterior = cabeca;
    return cabeca;
}

void mostraLista(No *cabeca) {
    No *atual = cabeca->proximo;
    printf("Lista:");
    while(atual != cabeca) {
        printf(" [%d] ", atual->chave);
        atual = atual->proximo;
    }
    printf("\n");
}  

// No *buscaLista(No *cabeca, int x) {
//     No *posicao = cabeca->proximo;
//     while(posicao != cabeca && posicao->chave < x) {
//         posicao = posicao->proximo;
//     }    
//     if(posicao != cabeca && posicao->chave == x) {
//         return posicao;
//     }
//     else {
//         return NULL;
//     }
// }

// bool insereLista(No *cabeca, int x) {
//     No *posicao = buscaLista(cabeca, x);

//     if(posicao != NULL) {
//         return false; //Retornando falso pois não quero repetição de itens 
//     }

//     else {
//         No *novo = malloc (sizeof(No));

//         novo->chave = x;
//         novo->proximo = posicao;
//         novo->anterior = posicao->anterior;
//         posicao->anterior->proximo = novo;           
//         posicao->anterior = novo;
    

//         return true;
//     }
// }

// bool removeLista(No *cabeca, int x) {
//     No *posicao = buscaLista(cabeca, x);

//     if (posicao == cabeca || posicao == NULL) {
//         //Não achamos o valor!
//         return false;
//     }

//     else {
//         No *apagar = posicao; 
//         apagar->anterior->proximo = apagar->proximo;
//         apagar->proximo->anterior = apagar->anterior;
//         free(apagar);
//         return true;
//     }
// }

bool buscaLista(No *cabeca, No **posicao, int x) {
    *posicao = cabeca->proximo;
    while(*posicao != cabeca && (*posicao)->chave < x) {
        *posicao = (*posicao)->proximo;
    }
    if(*posicao != cabeca && (*posicao)->chave == x) {
        return true;
    }
    else {
        return false;
    }
}

bool insereLista(No *cabeca, int x) {
    No *posicao = cabeca;
    if(!buscaLista(cabeca, &posicao, x)) {
        No *novo = malloc(sizeof(No));
        novo->chave = x;
        novo->proximo = posicao;
        novo->anterior = posicao->anterior;
        posicao->anterior->proximo = novo;
        posicao->anterior = novo;
        return true;
    } 
    else return false;

}

bool removeLista(No *cabeca, int x) {
    No *apagar = cabeca;
    if(buscaLista(cabeca, &apagar, x)) {
        apagar->anterior->proximo = apagar->proximo;
        apagar->proximo->anterior = apagar->anterior;
        free(apagar);
        return true;
    }
    else return false;
}

int main() {
    No *ptlista = inicializaLista();
    
    mostraLista(ptlista);
    insereLista(ptlista, 1);
    insereLista(ptlista, 270);
    insereLista(ptlista, 3);
    insereLista(ptlista, 2);
    insereLista(ptlista, 150);
    insereLista(ptlista, 10);
    mostraLista(ptlista);

    removeLista(ptlista, 10);
    removeLista(ptlista, 1);
    removeLista(ptlista, 3);
    removeLista(ptlista, 2);
    removeLista(ptlista, 150);
    removeLista(ptlista, 10);
    removeLista(ptlista, 270);

    mostraLista(ptlista);


    return 0;
}