#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structagenda.h"
#include "arquivoscontato.h"

int cont = 0;

int contContatos = 0;

contato *remover (contato *le, contato *aux) {
    contato *p = aux->ant;
    contato *q = aux;

    aux = aux->prox;

    p->prox = aux;
    aux->ant = p;

    free(q);

    contContatos--;

    return le->prox;
}

// A função recebe uma celula e edita
// seu numero, tipo, nome ou e-mail

void editar (contato *le) {
    int opcao;

    printf("\n\n Editar: ");
    printf("\n 1-Nome\n 2-Tipo\n 3-Numero\n 4-E-mail\n Opcao: ");
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            fflush(stdin);
            printf("\n Nome: ");
            gets(le->nome);
            le->nome[0] = towupper(le->nome[0]);
            for (int j = 1; j < strlen(le->nome); j++) le->nome[j] = tolower(le->nome[j]);
            break;
        case 2:
            fflush(stdin);
            printf("\n Tipo: ");
            gets(le->tipo);
            le->tipo[0] = towupper(le->tipo[0]);
            for (int j = 1; j < strlen(le->tipo); j++) le->tipo[j] = tolower(le->tipo[j]);
            break;
        case 3:
            fflush(stdin);
            printf("\n Numero: ");
            scanf("%lld", &le->numero); break;
        case 4:
            fflush(stdin);
            printf("\n E-mail: ");
        gets(le->email); break;
        default: printf("\n Opcao Invalida");
    }
}

// A função recebe duas celulas e a cabeça da lista
// e organiza elas por nome, tipo ou id

void organizar_lista (contato *pont, contato *pontAux, contato *le) {
    pontAux->prox = pont->prox;
    pont->ant = pontAux->ant;
    pont->prox = pontAux;
    pontAux->ant = pont;
    pont = pont->ant;
    pont->prox = pontAux->ant;
    pontAux = pontAux->prox;
    pont = pont->prox;
    pontAux->ant = pont->prox;
}

// A função recebe a cabeça de uma lista encadeada
// e adiciona novas celulas nessa lista

void adicionar (contato *le){
	system("cls");

	contContatos = 0;

	contato *novoContato;
	novoContato = malloc (sizeof (contato));

	if (le->prox != NULL) {
        for (contato *p = le->prox; p != le; p = p->prox) {
            if (p->id >= cont) cont = p->id;
            contContatos++;
	}
	}

    cont++;

	fflush(stdin);
	printf("\n%d.Nome do contato: ", cont);
	gets(novoContato->nome);
	novoContato->nome[0] = towupper(novoContato->nome[0]);
	for (int j = 1; j < strlen(novoContato->nome); j++) novoContato->nome[j] = tolower(novoContato->nome[j]);

	novoContato->id = cont;

	fflush(stdin);
	printf("\nTipo: ");
	gets(novoContato->tipo);
	novoContato->tipo[0] = towupper(novoContato->tipo[0]);
    for (int j = 1; j < strlen(novoContato->tipo); j++) novoContato->tipo[j] = tolower(novoContato->tipo[j]);


	fflush(stdin);
	printf("\nNumero: ");
	scanf("%lld", &novoContato->numero);

    fflush(stdin);
	printf("\nE-mail: ");
	gets(novoContato->email);

	if (le->prox == NULL) {
        novoContato->prox = le;
        novoContato->ant = le;
        le->prox = novoContato;
        le->ant = novoContato;
	} else {
	    contato *aux;
	    aux = le->prox;
	    while (aux->prox != le) {
            aux = aux->prox;
	    }
	    novoContato->prox = aux->prox;
	    novoContato->ant = aux;
	    le->ant = novoContato;
	    aux->prox = novoContato;
	}
	salvarNoFinalDoArquivo (novoContato);
	contContatos++;
}

void contatos ();
void ordena_nome ();
void ordena_tipo ();
void ordena_id ();

// A função recebe uma celula e imprime os conteudo dela

void imprime (contato *le) {
    printf("\n\n-------------CONTATOS----------------\n");

    printf("\n ID: %d", le->id);
    printf("\n Nome: %s", le->nome);
    printf("\n Tipo: %s", le->tipo);
    printf("\n Numero: %lld", le->numero);
    printf("\n E-mail: %s", le->email);
    printf("\n--------------------------------------\n");
}

// A função recebe uma celula e a cabeça de uma lista encadeada
// e da opçoes de de configuração para essa celula

int opcao_contatos (contato *aux, contato *le) {
    int opcao;

    printf("\n 1-Editar\n 2-Remover\n 3-Prox. Contato\n 4-Contato Anterior\n 5-Voltar Menu\n Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            editar (aux);
            salvarAgenda (le);
            system("cls");
            break;
        case 2:
            aux = remover (le, aux);
            salvarAgenda (le);
            system("cls");
            break;
        case 3:
            system("cls");
            break;
        case 4:
            system("cls");
            break;
        case 5:
            break;
        default:
            printf("\n Opcao Invalida!"); break;
    }
    return opcao;
}

// A função recebe a cabeça de uma lista encadeada
// e faz uma busca na lista do nome ou tipo digitado

void buscar(contato *le){
	char busca[255];
	int opc;
	int i = 0;

	contato *aux = le->prox;

	system("cls");

	printf("\n\n Buscar Contato por: ");
	printf("\n 1. Nome \t 2. Tipo: \n Opcao: ");
	scanf("%d", &opc);

	if (opc == 1) {
        char nomeAux[30];
        int opcao;

        fflush(stdin);
        printf("\n\n Digite o nome do contato: ");
        gets(busca);

        busca[0] = towupper(busca[0]);
        for (int j = 1; j < strlen(busca); j++) busca[j] = tolower(busca[j]);


        if (le->prox == NULL || le->prox == le) printf("\n\t Sem Contatos!\n");

        else {
            while  (aux != NULL) {
                for (int j = 0; j < strlen(aux->nome); j++) {
                    if (aux->nome[j] == ' ') break;
                    else {
                        nomeAux[j] = aux->nome[j];
                        nomeAux[j+1] = '\0';
                    }
                }

                if ((strcmp(busca, aux->nome)) == 0 || (strcmp(busca, nomeAux)) == 0) {

                    imprime (aux);

                    opcao = opcao_contatos (aux, le);

                    if (opcao == 2) {
                        i--;
                        aux = le->prox;
                        if (aux == le) {
                            break;
                        }
                    } else if (opcao == 3) {
                        aux = aux->prox;
                        i = 1;
                        if (aux == le) aux = aux->prox;
                    } else if (opcao == 4) {
                        aux = aux->ant;
                        while ((strcmp(busca, aux->nome)) != 0) {
                            aux = aux->ant;
                        }
                        if ((strcmp(busca, aux->nome)) == 0) continue;
                        i = 1;
                        if (aux == le) aux = aux->ant;
                    } else if (opcao == 5){
                        i = 1; break;
                    }

                } else {
                    aux = aux->prox;
                    if (aux == le && i < 1) break;
                }
            }
            if (i < 1) printf("\n\n\t Contato Nao Encontrado\n\n");

        }
    } else if (opc == 2) {
        int opcao;

        fflush(stdin);
        printf("\n\n Digite o tipo do contato: ");
        gets(busca);

        busca[0] = towupper(busca[0]);
        for (int j = 1; j < strlen(busca); j++) busca[j] = tolower(busca[j]);


        if (le->prox == NULL || le->prox == le) printf("\n\t Sem Contatos\n");

        else {
            while  (aux != NULL) {
                if ((strcmp(busca, aux->tipo)) == 0) {
                    imprime (aux);

                    opcao = opcao_contatos (aux, le);

                    if (opcao == 2) {
                        aux = le->prox;
                        i--;
                        if (aux == le) {
                            break;
                        }
                    } else if (opcao == 3) {
                        i = 1;
                        aux = aux->prox;
                        if (aux == le) aux = aux->prox;
                    } else if (opcao == 4) {
                        aux = aux->ant;
                        while ((strcmp(busca, aux->tipo)) != 0) {
                            aux = aux->ant;
                        }
                        if ((strcmp(busca, aux->tipo)) == 0) continue;
                        i = 1;
                        if (aux == le) aux = aux->ant;
                    } else if (opcao == 5){
                        i = 1;
                        break;
                    }

                } else {
                    aux = aux->prox;
                    if (aux == le && i < 1) break;
                }
            }
            if (i < 1) printf("\n\n\t Contato Nao Encontrado\n\n");
        }
    } else printf("\n\n Entrada invalida\n\n");
}

// A função recebe uma celula e a cabeça de uma lista encadeada
// e imprime seu conteudo e as opcoes de confguração para o conteudo

void aux_imprime (contato *aux, contato *le) {
    int opcao;

    while (aux != NULL) {
        if (aux != le) {
            printf("\n Contatos Total: %d\n\n", contContatos);

            imprime (aux);
            opcao = opcao_contatos (aux, le);

            if (opcao == 2) {
                aux = le->prox;
                if (aux == le) {
                    printf("\n\t Sem Contatos!\n"); break;
                }
            } else if (opcao == 3) {
                aux = aux->prox;
                if (aux == le) aux = aux->prox;
            } else if (opcao == 4) {
                aux = aux->ant;
                if (aux == le) aux = aux->ant;
            } else if (opcao == 5) break;
        } else aux = aux->prox;
    }
}

int main(){
    system("color F0");

    inicializarArquivo();

    contato *le;

    le = malloc (sizeof (contato));

    le->prox = NULL;
    le->ant = NULL;

    lerDoArquivo (le);

	int opc;

	do{
		system("cls");

		printf(" MENU DA AGENDA TELEFONICA\n\n");
		printf(" 1 - Adicionar numero\n\n");
		printf(" 2 - Buscar\n\n");
		printf(" 3 - Ver todos os contatos\n\n");
		printf(" 4 - Sair\n\n");
		printf(" Opcao: ");
		scanf("%d", &opc);

		switch(opc){
		case 1:
			adicionar(le);
			printf("\n");
			system("pause");
			break;

		case 2:
			buscar(le);
			printf("\n");
			system("pause");
			break;

		case 3:
			contatos(le);
			printf("\n");
			system("pause");
			break;
		}
	}while(opc!=4);

	if (le->prox != NULL) {
        salvarAgenda(le);
	}

	return 0;
}

// A função recebe a cabeça de uma lista encadeada e
// da opçoes da forma de listagem do conteudo da lista encadeada

void contatos (contato *le) {
    system("cls");
    printf("\n\n-------------CONTATOS---------------\n");

    contato *aux = le;
    int option;

    printf(" Listar por: ");
    printf("\n\n 1. Ordem Alfabetica\n 2. Tipo\n 3. ID\n\n Opcao: ");
    scanf("%d", &option);

    switch (option) {
    case 1:
        ordena_nome (aux);
        printf("\n\n");
        break;
    case 2:
        ordena_tipo (aux);
        printf("\n\n");
        break;
    case 3:
        ordena_id (aux);
        printf("\n\n");
        break;
    }
}

// A função recebe uma lista encadeada e imprime o conteudo
// dela por ordem alfabetica do nome

void ordena_nome (contato *le) {
    system ("cls");

    if (le->prox == NULL || le->prox == le) printf("\n\t Sem Contatos!\n");

    else {
        contato *pontAux = le->prox;
        contato *pont = pontAux->prox;
        while (pont != le) {
            if ((strcmp(pont->nome, pontAux->nome)) < 0) {

                organizar_lista (pont, pontAux, le);

                pontAux = le->prox;
                pont = pontAux->prox;

            } else {
                pontAux = pontAux->prox;
                pont = pont->prox;
            }
        }

        contato *aux = le->prox;

        aux_imprime (aux, le);
    }
}

// A função recebe uma lista encadeada e imprime o
// conteudo dela por ordem de armazenamento

void ordena_id (contato *le) {
    system ("cls");

    if (le->prox == NULL || le->prox == le) printf("\n\t Sem Contatos!\n");

    else {
        contato *pontAux = le->prox;
        contato *pont = pontAux->prox;
        while (pont != le) {
            if (pont->id < pontAux->id) {

                organizar_lista (pont, pontAux, le);

                pontAux = le->prox;
                pont = pontAux->prox;
            } else {
                pontAux = pontAux->prox;
                pont = pont->prox;
            }
        }

        contato *aux = le->prox;

        aux_imprime (aux, le);
    }
}

// A função recebe uma lista encadeada e imprime
// seu conteudo por tipos de contato

void ordena_tipo (contato *le) {
    system ("cls");

    if (le->prox == NULL || le->prox == le) printf("\n\t Sem Contatos!\n");

    else {
        contato *pontAux = le->prox;
        contato *pont = pontAux->prox;

        while (pont != le) {

            if ((strcmp(pont->tipo, pontAux->tipo)) < 0) {

                organizar_lista (pont, pontAux, le);

                pontAux = le->prox;
                pont = pontAux->prox;

            } else {
                pontAux = pontAux->prox;
                pont = pont->prox;
            }
        }

        contato *aux = le->prox;


        aux_imprime (aux, le);
    }
}
