#ifndef LOGTREE_H
#define LOGTREE_H
	#include <stdlib.h>
	#include <stdio.h>
	
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
		
	}Log;
	
	void inicializar(Log **l);
	Log *criar_no(int conta, int classe, int timer, int caixa);
	int log_registrar(Log **l, int conta, int classe, int timer, int caixa);
	float log_media_por_classe(Log **l, int classe);
	int log_obter_soma_por_classe(Log **l, int classe);
	int log_obter_contagem_por_classe(Log **l, int classe);
#endif