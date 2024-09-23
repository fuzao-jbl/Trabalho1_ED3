#include "registro.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// PRIVADO ///////////////////////////////////////////////////////////////////////

// A funcao removido recebe um registro e retorna true (1) se ele tiver sido logicamente
// removido ou false (0) caso contrario
int removido(Registro *registro)
{
    if (registro->removido == '1')
        return 1;
    else
        return 0;
}

// A funcao nao_nulo retorna true (1) se campo estiver nulo e false caso contrario
// cada campo sera refenciado pelo seu numero, como se fosse uma lista. Entao o campo 0
// eh a populacao, 1 o tamanho etc. Um resumo dos numeros de cada campo esta na propria struct
// acima
int nao_nulo(Registro *registro, int campo)
{
    switch (campo)
    {
        case 0:
            if (registro->populacao == -1 || registro->populacao == 0)
                return 0;
            else
                break;
        case 1:
            if (registro->tamanho == -1)
                return 0;
            else
                break;
        case 2:
            if (registro->unidadeMedida == '$')
                return 0;
            else
                break;
        case 3:
            if (registro->velocidade == -1)
                return 0;
            else
                break;
        case 4:
            if (registro->nome.tamanho == 0)
                return 0;
            else
                break;
        case 5:
            if (registro->especie.tamanho == 0)
                return 0;
            else
                break;
        case 6:
            if (registro->habitat.tamanho == 0)
                return 0;
            else
                break;
        case 7:
            if (registro->tipo.tamanho == 0)
                return 0;
            else
                break;
        case 8:
            if (registro->dieta.tamanho == 0)
                return 0;
            else
                break;
        case 9:
            if (registro->alimento.tamanho == 0)
                return 0;
            else
                break;
    }

    return 1;
}


// a funcao busca_int_printa vai buscar o int valor do respectivo int campo no FILE *arquivo
// printar os registros encontrados
// Se encontrar algum registro retorna 1, senao retorna 0
int busca_int_printa(FILE *arquivo, int campo, int valor)
{
    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    // pegamos tamanho para saber quando terminar a leitura
    int tamanho = tamanho_bytes(arquivo);
    // declaramos a variavel achou_algo inicializada em 0 (false), 
    // ja que no comeco da busca nao achamos nada
    int achou_algo = 0;
    // nao podemos pular linha no primeiro registro buscado
    int primeiro = 1;
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro))
            switch (campo)
            {
                case 0:
                    if (registro->populacao == valor)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        achou_algo = 1;
                        primeiro = 0;
                        printa_formatado(registro);
                    }
                    break;
                case 3:
                    if (registro->velocidade == valor)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        achou_algo = 1;
                        primeiro = 0;
                        printa_formatado(registro);
                    }
                    break;
            }
    }
    // por fim, liberamos o registro temporario
    libera_registro(registro);

    return achou_algo;
}

// a funcao busca_float_printa vai buscar o float valor do cmpo tamanho (unico que tem float)
// int campo no FILE *arquivo e printar os registros encontrados
// Retorna 1 se encontrou algum arquivo, senao retorna 0
int busca_float_printa(FILE *arquivo, float valor)
{
    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    int tamanho = tamanho_bytes(arquivo);
    int achou_algo = 0;
    int primeiro = 1;
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro) && registro->tamanho == valor)
        {
            if (!primeiro)
                printf("\n");
            primeiro = 0;
            achou_algo = 1;
            printa_formatado(registro);
        }
    }
    // por fim, liberamos o registro temporario
    libera_registro(registro);

    return achou_algo;
}

// a funcao busca_str_printa vai buscar o string valor do respectivo int campo no FILE *arquivo
// printar os registros encontrados
// retorna 1 se encontrou algum registro e 0 caso contrario
int busca_str_printa(FILE *arquivo, int campo, char *valor)
{
    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    int tamanho = tamanho_bytes(arquivo);
    int achou_algo = 0;
    int primeiro = 1;
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro))
            switch (campo)
            {
                case 4:
                    if (strcmp(registro->nome.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 5:
                    if (strcmp(registro->especie.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 6:
                    if (strcmp(registro->habitat.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 7:
                    if (strcmp(registro->tipo.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 8:
                    if (strcmp(registro->dieta.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 9:
                    if (strcmp(registro->alimento.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
            }
    }

    free(registro);
    return achou_algo;
}

/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// PUBLICO ///////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////

// essa funcao recebe o ponteiro de um arquivo, o byte offset do registro,
// e o ponteiro do registro que salvara os dados
// a seguinte funcao le o registro com byteoffset do arquivo
void le_registro(Registro *registro, FILE *arquivo, int offset)
{
    // arruma o ponteiro para o inicio do registro e le os valores
    fseek(arquivo, offset, SEEK_SET);
    fread(&registro->removido, 1, 1, arquivo);
    fread(&registro->encadenamento, 4, 1, arquivo);
    // toda especie precisa ter um nome valido, salvamos posicao e vemos se especie comeca com $
    offset = ftell(arquivo);
    if (fgetc(arquivo) == '$')
        return;
    fseek(arquivo, offset, SEEK_SET); 
    fread(&registro->populacao, 4, 1, arquivo);
    fread(&registro->tamanho, 4, 1, arquivo);
    fread(&registro->unidadeMedida, 1, 1, arquivo);
    fread(&registro->velocidade, 4, 1, arquivo);
    freadvar(&registro->nome, arquivo);
    freadvar(&registro->especie, arquivo);
    freadvar(&registro->habitat, arquivo);        
    freadvar(&registro->tipo, arquivo);
    freadvar(&registro->dieta, arquivo);
    freadvar(&registro->alimento, arquivo);
}

// a seguinte funcao recebe um registro e printa suas informacoes de forma formatada
void printa_formatado(Registro *registro)
{
    if (nao_nulo(registro, 4))
        printf("Nome: %s\n", registro->nome.valor);
    if (nao_nulo(registro, 5))
        printf("Especie: %s\n", registro->especie.valor);
    if (nao_nulo(registro, 7))
        printf("Tipo: %s\n", registro->tipo.valor);
    if (nao_nulo(registro, 8))
        printf("Dieta: %s\n", registro->dieta.valor);
    if (nao_nulo(registro, 6))
        printf("Lugar que habitava: %s\n", registro->habitat.valor);
    if (nao_nulo(registro, 1))
        printf("Tamanho: %.1f m\n", registro->tamanho);
    if (nao_nulo(registro, 2) && nao_nulo(registro, 3))
        printf("Velocidade: %d %cm/h\n", registro->velocidade, registro->unidadeMedida);
}

// essa funcao recebe o ponteiro desse registro e libera ele
void libera_registro(Registro *registro)
{
    free(registro->nome.valor);
    free(registro->especie.valor);
    free(registro->habitat.valor);
    free(registro->tipo.valor);
    free(registro->dieta.valor);
    free(registro->alimento.valor);
    free(registro);
}

// a seguinte funcao vai buscar no arquivo o registro que possui o campo com o valor
// especificado e vai printar todos os registros cujos valores baterem
void busca_e_printa(FILE *arquivo, int campo, char *valor)
{
    int achou_algo;
    // dependendo do tipo de valor que queremos buscar, chamamos uma funcao que realiza
    // essa busca especificamente para esse tipo 
    if (campo == 0 || campo == 3)
        achou_algo = busca_int_printa(arquivo, campo, atoi(valor));   // atoi(char *) transforma string em int
    else if (campo == 1)
        achou_algo = busca_float_printa(arquivo, atof(valor));        // afor(char *) transform string em float
    else
        achou_algo = busca_str_printa(arquivo, campo, sem_aspas(valor));

    // avisa caso nao tenha encontrado registro
    if (!achou_algo)
        printf("Registro inexistente.\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////
