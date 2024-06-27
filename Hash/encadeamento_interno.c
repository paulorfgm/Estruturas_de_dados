#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

#define TAMANHO_HASH 20
// #define INICIO_COLISAO 10 

typedef struct {
    int chave;
    int proximo;
} No;

typedef No * Hash;

int led = TAMANHO_HASH;

int funcaoHash(int x) {
    return x;
}

int h(int x) {
    return (funcaoHash(x) % TAMANHO_HASH);
}

Hash inicializa(int tamanho) {
    Hash hash = malloc(sizeof(No) * 2 * tamanho);

    //Hash normal
    for(int i = 0; i < tamanho; i++) {
        hash[i].proximo = -2;   
    }

    //Área de colisão
    for(int i = tamanho; i < 2*tamanho - 1; i++) {
        hash[i].proximo = i + 1;
    }

    hash[2*tamanho-1].proximo = -1;

    led = tamanho;

    return hash;
}

bool posicaoLivre(Hash hash, int posicao) {
    return (hash[posicao].proximo == -2);
}

int busca(Hash hash, int x) {
    int posicao = h(x);
    int atual = -1;

    if(!posicaoLivre(hash, x)) {
        atual = posicao;
        while(atual != -1 && hash[atual].chave != x) {
            atual = hash[atual].proximo;
        }
    }
    
    return atual;
}

bool insere(Hash hash, int x) {
    int posicao = h(x);
    
    int atual = busca(hash, x);

    if (atual == -1) {
        if (posicaoLivre(hash, posicao)) {
            hash[posicao].chave = x;
            hash[posicao].proximo = -1;
        }
        else {
            if (led == -1) {
                //Tabela cheia! overflow!!!
                return false;
            }
            
            int novaPosicao = led;


            led = hash[novaPosicao].proximo;
            hash[novaPosicao].proximo = hash[posicao].proximo;
            hash[posicao].proximo = novaPosicao;
            hash[novaPosicao].chave = x;
        }
    }
    
}

bool remove(Hash hash, int x) {
    int posicao = h(x);
    
    int atual = busca(hash, x);

    if (atual != -1) {
        
    } 

}


int main() {



    return 0;
}