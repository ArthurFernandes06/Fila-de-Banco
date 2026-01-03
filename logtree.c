#include "logtree.h"
void inicializar(Log **l)
{
	(*l) = NULL;
}
Log *criar_no(int conta, int classe, int timer, int caixa)
{
	Log *novo = malloc(sizeof(Log));
	if (novo == NULL) return NULL;
	
	//Info da arvore RB
	novo->dir = NULL;
	novo->esq = NULL;
	
	//data
	novo->conta = conta;
	novo->classe = classe;
	novo->caixa = caixa;
	novo->tempo = timer;
}

int log_registrar(Log **l, int conta, int classe, int timer, int caixa)
{
	Log *novo = criar_no(conta,classe,timer,caixa);
	if (novo == NULL) return 0;
	
	Log *p = (*l);
	Log *p_pai = NULL;
	while(p != NULL)
	{
		p_pai = p;
		if(conta > p->conta) p = p->dir;
		else p = p->esq;
	}
	
	if(p_pai == NULL)
	{
			(*l) = novo;
			return 1;
	}
	
	if(conta > p_pai->conta) p_pai->dir = novo;
	else p_pai->esq = novo;
	return 1;
}

int log_obter_soma_por_classe(Log **l, int classe)
{
	if(*l != NULL)
	{
		if((*l)->classe == classe) return log_obter_soma_por_classe(&(*l)->dir,classe) + log_obter_soma_por_classe(&(*l)->esq,classe) + (*l)->tempo;
		else return log_obter_soma_por_classe(&(*l)->dir,classe) + log_obter_soma_por_classe(&(*l)->esq,classe);
			
	}else
	{
		return 0;
	}
}

int log_obter_contagem_por_classe(Log **l, int classe)
{
	if(*l != NULL)
	{
		if((*l)->classe == classe) return log_obter_contagem_por_classe(&(*l)->dir,classe) + log_obter_contagem_por_classe(&(*l)->esq,classe) + 1;
		else return log_obter_contagem_por_classe(&(*l)->dir,classe) + log_obter_contagem_por_classe(&(*l)->esq,classe);
			
	}else
	{
		return 0;
	}
}

float log_media_por_classe(Log **l, int classe)
{
	int total = log_obter_contagem_por_classe(l,classe);
	if (total == 0) return 0;
	
	return log_obter_soma_por_classe(l,classe)/total;
}
