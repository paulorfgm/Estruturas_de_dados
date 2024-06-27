#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *valores;
    int tamanho;
    int proximo;
} Heap;

Heap *inicializa(int n) {
    Heap *heap = malloc(sizeof(Heap));
    if (heap == NULL) {
        printf("Não há memória!\n");
        return NULL;
    }

    heap->valores = malloc(sizeof(int) * n);
    if (heap->valores == NULL) {
        printf("Não há memória!\n");
        free(heap);
        return NULL;
    }

    heap->tamanho = n;
    heap->proximo = 0;

    return heap;
}

int Pai(int i) {
    return (i - 1) / 2;
}

int Filho_esquerdo(int i) {
    return 2 * i + 1;
}

int Filho_direito(int i) {
    return 2 * i + 2;
}

void subir(Heap *heap, int posicao) {
    if (posicao != 0) {
        int pai = Pai(posicao);
        if (heap->valores[pai] > heap->valores[posicao]) {
            int temporario = heap->valores[posicao];
            heap->valores[posicao] = heap->valores[pai];
            heap->valores[pai] = temporario;
            subir(heap, pai);
        }
    }
}

void insere(Heap *heap, int x) {
    if (heap->proximo == heap->tamanho) {
        printf("Heap cheio!\n");
        return;
    }
    heap->valores[heap->proximo] = x;
    subir(heap, heap->proximo);
    heap->proximo++;
}

void descer(Heap *heap, int posicao) {
    int tamanho = heap->proximo;

    int posicaoFilhoMenor = Filho_esquerdo(posicao);
    if (posicaoFilhoMenor < tamanho) {
        int posicaoFilhoDireita = posicaoFilhoMenor + 1;
        if (posicaoFilhoDireita < tamanho && heap->valores[posicaoFilhoDireita] < heap->valores[posicaoFilhoMenor]) {
            posicaoFilhoMenor = posicaoFilhoDireita;
        }
        if (heap->valores[posicao] > heap->valores[posicaoFilhoMenor]) {
            int temporario = heap->valores[posicao];
            heap->valores[posicao] = heap->valores[posicaoFilhoMenor];
            heap->valores[posicaoFilhoMenor] = temporario;
            descer(heap, posicaoFilhoMenor);
        }
    }
}

int removeMin(Heap *heap) {
    if (heap->proximo > 0) {
        heap->proximo--;
        int x = heap->valores[0];
        heap->valores[0] = heap->valores[heap->proximo];
        descer(heap, 0);
        return x;
    }
    return -1;
}

Heap *heapify(int *vetor, int numero_de_elementos) {
    Heap *heap = inicializa(numero_de_elementos);
    if (heap == NULL) {
        printf("Não foi possível inicializar a heap!\n");
        return NULL;
    }

    for (int i = 0; i < numero_de_elementos; i++) {
        heap->valores[i] = vetor[i];
    }
    heap->proximo = numero_de_elementos;

    for (int i = heap->proximo / 2 - 1; i >= 0; i--) {
        descer(heap, i);
    }

    return heap;
}

void printa(Heap *heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->proximo; i++) {
        printf(" [%d] ", heap->valores[i]);
    }
    printf("\n");
}

void heapSort(int *vetor, int numero_de_elementos) {
    Heap *heap = heapify(vetor, numero_de_elementos);
    if (heap == NULL) {
        printf("Falha na criação da heap para heapSort!\n");
        return;
    }

    for (int i = numero_de_elementos - 1; i > 0; i--) {
        int temp = heap->valores[0];
        heap->valores[0] = heap->valores[i];
        heap->valores[i] = temp;
        heap->proximo--;
        descer(heap, 0);
    }

    for (int i = 0; i < numero_de_elementos; i++) {
        vetor[i] = heap->valores[i];
    }

    free(heap->valores);
    free(heap);
}

int main() {

    return 0;
}
