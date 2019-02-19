#ifndef MATRIZ_H_
#define MATRIZ _H_

typedef struct reg elemento;

struct reg {
    int valor;
    elemento *abaixo;
    elemento *prox;
};

//A função recebe dois numeros inteiros
// e faz uma matriz de n linhas e n colunas

elemento *criarMatriz (int linhas, int colunas) {
    int l = 0;
    int c = 0;

    elemento *q = NULL;
    elemento *aux = NULL;
    elemento *prim = NULL;
    elemento *inicio = NULL;


    for (l; l < linhas; l++) {
        aux = NULL;
        c = 0;
        for (c; c < colunas; c++) {
            elemento *novo;
            novo = malloc (sizeof (elemento));
            novo->valor = 0;
            novo->prox = NULL;
            novo->abaixo = NULL;

            if (inicio == NULL) {
                inicio = novo;
            }
            if (aux != NULL) {
                novo->prox = aux->prox;
                aux->prox = novo;
            }
            aux = novo;

            if (q != NULL) {
                int i;
                elemento *p = q;
                for (i = 0; i < c; i++) p = p->prox;

                novo->abaixo = p->abaixo;
                p->abaixo = novo;
            }

            if (c == 0){
              prim = novo;
              //printf("%d ", prim->valor);
            }
        }
        q = prim;
        //printf("%d ", ant->valor);
    }

    return inicio;
}

// A função recebe o elemento cabeça, um inteiro
// linha, um inteiro coluna e inteiro x e preenche
// a a linha e coluna desejada com o valor x

void preencheMatriz (elemento *ma, int linhas, int coluna, int x) {
    int i = 0;
    elemento *aux  = ma->prox;
    for (i = 0; i < linhas; i++) aux = aux->abaixo;
    for (i = 0; i < coluna; i++) aux = aux->prox;
    aux->valor = x;
}

// imprime os valores da matriz

void imprimeMatriz (elemento *ma) {
    elemento *aux = ma->prox;
    elemento *p = ma->prox;
    while (p != NULL) {
        printf("\t%d", p->valor);

        p = p->prox;

        if (p == NULL) {
            printf("\n");
            p = aux->abaixo;
            aux = aux->abaixo;
        }
    }
}

// A função faz uma busca na linha e coluna
// desejada e retorna o valor encontrado nela

int buscaMatriz (int linha, int coluna, elemento *ma) {
    elemento *p = ma->prox;
    for (int l = 0; l < linha; l++) p = p->abaixo;
    for (int c = 0; c < coluna; c++) p = p->prox;

    return p->valor;
}

#endif
