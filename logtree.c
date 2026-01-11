#include "logtree.h"
void inicializar(Log **l)
{
	(*l) = NULL;
}
Log *criar_no_log(int conta, int classe, int timer, int caixa)
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
	Log *novo = criar_no_log(conta,classe,timer,caixa);
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

CaixaNoABB *criar_no_caixa(int caixa, int tempo_saida,int tempo_entrada, int tipo, int conta, int oper)
{
	CaixaNoABB *novo = malloc(sizeof(CaixaNoABB));
	if(novo == NULL) return NULL;

	novo->caixa = caixa;
	novo->tempo_entrada = tempo_entrada;
	novo->tempo_saida = tempo_saida;
	novo->tipo = tipo;
	novo->conta = conta;
	novo->oper = oper;
	novo->dir = NULL;
	novo->esq = NULL;

	return novo;
}
int c_adicionar_caixa_abb(CaixaNoABB **C, int caixa, int tempo_saida, int tempo_entrada, int tipo, int conta, int oper)
{
	CaixaNoABB *novo = criar_no_caixa(caixa,tempo_saida,tempo_entrada, tipo,conta,oper);
	if(novo == NULL) return 0;

	if(*C == NULL)
	{
		(*C) = novo;
		return 1;
	}
	CaixaNoABB *p = *C, *p_pai = NULL;

	while(p != NULL)
	{
		p_pai = p;
		if(p->tempo_saida > tempo_saida)
		{
			p = p->esq;

		}else if(p->tempo_saida < tempo_saida)
		{
			p = p->dir;
		}else
		{
			if(p->caixa > caixa) p = p->esq;
			else p = p->dir;
		}
	}
	
	if(p_pai->tempo_saida > tempo_saida)
	{
		p_pai->esq = novo;
	}else if(p_pai->tempo_saida < tempo_saida)
	{
		p_pai->dir = novo;
	}else
	{
		if(p_pai->caixa > caixa) p_pai->esq = novo;
		else p_pai->dir = novo;
	}

	return 1;
} 

CaixaNoABB *c_consultar_prox_caixa(CaixaNoABB* C)
{	
	CaixaNoABB *C_pai = NULL;

	while(C != NULL)
	{
		C_pai = C;
		C = C->esq;
	}
	return C_pai;
}

int c_retirar_prox_no(CaixaNoABB **C)
{
	if(*C == NULL) return 0;
	CaixaNoABB  *p = *C,*remov = c_consultar_prox_caixa(*C), *remov_pai = NULL;

	while(p != remov)
	{
		remov_pai = p;
		p = p->esq;
	}
	if(remov_pai == NULL)
	{
		(*C) = remov->dir;
		free(remov);
		return 1;
	}
	remov_pai->esq = remov->dir;
	free(remov);
	return 1;
}