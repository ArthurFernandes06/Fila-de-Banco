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
    /*
    essa função funciona por meio de uma lista de prioridade implementada com uma Árvore binária de busca,
    na qual a prioridade é o tempo de saida, primeiro preenche ela escrevendo 0 para chamada ao caixa,
    depois ela remove o cliente que sai mais cedo do menor caixa, e esse tempo de saida é o tempo de entrada
    de outro cliente então já é escrito no arquivo de saida esse tempo, e enquanto tiver gente para tirar
    dessa Lista de prioridade, em paralelo enquanto tiver clientes no escalonador é adicionado a ela.
    */

    //Preenchendo o escalonador com os dados do arquivo de entrada.
    e_conf_por_arquivo(e,nome_arq_in);
    FILE *arq = fopen(nome_arq_out, "w");
    int t_lista_caixa = 0;//Váriavel para guardar o tamanho da Lista de prioridade
    int caixa = 1;
    int oper, tipo,conta;
    int tempo_saida,tempo_entrada,tempo_total = 0;
    char categoria[32];

    /*
    Aqui eu estou declarando dois ponteiros, O 'C' que é a lista de prioridade,
    e o C_atual que será o ponteiro que recebe o próximo cliente que vai entrar no caixa.
    */
    CaixaNoABB *C = NULL;
    CaixaNoABB *C_atual = NULL;

    //Registros
    Log *l = NULL;

    while(t_lista_caixa < (*e)->caixas && e_consultar_qtde_clientes(*e) > 0)
    {
        /*
        Aqui é onde começa a preencher os caixas e preencher o arquivo para T = 0.
        */
        oper = e_consultar_prox_qtde_oper(*e);
        tipo = e_consultar_prox_fila(*e);
        conta = e_obter_prox_num_conta(*e);

        c_adicionar_caixa_abb(&C, caixa, (*e)->delta_t * oper,0, tipo, conta, oper);
        log_registrar(&l,conta,tipo, 0 ,caixa,oper);

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
        /*
        Como os caixas já estão preenchidos, aqui ele vai ser esvaziado,
        a medida que esvazia entra um novo cliente de acordo com a disciplina de atendimento,
        que tera tempo_entrada = tempo_saida(do cliente que saiu).
        */
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
            log_registrar(&l,conta,tipo,tempo_entrada,caixa,oper);

            fprintf(arq,"T = %d min: Caixa %d chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n",
            tempo_entrada,caixa,categoria,conta,oper);

            t_lista_caixa++;

        }
        if(tempo_total < tempo_saida) tempo_total = tempo_saida;
        c_retirar_prox_no(&C);
        t_lista_caixa--;
    }
    int clientes_premium = log_obter_contagem_por_classe(&l,1);
    int clientes_ouro = log_obter_contagem_por_classe(&l,2);
    int clientes_prata = log_obter_contagem_por_classe(&l,3);
    int clientes_bronze = log_obter_contagem_por_classe(&l,4);
    int clientes_comum = log_obter_contagem_por_classe(&l,5);

    float tempo_premium = log_media_por_classe(&l,1);
    float tempo_ouro = log_media_por_classe(&l,2);
    float tempo_prata = log_media_por_classe(&l,3);
    float tempo_bronze = log_media_por_classe(&l,4);
    float tempo_comum = log_media_por_classe(&l,5);



    fprintf(arq,"Tempo total de atendimento: %d minutos.\n",tempo_total);
    fprintf(arq,"Tempo medio de espera dos %d clientes Premium: %.2f\n", clientes_premium,tempo_premium);
    fprintf(arq,"Tempo medio de espera dos %d clientes Ouro: %.2f\n", clientes_ouro, tempo_ouro);
    fprintf(arq,"Tempo medio de espera dos %d clientes Prata: %.2f\n", clientes_prata, tempo_prata);
    fprintf(arq,"Tempo medio de espera dos %d clientes Bronze: %.2f\n",clientes_bronze, tempo_bronze);
    fprintf(arq,"Tempo medio de espera dos %d clientes Comuns: %.2f\n",clientes_comum, tempo_comum);

    float m_oper_premium = (float)log_obter_contagem_oper_por_classe(&l,1)/clientes_premium;
    float m_oper_ouro = (float)log_obter_contagem_oper_por_classe(&l,2)/clientes_ouro;
    float m_oper_prata = (float)log_obter_contagem_oper_por_classe(&l,3)/clientes_prata;
    float m_oper_bronze = (float)log_obter_contagem_oper_por_classe(&l,4)/clientes_bronze;
    float m_oper_leezu = (float)log_obter_contagem_oper_por_classe(&l,5)/clientes_comum;

    fprintf(arq,"Quantidade media de operacoes por cliente Premium = %.2f\n",m_oper_premium);
    fprintf(arq,"Quantidade media de operacoes por cliente Ouro = %.2f\n", m_oper_ouro);
    fprintf(arq,"Quantidade media de operacoes por cliente Prata = %.2f\n", m_oper_prata);
    fprintf(arq,"Quantidade media de operacoes por cliente Bronze = %.2f\n", m_oper_bronze);
    fprintf(arq,"Quantidade media de operacoes por cliente Leezu = %.2f\n",m_oper_leezu);

    for(int i = 1; i<= (*e)->caixas; ++i)
    {
        fprintf(arq,"O caixa de número %d atendeu %d clientes.\n",i, log_obter_contagem_por_caixa(&l,i));
    }
    fclose(arq);
}
