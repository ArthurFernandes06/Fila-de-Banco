#include <stdio.h>
#include <stdlib.h>
#include "escalonador.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <X>\n", argv[0]);
        return 1;
    }

    int X = atoi(argv[1]);

    //Faz a validação do intervalo
    if (X < 1 || X > 9999)
    {
        printf("Erro: X deve estar no intervalo [1, 9999]\n");
        return 1;
    }

    char nome_entrada[32];
    char nome_saida[32];

    // monta os nomes com zeros na esquerda
    sprintf(nome_entrada, "entrada-%04d.txt", X);
    sprintf(nome_saida,   "saida-%04d.txt",   X);

    Escalonador *e = NULL;
    e_conf_por_arquivo(&e,nome_entrada);
    e_rodar(&e, nome_entrada, nome_saida);

    return 0;
}
