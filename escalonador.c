#include "escalonador.h"

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
    //Na inserção na fila, num_conta é a chave e qtde_operacoes é valor.
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
    int tam_f1,tam_f2,tam_f3,tam_f4,tam_f5, total;
    tam_f1 = f_num_elementos(&e->fila_1);
    tam_f2 = f_num_elementos(&e->fila_2);
    tam_f3 = f_num_elementos(&e->fila_3);
    tam_f4 = f_num_elementos(&e->fila_4);
    tam_f5 = f_num_elementos(&e->fila_5);

    total = tam_f1 + tam_f2 + tam_f3 + tam_f4 + tam_f5;
    return total;
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


    if(conta_prox == conta_1) return f_consultar_proximo_valor(&e->fila_1);
    else if(conta_prox == conta_2) return f_consultar_proximo_valor(&e->fila_2);
    else if(conta_prox == conta_3) return f_consultar_proximo_valor(&e->fila_3);
    else if(conta_prox == conta_4) return f_consultar_proximo_valor(&e->fila_4);
    else if(conta_prox == conta_5) return f_consultar_proximo_valor(&e->fila_5);
    else return -1;
}

int e_consultar_prox_fila (Escalonador *e)
{
    /*
        Usando a lógica da disciplina do escalonador para consultar a próxima conta,
        aqui a gente só compara de qual fila é essa próxima conta e retorna o número da fila.
    */
    int conta_prox = e_consultar_prox_num_conta(e);
    int conta_1 = f_consultar_proxima_chave(&e->fila_1);
    int conta_2 = f_consultar_proxima_chave(&e->fila_2);
    int conta_3 = f_consultar_proxima_chave(&e->fila_3);
    int conta_4 = f_consultar_proxima_chave(&e->fila_4);
    int conta_5 = f_consultar_proxima_chave(&e->fila_5);


    if(conta_prox == conta_1) return 1;
    else if(conta_prox == conta_2) return 2;
    else if(conta_prox == conta_3) return 3;
    else if(conta_prox == conta_4) return 4;
    else if(conta_prox == conta_5) return 5;
    else return -1;
}

int e_consultar_tempo_prox_cliente (Escalonador *e)
{
    /*
        Usando a mesma lógica do e_consultar_prox_fila, a gente vai checar a próxima conta,
        vamos checar de qual fila essa conta é, consultar a quantidade de operações usando a 
        função e_consultar_prox_qtde_oper() e retornar as operações vezes o delta_t.
    */
    int conta_prox = e_consultar_prox_num_conta(e);
    int conta_1 = f_consultar_proxima_chave(&e->fila_1);
    int conta_2 = f_consultar_proxima_chave(&e->fila_2);
    int conta_3 = f_consultar_proxima_chave(&e->fila_3);
    int conta_4 = f_consultar_proxima_chave(&e->fila_4);
    int conta_5 = f_consultar_proxima_chave(&e->fila_5);


    if(conta_prox == conta_1) return f_consultar_proximo_valor(&e->fila_1) * e->delta_t;
    else if(conta_prox == conta_2) return f_consultar_proximo_valor(&e->fila_2) * e->delta_t;
    else if(conta_prox == conta_3) return f_consultar_proximo_valor(&e->fila_3) * e->delta_t;
    else if(conta_prox == conta_4) return f_consultar_proximo_valor(&e->fila_4) * e->delta_t;
    else if(conta_prox == conta_5) return f_consultar_proximo_valor(&e->fila_5) * e->delta_t;
    else return -1;

}
int e_conf_por_arquivo (Escalonador **e, char *nome_arq_conf)
{
    /*
    Realiza a configuração de inicialização do escalonador através da leitura do arquivo de configuração de nome
    “nome_arq_conf”, retornando 1 em caso de sucesso e 0 caso contrário.
    */

    FILE *arq = fopen(nome_arq_conf, "r");
    if(arq == NULL) return 0;

    //Dados escalonador
    char linha[256];
    int delta_t, caixas;
    int d1,d2,d3,d4,d5;

    //Dados Clientes
    char tipo[20];
    int conta, operacoes;
    int fila = -1;

    //Aqui é feita a validação e leitura dos caixas
    if(!fgets(linha, sizeof(linha), arq))
    {
        fclose(arq);
        return 0;
    }
    if(sscanf(linha, "qtde de caixas = %d", &caixas) != 1)
    {
        fclose(arq);
        return 0;
    }

    //Validação e leitura do delta_t
    if(!fgets(linha, sizeof(linha), arq))
    {
        fclose(arq);
        return 0;
    }
    if(sscanf(linha, "delta t = %d", &delta_t) != 1)
    {
        fclose(arq);
        return 0;
    }

    //Validação e leitura das disciplinas de escalonamento
    if(!fgets(linha, sizeof(linha), arq))
    {
        fclose(arq);
        return 0;
    }
    if(sscanf(linha,"disciplina de escalonamento = {%d,%d,%d,%d,%d}", &d1, &d2, &d3, &d4, &d5) != 5)
    {
        fclose(arq);
        return 0;
    }


    if(!e_inicializar(e,caixas,delta_t,d1,d2,d3,d4,d5))
    {
        fclose(arq);
        return 0;
    }


    while(fgets(linha, sizeof(linha), arq))
    {
        fila = -1;
        //Se tiver uma linha com dados inválidos o programa pula a leitura
        if(sscanf(linha, "%19s - conta %d - %d operacao", tipo, &conta, &operacoes) == 3)
        {
            if(strcmp(tipo, "Premium") == 0) fila = 1;
            else if(strcmp(tipo, "Ouro") == 0) fila = 2;
            else if(strcmp(tipo, "Prata") == 0) fila = 3;
            else if(strcmp(tipo, "Bronze") == 0) fila = 4;
            else if(strcmp(tipo, "Leezu") == 0) fila = 5;

            if(fila != -1) e_inserir_por_fila(*e, fila, conta, operacoes);
        }

    }
    fclose(arq);
    return 1;
}
void e_rodar(Escalonador **e, char *nome_arq_in, char *nome_arq_out)
{
    e_conf_por_arquivo(e,nome_arq_in);
    FILE *arq = fopen(nome_arq_out, "w");
    int t_lista_caixa = 0;
    int caixa = 1;
    int oper, tipo,conta;
    int tempo_saida,tempo_entrada;
    char categoria[32];

    CaixaNoABB *C = NULL;
    CaixaNoABB *C_atual = NULL;

    while(t_lista_caixa < (*e)->caixas && e_consultar_qtde_clientes(*e) > 0)
    {
        oper = e_consultar_prox_qtde_oper(*e);
        tipo = e_consultar_prox_fila(*e);
        conta = e_obter_prox_num_conta(*e);

        c_adicionar_caixa_abb(&C, caixa, (*e)->delta_t * oper,0, tipo, conta, oper);
        
        if(tipo == 1) strcpy(categoria, "Premium");
        else if(tipo == 2) strcpy(categoria,"Ouro");
        else if(tipo == 3) strcpy(categoria,"Prata");
        else if(tipo == 4) strcpy(categoria,"Bronze");
        else strcpy(categoria, "Leezu");

        
        fprintf(arq,"T = %d min: Caixa %d chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n",
            0,caixa,categoria,conta,oper);

        caixa++;
        t_lista_caixa++;
    }


    while(t_lista_caixa > 0)
    {  
        
        if(e_consultar_qtde_clientes(*e) > 0)
        {
            C_atual = c_consultar_prox_caixa(C);
            oper = e_consultar_prox_qtde_oper(*e);
            tipo = e_consultar_prox_fila(*e);
            if(tipo == 1) strcpy(categoria, "Premium");
            else if(tipo == 2) strcpy(categoria,"Ouro");
            else if(tipo == 3) strcpy(categoria,"Prata");
            else if(tipo == 4) strcpy(categoria,"Bronze");
            else strcpy(categoria, "Leezu");

            conta = e_obter_prox_num_conta(*e);
            caixa = C_atual->caixa;
            tempo_entrada = C_atual->tempo_saida;
            tempo_saida = tempo_entrada + oper*(*e)->delta_t;
            c_adicionar_caixa_abb(&C,C_atual->caixa,tempo_saida,tempo_entrada,tipo,conta,oper);

            fprintf(arq,"T = %d min: Caixa %d chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n",
            tempo_entrada,caixa,categoria,conta,oper);

            t_lista_caixa++;

        }
        c_retirar_prox_no(&C);
        t_lista_caixa--;
    }


    

    fclose(arq);
}
