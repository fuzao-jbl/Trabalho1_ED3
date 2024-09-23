#include "funcionalidades.h"

// a funcao recebe ponteiro de arquivo e printa suas informacoes da forma formatada
// representa a funcionalidade (2) do trabalho
void select_from(FILE *arquivo)
{
    // alocamos a memoria do registro temporario e do cabecalho
    Registro *registro_temporario = (Registro *)malloc(sizeof(Registro));
    Cabecalho *cabecalho = (Cabecalho *)malloc(sizeof(Cabecalho));

    // primeiro abrimos o arquivo e contamos o numero de registros
    int tamanho = tamanho_bytes(arquivo);

    // lemos o cabecalho do arquivo
    le_cabecalho(cabecalho, arquivo);

    // pegamos as informacoes e printamos
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro_temporario, arquivo, offset);
        if (!removido(registro_temporario))
            printa_formatado(registro_temporario);
        printf("\n");
    }

    // printamos numero de paginas
    printf("Numero de paginas de disco: %d\n", cabecalho->nroPagDisco);

    // por fim libera o registro temporario
    libera_registro(registro_temporario);
    free(cabecalho);
}

// a funcao recebe um arquivo e pede o comando "where" do SQL com o numero n de
// criterios e depois o nome do campo e seu valor, que devem vir do usuario.
// A funcao printa na tela os registros que conterem os campos com os valores
// pedidos.
// select_where representa a funcionalidade (3) do trabalho
void select_where(FILE* arquivo)
{
    // vamos primeiro receber a fila
    // precisamos receber o n para saber quantos criterios de selecao vao ter
    int n;
    scanf(" %d", &n);
    // depois precisamos receber a entrada e separar a string nos espacos
    char entrada[25*n];
    fgets(entrada, sizeof(entrada), stdin);
    // vamos criar uma fila
    Fila *fila = cria_fila();
    // vamos tokenizar separando pelos espacos " "
    No *no = (No *)malloc(sizeof(No));
    no->campo = strtok(entrada, " ");
    no->valor = strtok(NULL, " ");
    poe_na_fila(fila, no);
    for (int i = 1; i < n; i++)
    {
        No *no = (No *)malloc(sizeof(No));
        no->campo = strtok(NULL, " ");
        no->valor = strtok(NULL, " ");
        poe_na_fila(fila, no);
    }

    // agora vamos nos preparar para ler os dados do arquivo
    // alocamos a memoria do cabecalho
    Cabecalho *cabecalho = (Cabecalho *)malloc(sizeof(Cabecalho));
    // lemos o cabecalho do arquivo
    le_cabecalho(cabecalho, arquivo);
  
    // iteramos sobre cada busca 
    int campo;
    for (int i = 0; i < n; i++)
    {
        printf("Busca %d\n", i+1);
        // vamos receber o numero do campo para conseguir fazer a busca
        campo = int_campo(fila->cabeca->campo);
        // se encontramos algo printamos
        busca_e_printa(arquivo, campo, fila->cabeca->valor);
        // a cabeca da fila se torna o proximo da antiga cabeca e liberamos aquele
        // no
        proximo_na_fila(fila);
        // printamos numero de paginas
        if (i == n-1)
            printf("\nNumero de paginas de disco: %d\n", cabecalho->nroPagDisco);
        else
            printf("\nNumero de paginas de disco: %d\n\n", cabecalho->nroPagDisco);
    }
}

// a funcao recebe um arquivo e executa a funcionalidade (4) do trabalho, que eh
// a remocao logica de registros
// Para isso, a funcao vai perguntar quantas buscas e remocoes serao feitas e
// depois os campos e valores como especificado pelo trabalho
void remocao_logica(FILE *arquivo)
{
    // recebe o numero de buscas que realizara
    int n;
    scanf("%d", &n);
}
