#include "escalonador.h"
#include <stdio.h>

int e_inicializar(Escalonador **e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5)
{
    (*e) = malloc(sizeof(Escalonador));
    if(*e == NULL) return 0;

    f_inicializar(&(*e)->fila_1);
    f_inicializar(&(*e)->fila_2);
    f_inicializar(&(*e)->fila_3);
    f_inicializar(&(*e)->fila_4);
    f_inicializar(&(*e)->fila_5);

    (*e)->disciplina_at[0] = n_1;
    (*e)->disciplina_at[1] = n_2;
    (*e)->disciplina_at[2] = n_3;
    (*e)->disciplina_at[3] = n_4;
    (*e)->disciplina_at[4] = n_5;


    for(int i = 0; i < 5; ++i) (*e)->atendidos[i] = 0;

    (*e)->caixas = caixas;
    (*e)->delta_t = delta_t;
    
    return 1;
}

int e_inserir_por_fila (Escalonador *e, int classe, int num_conta, int qtde_operacoes)
{
    int ins_sucess;
    switch(classe)
    {
        case 1:
            ins_sucess = f_inserir(&e->fila_1,num_conta,qtde_operacoes);
            break;
        case 2:
            ins_sucess = f_inserir(&e->fila_2,num_conta,qtde_operacoes);
            break;
        case 3:
            ins_sucess = f_inserir(&e->fila_3,num_conta,qtde_operacoes);
            break;
        case 4:
            ins_sucess = f_inserir(&e->fila_4,num_conta,qtde_operacoes);
            break;
        case 5:
            ins_sucess = f_inserir(&e->fila_5,num_conta,qtde_operacoes);
            break;
        default:
            ins_sucess = 0;
    }
    return ins_sucess;
}
int e_consultar_qtde_clientes (Escalonador *e)
{
    int tam_f1,tam_f2,tam_f3,tam_f4,tam_f5;
    tam_f1 = f_num_elementos(&e->fila_1);
    tam_f2 = f_num_elementos(&e->fila_2);
    tam_f3 = f_num_elementos(&e->fila_3);
    tam_f4 = f_num_elementos(&e->fila_4);
    tam_f5 = f_num_elementos(&e->fila_5);

    return tam_f1 + tam_f2 + tam_f3 + tam_f4 + tam_f5;
}

int e_consultar_prox_num_conta(Escalonador *e)
{
    int conta;
    if(e->atendidos[0] < e->disciplina_at[0] && f_num_elementos(&e->fila_1) > 0)
    {
        conta = f_consultar_proxima_chave(&e->fila_1);

    }else if(e->atendidos[1] < e->disciplina_at[1] && f_num_elementos(&e->fila_2) > 0)
    {
        conta = f_consultar_proxima_chave(&e->fila_2);

    }else if(e->atendidos[2] < e->disciplina_at[2] && f_num_elementos(&e->fila_3) > 0)
    {
        conta = f_consultar_proxima_chave(&e->fila_3);

    }else if(e->atendidos[3] < e->disciplina_at[3] && f_num_elementos(&e->fila_4) > 0)
    {
        conta = f_consultar_proxima_chave(&e->fila_4);

    }else if(e->atendidos[4] < e->disciplina_at[4] && f_num_elementos(&e->fila_5) > 0)
    {
        conta = f_consultar_proxima_chave(&e->fila_5);

    }else if(e_consultar_qtde_clientes(e) == 0)
    {

        conta = -1;
    }else
    {
        for(int i = 0; i < 5; ++i) e->atendidos[i] = 0;
        return e_consultar_prox_num_conta(e);
    }

    return conta;
}

int e_obter_prox_num_conta(Escalonador *e)
{
    int conta;

    if(e->atendidos[0] < e->disciplina_at[0] && f_num_elementos(&e->fila_1) > 0)
    {
        conta = f_obter_proxima_chave(&e->fila_1);
        e->atendidos[0]++;

    }else if(e->atendidos[1] < e->disciplina_at[1] && f_num_elementos(&e->fila_2) > 0)
    {
        conta = f_obter_proxima_chave(&e->fila_2);
        e->atendidos[1]++;

    }else if(e->atendidos[2] < e->disciplina_at[2] && f_num_elementos(&e->fila_3) > 0)
    {
        conta = f_obter_proxima_chave(&e->fila_3);
        e->atendidos[2]++;

    }else if(e->atendidos[3] < e->disciplina_at[3] && f_num_elementos(&e->fila_4) > 0)
    {
        conta = f_obter_proxima_chave(&e->fila_4);
        e->atendidos[3]++;

    }else if(e->atendidos[4] < e->disciplina_at[4] && f_num_elementos(&e->fila_5) > 0)
    {
        conta = f_obter_proxima_chave(&e->fila_5);
        e->atendidos[4]++;

    }else if(e_consultar_qtde_clientes(e) == 0)
    {
        conta = -1;
    }else
    {
        for(int i = 0; i < 5; ++i) e->atendidos[i] = 0;
        return e_obter_prox_num_conta(e);
    }

    return conta;
}

int e_consultar_prox_qtde_oper(Escalonador *e)
{
    int conta_prox = e_consultar_prox_num_conta(e);
    int conta_1 = f_consultar_proxima_chave(&e->fila_1);
    int conta_2 = f_consultar_proxima_chave(&e->fila_2);
    int conta_3 = f_consultar_proxima_chave(&e->fila_3);
    int conta_4 = f_consultar_proxima_chave(&e->fila_4);
    int conta_5 = f_consultar_proxima_chave(&e->fila_5);


    if(conta_prox == conta_1)
    {
        
    }
}
int main()
{
    Escalonador *e;
    e_inicializar(&e,5,1,1,1,1,1,1);
     
    e_inserir_por_fila(e,2,1,10);
    e_inserir_por_fila(e,1,22,3);
    e_inserir_por_fila(e,1,2,3);
    e_inserir_por_fila(e,3,40,1);
    int conta = e_consultar_prox_num_conta(e);
    printf("\nProxima Conta: %d", conta);

    while(e_consultar_prox_num_conta(e) > 0)
    {
        conta = e_obter_prox_num_conta(e);
        printf("\nProxima Conta: %d", conta);
    }
}