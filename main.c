#include"escalonador.h"

int main()
{
    Escalonador *e;
    e_conf_por_arquivo(&e,"entrada-0001.txt");
    e_rodar(&e,"entrada-0001.txt","saida-teste.txt");    
   return 0;
}