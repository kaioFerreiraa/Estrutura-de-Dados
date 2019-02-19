#ifndef STRUCTAGENDA_H_
#define STRUCTAGENDA_H_
#include <stdlib.h>

typedef struct Contato contato;

struct Contato {
	char nome [255];
	char tipo [25];
	long long numero;
	int id;
	char email [40];
	struct Contato *prox;
	struct Contato *ant;
};

#endif
