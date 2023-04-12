#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
Author: @bennie10colado
*/

struct Musica // musicas
{
    char nome_musica[100];
    int codigo_musica;
    float tempo;
};

struct Album // albuns
{
    struct Musica musicas[100];
    char nome_album[100];
    int codigo_album;
    int quantidade_musicas;
};

struct Banda // bandas
{
    struct Album albuns[100]; // lista de albuns
    char nome_banda[100];
    int codigo_banda;
    int quantidade_albuns;
};

struct Banda spotify[100];
int quantidade_bandas = 0;

//-------------------------------------------------- VOIDS BANDAS --------------------------------------------------------------------

int ExisteBanda(char nome_banda1[], int codigo_banda1)
{
    int i, aux = -1; //-1 é um valor arbitrario
    for (i = 0; i < quantidade_bandas; i++)
    {
        if (strcmp(nome_banda1, spotify[i].nome_banda) == 0 || spotify[i].codigo_banda == codigo_banda1)
        {
            aux = i;
            // printf("Achamos uma banda igual\n");
        }
    }
    if (aux != -1)
    {
        // printf("posicao da banda %d", aux);
        return aux;
    }
    else
        return -1; // se continuar inalterado(-1), é porque a banda nao existe
}

int PosicaoBanda(char nome_banda1[], int codigo_banda1)
{
    int i, aux1 = -1, aux = ExisteBanda(nome_banda1, codigo_banda1);

    // =! -1, entao a banda existe, entao será percorrida
    if (aux != -1)
    {
        for (i = 0; i < quantidade_bandas; i++)
        {
            if (strcmp(nome_banda1, spotify[i].nome_banda) == 0 && spotify[i].codigo_banda == codigo_banda1)
                aux1 = i; // pega o valor i onde a específica banda se encontra
        }
    }

    return aux1; // retorna posicao em que a banda se encontra no repositorio, e se o aux1 retornar -1 a banda nao existe
}

void CadastrarBanda(char nome_banda1[], int codigo_banda1)
{
    int aux;
    aux = ExisteBanda(nome_banda1, codigo_banda1);
    if (aux == -1) // se a banda nao existe
    {
        strcpy(spotify[quantidade_bandas].nome_banda, nome_banda1);
        spotify[quantidade_bandas].codigo_banda = codigo_banda1;
        spotify[quantidade_bandas].quantidade_albuns = 0;

        // printf("\n%s #%d# \n", spotify[quantidade_bandas].nome_banda, spotify[quantidade_bandas].codigo_banda);
        // printf("%d\n", quantidade_bandas);

        quantidade_bandas++;
    }
    else
    {
        printf("\nEsta banda ja esta cadastrada.\n");
    }

    // printf("\n %s #%d# \n", spotify[quantidade_bandas].nome_banda, spotify[quantidade_bandas].codigo_banda);
    // printf("%d\n", quantidade_bandas);
}

void VisualizarBanda(char nome_banda1[], int codigo_banda1)
{
    int aux;
    aux = PosicaoBanda(nome_banda1, codigo_banda1);

    if (aux == -1)
        printf("A banda nao esta cadastrada.\n");

    else
        printf("Nome: %s || Codigo: %d\n", spotify[aux].nome_banda, spotify[aux].codigo_banda);
}

void AtualizarBanda(char nome_banda1[], int codigo_banda1, char novo_nome[], int novo_codigo)
{
    int aux;
    aux = PosicaoBanda(nome_banda1, codigo_banda1);

    if (strcmp(novo_nome, nome_banda1) == 0 || codigo_banda1 == novo_codigo)
    {
        printf("Voce esta tentando atualizar uma banda anterior\n");

        if (aux != -1)
        {
            strcpy(spotify[aux].nome_banda, novo_nome);
            spotify[aux].codigo_banda = novo_codigo;
            printf("Banda atualizada!!\n");
        }

        else
            printf("A banda nao esta cadastrada.\n"); // se a banda nao existe: aux == 1
    }

    else
    {
        strcpy(spotify[aux].nome_banda, novo_nome);
        spotify[aux].codigo_banda = novo_codigo;
        printf("Banda atualizada!!\n");
    }
}

void RemoverBanda(char nome_banda1[], int codigo_banda1)
{

    int i, j, aux = 0;

    for (i = 0; i < quantidade_bandas; i++)
    {
        if (strcmp(nome_banda1, spotify[i].nome_banda) == 0 && spotify[i].codigo_banda == codigo_banda1)
        {
            for (j = i; j < quantidade_bandas - 1; j++)
            {
                spotify[j] = spotify[j + 1];
            }

            quantidade_bandas--;
            aux++;
        }
    }

    if (aux == 1)
        printf("Elemento removido!!\n");
    else
        printf("Elemento não existe\n");
}

//-------------------------------------------------- VOIDS ALBUNS --------------------------------------------------------------------

int ExisteAlbum(char nome_banda1[], int codigo_banda1, char nome_album[], int codigo_album)
{
    int i, aux, aux1 = -1;
    aux = PosicaoBanda(nome_banda1, codigo_banda1);

    if (aux != -1)
    {
        for (i = 0; i < spotify[aux].quantidade_albuns; i++)
        {
            if (codigo_album == spotify[aux].albuns[i].codigo_album || strcmp(spotify[aux].albuns[i].nome_album, nome_album) == 0)
                aux1 = i;
        }
    }

    else
        printf("A banda que voce deseja cadastrar algo nao existe\n");

    if (aux1 != -1)
    {
        return aux1;
    }
    else
        return -1; // então o album nao existe
}

int PosicaoAlbum(char nome_banda[], int codigo_banda, char nome_album[], int codigo_album)
{
    int i, aux, aux1, aux2 = -1;
    aux = PosicaoBanda(nome_banda, codigo_banda);
    aux1 = ExisteAlbum(nome_banda, codigo_banda, nome_album, codigo_album);

    if (aux != -1 && aux1 != -1)
    {
        for (i = 0; i < spotify[aux].quantidade_albuns; i++)
        {
            if (codigo_album == spotify[aux].albuns[i].codigo_album && strcmp(spotify[aux].albuns[i].nome_album, nome_album) == 0)
                aux2 = i;
        }
    }

    return aux2;
}

void CadastrarAlbum(char nome_banda[], int codigo_banda, char nome_album1[], int codigo_album1)
{

    int aux1 = ExisteAlbum(nome_banda, codigo_banda, nome_album1, codigo_album1);
    int aux = PosicaoBanda(nome_banda, codigo_banda);

    if (aux != -1) // se a banda existe
    {
        if (aux1 == -1) // entao o album nao existe, e pode ser adicionado
        {
            strcpy(spotify[aux].albuns[spotify[aux].quantidade_albuns].nome_album, nome_album1);
            spotify[aux].albuns[spotify[aux].quantidade_albuns].codigo_album = codigo_album1;
            spotify[aux].albuns[spotify[aux].quantidade_albuns].quantidade_musicas = 0;
            spotify[aux].quantidade_albuns++;
            printf("Album cadastrado com sucesso!!\n");
        }
        else
            printf("O album ja foi cadastrado\n");
    }

    else
        printf("A banda que voce deseja adicionar um album nao existe\n"); // aux == 1, e entao nao existiria a banda
}

void VisualizarAlbum(char nome_banda[], int codigo_banda, char nome_album1[], int codigo_album1)
{
    int aux1, aux2;
    aux1 = PosicaoBanda(nome_banda, codigo_banda);
    aux2 = PosicaoAlbum(nome_banda, codigo_banda, nome_album1, codigo_album1);

    if (aux2 == -1)
        printf("O album que voce busca nao existe\n");
    else
        printf("Nome do album: %s || Quantidade de musicas: %d || Codigo do album: %d\n", spotify[aux1].albuns[aux2].nome_album, spotify[aux1].albuns[aux2].quantidade_musicas, spotify[aux1].albuns[aux2].codigo_album);
}

// eh possivel adicionar uma funcao para visualizar todos os albuns de uma banda
void AtualizarAlbum(char nome_banda[], int codigo_banda, char nome_album1[], int codigo_album1, char novo_nome[], int novo_codigo)
{
    int aux1, aux2;
    aux1 = PosicaoBanda(nome_banda, codigo_banda);
    aux2 = PosicaoAlbum(nome_banda, codigo_banda, nome_album1, codigo_album1);

    if (strcmp(novo_nome, nome_album1) == 0 || novo_codigo == codigo_album1) // mudar o nome ou o codigo
    {
        printf("Voce ira atualizar o album inicial\n");

        if (aux2 != -1)
        { // album existe
            spotify[aux1].albuns[aux2].codigo_album = novo_codigo;
            strcpy(spotify[aux1].albuns[aux2].nome_album, novo_nome);
            printf("Album atualizado!!\n");
        }

        else
            printf("O album nao esta cadastrado.\n");
    }

    else
    {
        spotify[aux1].albuns[aux2].codigo_album = novo_codigo;
        strcpy(spotify[aux1].albuns[aux2].nome_album, novo_nome);
        printf("Album atualizado!!\n");
    }
}

void RemoverAlbum(char nome_banda[], int codigo_banda, char nome_album1[], int codigo_album1)
{
    int i, j, aux1, a = 0;
    aux1 = PosicaoBanda(nome_banda, codigo_banda);

    for (i = 0; i < spotify[aux1].quantidade_albuns; i++)
    {
        if (codigo_album1 == spotify[aux1].albuns[i].codigo_album && strcmp(spotify[aux1].albuns[i].nome_album, nome_album1) == 0)
        {
            for (j = i; j < spotify[aux1].quantidade_albuns - 1; j++)
            {
                spotify[aux1].albuns[j] = spotify[aux1].albuns[j + 1];
            }

            spotify[aux1].quantidade_albuns--;
            a++;
        }
    }
    if (a == 1)
        printf("Album removido com sucesso\n");
    else
        printf("Album nao existe\n");
}

//-------------------------------------------------- VOIDS MUSICAS --------------------------------------------------------------------

int ExisteMusica(char nome_banda[], int codigo_banda, char nome_album[], int codigo_album, char nome_musica1[], int codigo_musica1)
{
    int i, aux1, aux2, aux = -1;
    aux1 = PosicaoBanda(nome_banda, codigo_banda);
    aux2 = PosicaoAlbum(nome_banda, codigo_banda, nome_album, codigo_album);

    if (aux1 != -1 && aux2 != -1)
    {
        for (i = 0; i < spotify[aux1].albuns[aux2].quantidade_musicas; i++)
        {
            if (codigo_musica1 == spotify[aux1].albuns[aux2].musicas[i].codigo_musica || strcmp(nome_musica1, spotify[aux1].albuns[aux2].musicas[i].nome_musica) == 0)
            {
                aux = i;
            }
        }
    }

    if (aux != -1)
        return aux;
    else
        return -1;
}

int PosicaoMusica(char nome_banda[], int codigo_banda, char nome_album[], int codigo_album, char nome_musica1[], int codigo_musica1)
{
    int i, aux1, aux2, aux3, aux = -1;
    aux1 = PosicaoBanda(nome_banda, codigo_banda);
    aux2 = PosicaoAlbum(nome_banda, codigo_banda, nome_album, codigo_album);
    aux3 = ExisteMusica(nome_banda, codigo_banda, nome_album, codigo_album, nome_musica1, codigo_musica1);

    if (aux1 != -1 && aux2 != -1 && aux3 != -1)
    {
        for (i = 0; i < spotify[aux1].albuns[aux2].quantidade_musicas; i++)
        {
            if (codigo_musica1 == spotify[aux1].albuns[aux2].musicas[i].codigo_musica && strcmp(nome_musica1, spotify[aux1].albuns[aux2].musicas[i].nome_musica) == 0)
            {
                aux = i;
            }
        }
    }

    return aux;
}

void RemoverMusica(char nome_banda[], int codigo_banda, char nome_album[], int codigo_album, char nome_musica[], int codigo_musica)
{
    int i, j, aux1, aux2, aux = 0;

    aux1 = PosicaoBanda(nome_banda, codigo_banda);
    aux2 = PosicaoAlbum(nome_banda, codigo_banda, nome_album, codigo_album);

    for (i = 0; i < spotify[aux1].albuns[aux2].quantidade_musicas; i++)
    {
        if (codigo_musica == spotify[aux1].albuns[aux2].musicas[i].codigo_musica || strcmp(nome_musica, spotify[aux1].albuns[aux2].musicas[i].nome_musica) == 0)
        {
            for (j = i; j < spotify[aux1].albuns[aux2].quantidade_musicas - 1; j++)
            {
                spotify[aux1].albuns[aux2].musicas[j] = spotify[aux1].albuns[aux2].musicas[j + 1];
            }
            spotify[aux1].albuns[aux2].quantidade_musicas--;
            aux++;
        }
    }

    if (aux == 1)
        printf("Musica removida com sucesso\n");

    else
        printf("A musica nao existe");
}

void VisualizarMusica(char nome_banda[], int codigo_banda, char nome_album[], int codigo_album, char nome_musica[], int codigo_musica)
{
    int aux1, aux2, aux3;
    aux1 = PosicaoBanda(nome_banda, codigo_banda);
    aux2 = PosicaoAlbum(nome_banda, codigo_banda, nome_album, codigo_album);
    aux3 = PosicaoMusica(nome_banda, codigo_banda, nome_album, codigo_album, nome_musica, codigo_musica);

    if (aux3 == -1)
        printf("A musica que voce busca nao existe\n");
    else
        printf("Artista(s): %s || Nome do album: %s || Nome da musica: %s \n|| Codigo da musica: %d || Tempo da musica: %.02lf\n", spotify[aux1].nome_banda, spotify[aux1].albuns[aux2].nome_album, spotify[aux1].albuns[aux2].musicas[aux3].nome_musica, spotify[aux1].albuns[aux2].musicas[aux3].codigo_musica, spotify[aux1].albuns[aux2].musicas[aux3].tempo);
}

void AtualizarMusica(char nome_banda[], int codigo_banda, char nome_album[], int codigo_album, char nome_musica1[], int codigo_musica1, char novo_nome[], int novo_codigo, float novo_tempo)
{
    int aux1, aux2, aux3;
    aux1 = PosicaoBanda(nome_banda, codigo_banda);
    aux2 = PosicaoAlbum(nome_banda, codigo_banda, nome_album, codigo_album);
    aux3 = PosicaoMusica(nome_banda, codigo_banda, nome_album, codigo_album, nome_musica1, codigo_musica1);

    if (aux3 != -1)
    {
        spotify[aux1].albuns[aux2].musicas[aux3].codigo_musica = novo_codigo;
        strcpy(spotify[aux1].albuns[aux2].musicas[aux3].nome_musica, novo_nome);
        spotify[aux1].albuns[aux2].musicas[aux3].tempo = novo_tempo;
        printf("Musica atualizada com sucesso!!\n");
    }

    else
        printf("Essa musica nao existe\n");
}

void CadastrarMusica(char nome_banda[], int codigo_banda, char nome_album[], int codigo_album, char nome_musica1[], int codigo_musica1, float tempo1)
{
    int aux1, aux2, aux;
    aux = ExisteMusica(nome_banda, codigo_banda, nome_album, codigo_album, nome_musica1, codigo_musica1);
    aux1 = PosicaoBanda(nome_banda, codigo_banda);
    aux2 = PosicaoAlbum(nome_banda, codigo_banda, nome_album, codigo_album);

    if (aux1 != -1 && aux2 != -1)
    {
        if (aux == -1)
        {
            strcpy(spotify[aux1].albuns[aux2].musicas[spotify[aux1].albuns[aux2].quantidade_musicas].nome_musica, nome_musica1);
            spotify[aux1].albuns[aux2].musicas[spotify[aux1].albuns[aux2].quantidade_musicas].codigo_musica = codigo_musica1;
            spotify[aux1].albuns[aux2].musicas[spotify[aux1].albuns[aux2].quantidade_musicas].tempo = tempo1;
            spotify[aux1].albuns[aux2].quantidade_musicas++;
            printf("Musica cadastrada com sucesso!!\n");
        }

        else
            printf("A musica ja foi cadastrada\n");
    }

    else
        printf("A banda ou o album nao foram cadastrados");
}

int main()
{
    int opcao;
    char nome_banda1[100], novo_nome[100], nome_banda_remover[100], nome_musica[100];
    int codigo_banda1, novo_codigo, codigo_banda_remover, codigo_musica;
    char nome_album1[100];
    int codigo_album1;
    double tempo;

    printf("________CATALOGO DE MUSICAS_______ \n\n");
    printf("[1]-   Adicionar  Banda.\n");
    printf("[2]-   Adicionar  Album.\n");
    printf("[3]-   Adicionar  Musica.\n");
    printf("[4]-   Visualizar Banda.\n");
    printf("[5]-   Visualizar Album.\n");
    printf("[6]-   Visualizar Musica.\n");
    printf("[7]-   Editar Banda.\n");
    printf("[8]-   Editar Album.\n");
    printf("[9]-   Editar Musica.\n");
    printf("[10]-  Remover Banda.\n");
    printf("[11]-  Remover Album.\n");
    printf("[12]-  Remover Musica.\n");
    printf("[13]-  Sair do menu.\n");
    printf("_________________________________________________\n");

    do
    {
        printf("\nEscolha uma opcao:\n");
        printf("----------------------------------\n");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            printf("--------add band---------\n");
            printf("Informe o nome da banda: ");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: ");
            scanf("%d", &codigo_banda1);

            CadastrarBanda(nome_banda1, codigo_banda1);
        }

        if (opcao == 2)
        {
            printf("--------add album---------\n");
            printf("Informe o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: \n");
            scanf("%d", &codigo_banda1);
            printf("Informe o nome do album: \n");
            scanf("%s", nome_album1);
            printf("Informe o codigo do album: \n");
            scanf("%d", &codigo_album1);

            CadastrarAlbum(nome_banda1, codigo_banda1, nome_album1, codigo_album1);
        }

        if (opcao == 3)
        {
            printf("\nSecurity Observation: Todos os dados solicitados sao uteis para o banco de arquivos e suas funcoes.\n\n");
            printf("--------add music---------\n");
            printf("Informe o nome da banda:\n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda:\n");
            scanf("%d", &codigo_banda1);
            printf("Informe o nome do album da musica que voce quer adicionar: \n");
            scanf("%s", nome_album1);
            printf("Informe o codigo do album:\n");
            scanf("%d", &codigo_album1);
            printf("Informe o nome da musica a adicionar: \n");
            scanf("%s", nome_musica);
            printf("Informe o codigo da musica que voce quer adicionar: \n");
            scanf("%d", &codigo_musica);
            printf("Informe o tempo de duracao da musica (obs: no formato 2.00): \n");
            scanf("%lf", &tempo);

            CadastrarMusica(nome_banda1, codigo_banda1, nome_album1, codigo_album1, nome_musica, codigo_musica, tempo);
        }

        if (opcao == 4)
        {
            printf("--------view band---------\n");
            printf("\nInforme o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("\nInforme o codigo da banda: \n");
            scanf("%d", &codigo_banda1);

            VisualizarBanda(nome_banda1, codigo_banda1);
        }

        if (opcao == 5)
        {
            printf("--------view album---------\n");
            printf("Informe o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: \n");
            scanf("%d", &codigo_banda1);
            printf("Informe o nome do album: \n");
            scanf("%s", nome_album1);
            printf("Informe o codigo do album: \n");
            scanf("%d", &codigo_album1);

            VisualizarAlbum(nome_banda1, codigo_banda1, nome_album1, codigo_album1);
        }

        if (opcao == 6)
        {
            printf("--------view music---------\n");
            printf("Informe o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: \n");
            scanf("%d", &codigo_banda1);
            printf("Informe o nome do album: \n");
            scanf("%s", nome_album1);
            printf("Informe o codigo do album: \n");
            scanf("%d", &codigo_album1);
            printf("Informe o nome da musica: \n");
            scanf("%s", nome_musica);
            printf("Informe o codigo da musica: \n");
            scanf("%d", &codigo_musica);

            VisualizarMusica(nome_banda1, codigo_banda1, nome_album1, codigo_album1, nome_musica, codigo_musica);
        }

        if (opcao == 7)
        {
            printf("--------edit band---------\n");
            printf("Informe o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: \n");
            scanf("%d", &codigo_banda1);
            printf("Informe o NOVO nome da banda: \n");
            scanf("%s", novo_nome);
            printf("Informe o NOVO codigo da banda: \n");
            scanf("%d", &novo_codigo);

            AtualizarBanda(nome_banda1, codigo_banda1, novo_nome, novo_codigo);
        }

        if (opcao == 8)
        {
            printf("--------edit album---------\n");
            printf("Informe o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: \n");
            scanf("%d", &codigo_banda1);
            printf("Informe o nome do album: \n");
            scanf("%s", nome_album1);
            printf("Informe o codigo do album: \n");
            scanf("%d", &codigo_album1);
            printf("Informe o NOVO nome do album: \n");
            scanf("%s", novo_nome);
            printf("Informe o NOVO codigo do album: \n");
            scanf("%d", &novo_codigo);

            AtualizarAlbum(nome_banda1, codigo_banda1, nome_album1, codigo_album1, novo_nome, novo_codigo);
        }

        if (opcao == 9)
        {
            printf("--------edit music---------\n");
            printf("Informe o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: \n");
            scanf("%d", &codigo_banda1);
            printf("Informe o nome do album: \n");
            scanf("%s", nome_album1);
            printf("Informe o codigo do album: \n");
            scanf("%d", &codigo_album1);
            printf("Informe o nome da musica: \n");
            scanf("%s", nome_musica);
            printf("Informe o codigo da musica: \n");
            scanf("%d", &codigo_musica);
            printf("Informe o NOVO nome da musica: \n");
            scanf("%s", novo_nome);
            printf("Informe o NOVO codigo da musica: \n");
            scanf("%d", &novo_codigo);
            printf("Informe o NOVO tempo da musica: \n");
            scanf("%d", &tempo);

            AtualizarMusica(nome_banda1, codigo_banda1, nome_album1, codigo_album1, nome_musica, codigo_musica, novo_nome, novo_codigo, tempo);
        }

        if (opcao == 10)
        {

            printf("--------remove band---------\n");
            printf("\nInforme o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("\nInforme o codigo da banda: \n");
            scanf("%d", &codigo_banda1);

            RemoverBanda(nome_banda1, codigo_banda1);
        }

        if (opcao == 11)
        {

            printf("--------remove album---------\n");
            printf("Informe o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: \n");
            scanf("%d", &codigo_banda1);
            printf("Informe o nome do album: \n");
            scanf("%s", nome_album1);
            printf("Informe o codigo do album: \n");
            scanf("%d", &codigo_album1);

            RemoverAlbum(nome_banda1, codigo_banda1, nome_album1, codigo_album1);
        }

        if (opcao == 12)
        {
            printf("--------remove music---------\n");
            printf("Informe o nome da banda: \n");
            scanf("%s", nome_banda1);
            printf("Informe o codigo da banda: \n");
            scanf("%d", &codigo_banda1);
            printf("Informe o nome do album: \n");
            scanf("%s", nome_album1);
            printf("Informe o codigo do album: \n");
            scanf("%d", &codigo_album1);
            printf("Informe o nome da musica: \n");
            scanf("%s", nome_musica);
            printf("Informe o codigo da musica: \n");
            scanf("%d", &codigo_musica);

            RemoverMusica(nome_banda1, codigo_banda1, nome_album1, codigo_album1, nome_musica, codigo_musica);
        }

    } while (opcao != 13);

    printf("Programa Finalizado...\nbip.. bip...\nbop...");
    
    return 0;
}