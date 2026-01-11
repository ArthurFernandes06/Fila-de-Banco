#ifndef LOGTREE_H
#define LOGTREE_H
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	typedef struct Log
	{
		//Estrutura Arvore
		struct Log *dir;
		struct Log *esq;
		
		//Info
		int tempo;
		int conta;
		int classe;
		int caixa;
		int oper;
		
	}Log;

	typedef struct CaixaNoABB
	{
		int tempo_saida;
		int tempo_entrada;
		int caixa;
		int tipo;
		int conta;
		int oper;
		struct CaixaNoABB *dir;
		struct CaixaNoABB *esq;
	}CaixaNoABB;
	
	void inicializar(Log **l);
	Log *criar_no_log(int conta, int classe, int timer, int caixa, int oper);
	int log_registrar(Log **l, int conta, int classe, int timer, int caixa,int oper);
	float log_media_por_classe(Log **l, int classe);
	int log_obter_soma_por_classe(Log **l, int classe);
	int log_obter_contagem_por_classe(Log **l, int classe);
	int log_obter_contagem_oper_por_classe(Log **l, int classe);
	int log_obter_contagem_por_caixa(Log **l, int caixa);
	CaixaNoABB *criar_no_caixa(int caixa, int tempo_saida,int tempo_entrada, int tipo, int conta, int oper);
	int c_adicionar_caixa_abb(CaixaNoABB **C, int caixa, int tempo_saida,int tempo_entrada, int tipo, int conta, int oper);
	CaixaNoABB *c_consultar_prox_caixa(CaixaNoABB* C);
	int c_retirar_prox_no(CaixaNoABB **C);

#endif