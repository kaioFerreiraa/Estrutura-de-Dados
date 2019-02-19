#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

typedef struct registro celula;

struct registro{
    int conteudo;
    struct registro *prox;
};

celula *fi;

// A função cria a cabeça de uma fila

void criarfila () {
    fi = malloc (sizeof (celula));
    fi->prox = fi;
}

// coloca um inteiro x no final da fila

void colocanafila (int x) {
    celula *nova;
    nova = malloc (sizeof (celula));
    fi->conteudo = x;
    nova->prox = fi->prox;
    fi->prox = nova;
    fi = fi->prox;
}

// A função tira a primeiro celula da fila
// e retorna valor dele

int tiradafila () {
    celula *p;
    p = fi->prox;
    int x = p->conteudo;
    fi->prox = p->prox;
    free(p);
    return x;
}

// A função recebe uma celula cabeça e
// um inteiro n e insere n na lista encadeada

void inserirnaLista (celula *le, int n) {
    celula *nova = malloc (sizeof (celula));
    nova->conteudo = n;
    if (le->prox == NULL) {
        nova->prox = le->prox;
        le->prox = nova;
    } else {
        celula *p = le->prox;
        while (p->prox != NULL) p = p->prox;
        nova->prox = p->prox;
        p->prox = nova;
    }
}

// A função recebe uma matriz, uma cidade c, o numero
// de cidades e a uma celula cabeça, e calcula a diistancia
// da cidade c para todas as outras cidades

void distancias (elemento *ma, int c, int n, celula *le) {
    c;
    celula *aux;
    for (int j = 0; j < n; j++) {
        if (j == c) inserirnaLista(le, 0);
        else inserirnaLista(le, n);
    }
    criarfila();
    colocanafila(c);

    while (fi->prox != fi) {
        int i = tiradafila();

        aux = le->prox;
        for (int cont = 0; cont < i; cont++) aux = aux->prox;

        celula *p = le->prox;

        for (int j = 0; j < n; j++, p = p->prox) {
            int valor = buscaMatriz(i, j, ma);

            if (valor == 1 && p->conteudo >= n) {
                p->conteudo = aux->conteudo + 1;
                colocanafila(j);
            }
        }
    }
}

int main () {
    celula *le = malloc (sizeof (celula));
    le->prox = NULL;

    elemento *ma = malloc (sizeof (elemento));
    ma->abaixo = NULL;
    ma->prox = criarMatriz(6, 6);


    preencheMatriz (ma, 0, 1, 1);
    preencheMatriz (ma, 0, 2, 0);
    preencheMatriz (ma, 0, 3, 0);
    preencheMatriz (ma, 0, 4, 0);
    preencheMatriz (ma, 0, 5, 0);
    preencheMatriz (ma, 1, 0, 0);
    preencheMatriz (ma, 1, 1, 0);
    preencheMatriz (ma, 1, 2, 1);
    preencheMatriz (ma, 1, 3, 0);
    preencheMatriz (ma, 1, 4, 0);
    preencheMatriz (ma, 1, 5, 0);
    preencheMatriz (ma, 2, 0, 0);
    preencheMatriz (ma, 2, 1, 0);
    preencheMatriz (ma, 2, 2, 0);
    preencheMatriz (ma, 2, 3, 0);
    preencheMatriz (ma, 2, 4, 1);
    preencheMatriz (ma, 2, 5, 0);
    preencheMatriz (ma, 3, 0, 0);
    preencheMatriz (ma, 3, 1, 0);
    preencheMatriz (ma, 3, 2, 1);
    preencheMatriz (ma, 3, 3, 0);
    preencheMatriz (ma, 3, 4, 1);
    preencheMatriz (ma, 3, 5, 0);
    preencheMatriz (ma, 4, 0, 1);
    preencheMatriz (ma, 4, 1, 0);
    preencheMatriz (ma, 4, 2, 0);
    preencheMatriz (ma, 4, 3, 0);
    preencheMatriz (ma, 4, 4, 0);
    preencheMatriz (ma, 4, 5, 0);
    preencheMatriz (ma, 5, 0, 0);
    preencheMatriz (ma, 5, 1, 1);
    preencheMatriz (ma, 5, 2, 0);
    preencheMatriz (ma, 5, 3, 0);
    preencheMatriz (ma, 5, 4, 0);
    preencheMatriz (ma, 5, 5, 0);



    printf("Cid:\t0\t1\t2\t3\t4\t5\n");
    printf("===================================================\n");
    imprimeMatriz(ma);
    printf("===================================================\n\n\n");

    int c;

    printf("Digite a Cidade: ");
    scanf("%d", &c);

    if (c > 5 || c < 0) printf("Cidade invalida");
    else {
        distancias(ma, c, 6, le);

        printf("\n\n\nCid:\t\t0\t1\t2\t3\t4\t5\n");
        printf("==========================================================\n");
        printf("Dist cid %d:", c);

        for (celula *p = le->prox; p != NULL; p = p->prox) printf("\t%d ", p->conteudo);

        printf("\n==========================================================\n");
    }


return 0;
}
