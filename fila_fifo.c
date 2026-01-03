#include "fila_fifo.h"

void f_inicializar(Fila_FIFO **f)
{
	(*f) = malloc(sizeof(Fila_FIFO));
	if(*f == NULL)return;
	
	(*f)->prim = NULL;
	(*f)->ult = NULL;
	(*f)->tamanho = 0;
}

NoFila *criar_no(int chave, int valor)
{
	NoFila *novo = malloc(sizeof(NoFila));
	if (novo == NULL) return NULL;
	
	novo->prox = NULL;
	novo->chave = chave;
	novo->valor = valor;
	
	return novo;
}

int f_inserir(Fila_FIFO **f,int chave, int valor)
{
	NoFila *novo = criar_no(chave,valor);
	if(novo == NULL) return 0;
	
	(*f)->tamanho += 1;
	if((*f)->prim == NULL)
	{
		(*f)->prim = novo;
		(*f)->ult = novo;
		return 1;
	}
	
	(*f)->ult->prox = novo;
	(*f)->ult = novo;
	return 1;
}

int f_obter_proxima_chave(Fila_FIFO **f)
{
	NoFila *remov = (*f)->prim;
	if (remov == NULL) return -1;
	
	(*f)->tamanho -= 1;
	int chave = remov->chave;
	if(remov == (*f)->ult)
	{
		(*f)->prim = NULL;
		(*f)->ult = NULL;
		free(remov);
		return chave;
	}
	
	(*f)->prim = (*f)->prim->prox;
	free(remov);
	return chave;
}

int f_consultar_proxima_chave(Fila_FIFO **f)
{
	if(*f == NULL) return -1;
	
	return (*f)->prim->chave;
}

int f_consultar_proximo_valor(Fila_FIFO **f)
{
	if(*f == NULL) return -1;
	
	return (*f)->prim->valor;
}

int f_num_elementos(Fila_FIFO **f)
{
	if((*f) == NULL) return 0;
	
	return (*f)->tamanho;
}

int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao)
{
	NoFila *p = (*f)->prim;
	int i = 1;
	while(p != NULL)
	{
		if(i == posicao) return p->chave;
		i++;
		p = p->prox;
	}
	return -1;
}

int f_consultar_valor_por_posicao(Fila_FIFO **f, int posicao)
{
	NoFila *p = (*f)->prim;
	int i = 1;
	while(p != NULL)
	{
		if(i == posicao) return p->valor;
		i++;
		p = p->prox;
	}
	return -1;
}
