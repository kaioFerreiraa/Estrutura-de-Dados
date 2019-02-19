#ifndef ARQUIVOSCONTATO_H_
#define ARQUIVOSCONTATO_H_

char *caminhoDoArquivo = "contatos.txt";

FILE *contatosFile = NULL;

int inicializarArquivo() {
    contatosFile = fopen(caminhoDoArquivo, "r+");
    if (contatosFile == NULL) {
        printf("[INFO]inicializarArquivo: Nao foi possivel localizar o arquivo... Criando um novo...\n\n\n");
        contatosFile = fopen(caminhoDoArquivo, "w+");
        system("cls");
        if (contatosFile == NULL) {
            printf("[INFO]inicializarArquivo: Nao foi possivel iniciar o arquivo. Saindo...\n");
            exit(1);
        }
    }

    printf("[INFO]inicializarArquivo: Arquivo Inicializado com Sucesso! \n");
    system("pause");
    fclose(contatosFile);
    contatosFile = NULL;
    return 1;
}

void fecharArquivo() {
    fclose(contatosFile);
    contatosFile = NULL;
}

void inserir (contato pessoa, contato *le) {
    contato *novoContato;
    novoContato = malloc (sizeof (contato));

    strcpy(novoContato->nome, pessoa.nome);
    novoContato->id = pessoa.id;
    strcpy(novoContato->tipo, pessoa.tipo);
    novoContato->numero = pessoa.numero;
    strcpy(novoContato->email, pessoa.email);

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
}

void lerDoArquivo(contato *le) {
    contatosFile = fopen(caminhoDoArquivo, "r");
    if (contatosFile == NULL) {
        printf("[ERROR]lerDoArquivo: Falha ao abrir o arquivo.");
    }
    contato count;
    char numero[30];
    char id[30];

    while(fscanf(contatosFile, "%s %[^\n] %[^\n] %s %[^\n]\n", id, count.nome, count.tipo, numero, count.email) != EOF){
        count.id = atol(id);
        count.numero = atoll(numero);
        //printf("%li\n%s\n%s\n%lli\n", count.id, count.nome, count.tipo, count.numero); //AQUI O OBJETO cont esta pronto para ser inserido na lista
        inserir(count, le);
    }
    fecharArquivo();
}

void escreverContatoNoArquivo(contato *pessoa) {
    if(fprintf(contatosFile, "%li\n%s\n%s\n%lld\n%s\n\n", pessoa->id, pessoa->nome, pessoa->tipo, pessoa->numero, pessoa->email) <= 0) {
        printf("[ERRO]escreverContatoNoArquivo: Houve uma falha durante a escrita do contato.");
    }
}

void salvarNoFinalDoArquivo(contato *pessoa) {
    contatosFile = fopen(caminhoDoArquivo, "a");
    escreverContatoNoArquivo (pessoa);
    fecharArquivo();
}

void salvarAgenda(contato *agenda) {
    contato *aux = agenda->prox;
    contatosFile = fopen(caminhoDoArquivo, "w+");
    while (aux != agenda) {
        escreverContatoNoArquivo(aux);
        aux = aux->prox;
    }
    fecharArquivo();
}

#endif // ARQUIVOSCONTATO_H_
