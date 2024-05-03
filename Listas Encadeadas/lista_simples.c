//A lista implementada aqui não tem nó cabeça, é simplesmente encadeada, e não ordenada. 

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

typedef struct no {
	int dado; //podem ser tipos de dados diferentes
	struct no *proximo;
} No;

typedef struct {
	No *inicio;
	int tamanho;
}Lista;

void inicializarLista(Lista *l) {
	l->inicio = NULL;
	l->tamanho = 0;
}

bool insereLista(Lista *l, int x, int posicao) {
	if (posicao < 0 || posicao > l->tamanho) { 
		printf("\tPosicao invalida!\n");
		return false; 
	}
	
	No *novo = malloc(sizeof(No));
	if(!novo) {
		printf("\tAlocação de memória falhou!\n");
		return false;
	}
	
	novo->dado = x;
	if(posicao == 0) { //Queremos inserir no início
		novo->proximo = l->inicio;
		l->inicio = novo;
		l->tamanho++;
		return true;
	}

	No *aux = l->inicio; //Percorremos até 1 antes do local de inserção
	for (int i = 0; i < posicao - 1; i++) {
		aux = aux->proximo;
	}
	
	novo->proximo = aux->proximo;
	aux->proximo = novo;
	l->tamanho++;
	return true;
}

bool excluiLista(Lista *l, int posicao) {
	if (posicao < 0 || posicao >= l->tamanho) {
		printf("\tPosicao invalida!\n");
		return false;
	}
	
	if (l->inicio == NULL) {
		printf("\tA lista ja esta vazia!\n");
		return false;
	}
	
	No *apagar;
	if (posicao == 0) {
		apagar = l->inicio;
		l->inicio = apagar->proximo;
	}
	else {
		No *aux = l->inicio;
		for (int i = 0; i < posicao - 1; i++) {
			aux = aux->proximo;		
		}
		apagar = aux->proximo;
		aux->proximo = apagar->proximo;
	}
	
	free(apagar);
	l->tamanho--;
	return true;
}

void printLista(Lista *l) {
	No *aux = l->inicio;
	printf("Lista: ");
	while(aux != NULL) {
		printf(" [%d] ", aux->dado);
		aux = aux->proximo;
	}
	printf("\n");
}

int main() {
    Lista l;
    Lista *lista = &l;
    inicializarLista(lista);

    char comando;

    int x, pos;

    printf("Digite o comando: ");
    scanf("%c", &comando);
    while (comando != 'e') {
        switch (comando) {
        case 'i':
            printf("\tDigite o valor a ser inserido, e sua posicao: ");
            scanf("%d %d", &x, &pos);
            insereLista(lista, x, pos);
            break;
        case 'r':
            printf("\tDigite a posicao do valor a ser removido: ");
            scanf("%d", &pos);
            excluiLista(lista, pos);
            break;
        case 'p':
            printLista(lista);
            break;
        case 't':
            printf("%d", lista->tamanho);
            break;
        default:
            break;
        }
        while((getchar()) != '\n');

        printf("Digite o comando: ");
        comando = getchar();

    }
    
    return 0;
}