// #include <stdio.h>
// #include <stdlib.h>

// typedef struct {
//     int *valores;
//     int tamanho;
//     int proximo;
// } Heap;


// Heap * inicializa(int n) {
//     Heap *heap = malloc(sizeof(Heap));
//     if (heap == NULL) {printf("Não há memória!"); return NULL;}

//     heap->valores = malloc(sizeof(int) * n);
//     if (heap->valores == NULL) {printf("Não há memória!"); return NULL;}
    
//     heap->tamanho = n;
//     heap->proximo = 0;

//     return heap;
// }

// int Pai(int i) {return (i-1)/2;}
// int Filho_esquerdo(int i) {return 2*i + 1;}
// int Filho_direito(int i) {return 2*i + 2;}

// void subir(Heap *heap, int posicao) {
//     if (posicao != 0) {
//         int pai = Pai(posicao);
//         if (heap->valores[pai] > heap->valores[posicao]) {
//             int temporario = heap->valores[posicao];
//             heap->valores[posicao] = heap->valores[pai];
//             heap->valores[pai] = temporario;
//             subir(heap, pai);
//         }
//     }
// }

// void insere(Heap *heap, int x) {
//     if (heap->proximo == heap->tamanho) {printf("Não há memória!"); return;}
//     if (heap->proximo < heap->tamanho) {
//         heap->valores[heap->proximo] = x;
//         subir(heap, heap->proximo);
//         heap->proximo++;
//     }
// }

// void descer(Heap *heap, int posicao) {
//     int tamanho = heap->proximo;

//     int posicaoFilhoMenor = Filho_esquerdo(posicao);
//     if (posicaoFilhoMenor < tamanho) {
//         int posicaoFilhoDireita = posicaoFilhoMenor + 1;
//         if (posicaoFilhoDireita < tamanho) {
//             if (heap->valores[posicaoFilhoDireita] < heap->valores[posicaoFilhoMenor]) {
//                 posicaoFilhoMenor = posicaoFilhoDireita;
//             }
//         }
//         if (heap->valores[posicao] > heap->valores[posicaoFilhoMenor]) {
//             int temporario = heap->valores[posicao];
//             heap->valores[posicao] = heap->valores[posicaoFilhoMenor];
//             heap->valores[posicaoFilhoMenor] = temporario;
//             descer(heap, posicaoFilhoMenor);
//         }
//     }

// }

// int removeMin(Heap *heap) {
//     if (heap->proximo > 0) {
//         heap->proximo = heap->proximo - 1;
//         int x = heap->valores[0];
//         heap->valores[0] = heap->valores[heap->proximo];
//         descer(heap, 0);
//         return x;
//     }
//     return -1;
// }

// Heap * heapify(int *vetor, int numero_de_elementos) {
//     Heap *heap = malloc(sizeof(Heap));
//     if (heap == NULL) {printf("Não há memória!"); return NULL;}

//     heap->valores = &(*vetor);
//     heap->tamanho = numero_de_elementos;
//     heap->proximo = numero_de_elementos;

//     for (int i = 0; i <= numero_de_elementos - 1; i++) {
//         subir(heap, i);
//     }

//     return heap;
// }

// void printa(Heap *heap) {
//     printf("Heap: ");
//     for (int i = 0; i < heap->proximo; i++) {
//         printf(" [%d] ", heap->valores[i]);
//     }
//     printf("\n");
// }

// Heap * heapSort(int *vetor, int numero_de_elementos) {
//     Heap *heap = heapify(vetor, numero_de_elementos);
    
//     int posicao = numero_de_elementos - 1;
//     int valor;

//     while(posicao > 0) {
//         valor = heap->valores[0];
//         heap->valores[0] = heap->valores[posicao];
//         descer(heap, posicao);
//         posicao--;
//     }
    
//     return heap;
// }

// int main() {
//     int tamanho;
//     printf("Digite o tamanho: "); scanf("%d", &tamanho);
    
//     int *vetor = malloc(sizeof(int) * tamanho);

//     for(int i = 0; i < tamanho; i++) {
//         vetor[i] = i+1;
//     }

//     printf("Vetor: ");
//     for(int i = 0; i < tamanho; i++) {
//         printf(" [%d] ", vetor[i]);
//     }
//     printf("\n");


//     Heap *heap2 = heapSort(vetor, tamanho);
//     printa(heap2);

    
    


//     return 0;
// }