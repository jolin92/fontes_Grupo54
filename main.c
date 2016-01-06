/* 
 * File:   Boleias_Partilhadas.c
 * Author: Antonio Santana & Bruno Oliveira
 *
 * Created on 14 de Janeiro de 2013, 10:29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas.h"

/*
 * 
 */

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////Prototipos////////////////////////////////////////

const short TAMVIAGENS = 20;
const short TAMCONDUTORES = 5;
const short TAMAGENDA = 10;

void menu(viagem viagens[], const short TAMVIAGENS, condutor condutores[], const short TAMCONDUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_viagem, int cont_condutor, int cont_agenda);

unsigned long lerNumViagem(char mensagem[]) {
    unsigned long id_viagem;

    printf("%s", mensagem);
    scanf("%lu", &id_viagem);

    return id_viagem;
}

unsigned long lerNumCondutor(char mensagem[]) {
    unsigned long id_condutor;

    printf("%s", mensagem);
    scanf("%lu", &id_condutor);

    return id_condutor;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * Limpa o buffer de entrada de dados
 * Aviso: Caso o buffer de entrada nÃ£o contenha dados, a funÃ§Ã£o fica a aguardar que se introduzam dados 
 */
void clear_input() {
    char ch;

    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * LÃª uma cadeia de caracteres (string) atravÃ©s da stream stdin
 *
 * @param frase - Apontador para a frase lida.
 * @param tamanho - Tamanho mÃ¡ximo da frase a ser lida. @warning: O tamanho da frase
deve ter em conta o espaÃ§o para o caracter de tÃ©rmino da string ('\0')
 * @return 1 em caso de leitura com sucesso, 0 caso ocorra um erro.
 *
 * Exemplo:
 * char nome[100 + 1];
 * printf("Introduza o seu nome: ");
 * if (lerFrase (nome, 100 + 1) == 1)
 * printf("O nome lido e: %s", nome);
 */
unsigned char lerFrase(char * const frase, const unsigned int tamanho) {
    unsigned int sTam;
    if (fgets(frase, tamanho, stdin) != NULL) {
        sTam = strlen(frase) - 1;
        if (frase[sTam] == '\n')
            frase[sTam] = '\0';
        return 1;
    } else
        return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////*esta e a funcao necessaria para abrir ficheiro Viagem*////////////////////////////////////
void abrirViagem(viagem viagens[], const short TAMVIAGENS, int cont_viagem) {
    FILE *travel;
    travel = fopen("viagens.txt", "r");
    if ((travel == (FILE*) NULL)){
        printf("\n\n\tImpossivel abrir o ficheiro Viagem!\n\n");
        travel = fopen("viagens.txt", "w");
    }else {
        cont_viagem = fread(viagens, sizeof (viagem), TAMVIAGENS, travel);
        fclose(travel);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////*esta e a funcao necessaria para abrir ficheiro Condutor*////////////////////////////////////
void abrirCondutor(condutor condutores[], const short TAMCONDUTORES, int cont_condutor) {
    FILE *driver;
    condutor = fopen("condutores.txt", "r");
    
    if ((condutor == (FILE*) NULL)){
        printf("\n\n\tImpossivel abrir o ficheiro Condutor!\n\n");
        condutor = fopen("condutores.txt", "w");
    }else {
        cont_condutor = fread(condutores, sizeof (condutor), TAMCONDUTORES, driver);
        fclose(driver);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////*esta e a funcao necessaria para abrir ficheiro Agenda*////////////////////////////////////
void abrirAgenda(agendas agenda[], const short TAMAGENDA, int cont_agenda) {
    
    FILE *agendamento;
    agendamento = fopen("agendamento.txt", "r");
    
    if ((agendamento == (FILE*) NULL)) {
        printf("\n\n\tImpossivel abrir o ficheiro Agenda!\n\n");
        agendamento = fopen("agendamento.txt", "w");
    } else {
        cont_agenda = fread(agenda, sizeof (agendas), TAMAGENDA, agendamento);
        fclose(agendamento);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////*esta e a funcao necessaria para guardar o ficheiro Aluno*//////////////////////////////
void guardarViagem(viagem viagens[], const short TAMVIAGENS,agendas agenda[], const short TAMAGENDA, 
        int cont_viagem, int cont_agenda) {
    
    FILE *travel;
    
    travel = fopen("viagens.txt", "w");
    fwrite(viagens, sizeof (viagem), cont_viagem, travel);
    fclose(travel);

    printf("Guardado!\n");

    cont_agenda = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////*esta e a funcao necessaria para guardar o ficheiro Aluno*//////////////////////////////
void guardarCondutor(condutor condutores[], const short TAMCONDUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_condutor, int cont_agenda) {

    FILE *driver;

    condutor = fopen("condutores.txt", "w");
    fwrite(condutores, sizeof (condutor), cont_condutor, driver);
    fclose(driver);

    printf("Guardado!\n");

    cont_agenda = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////*esta e a funcao necessaria para guardar o ficheiro Agenda*//////////////////////////////
void guardarAgenda(agendas agenda[], const short TAMAGENDA, int cont_agenda) {

    FILE *agendamento;
    
    agendamento = fopen("agendamento.txt", "w");
    fwrite(agenda, sizeof (agendas), cont_agenda, agendamento);
    fclose(agendamento);

    printf("Guardado!\n");

    cont_agenda = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////*esta e a funcao responsavel pela pesquisa de alunos */////////////////////
//////////////////////////////*o modo de pesquisa e a pesquisa binaria*/////////////////////////////

int pesquisarViagem(int x, viagem viagens[], int cont_viagem) {
    int i;
    int l = 0; //Limite inferior
    int u = cont_viagem - 1; //Limite superior 

    while (l <= u) {
        i = l + (l - u) / 2;
        if (x == viagens[i].id) {
            return i;
        } else if (x < viagens[i].id) {
            u = i - 1;
        } else {
            l = i + 1;
        }
    }

    return -1; // nÃ£o encontrado
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////*esta e a funcao responsavel pela ordenacao de alunos */////////////////////////////////
///////////////////////*o modo de pesquisa e a pesquisa binaria*///////////////////////////////////////

ordenarViagem(int inf, int sup, viagem viagens[]) {
    int i, j;
    viagem temp;

    while (sup > inf) {
        i = inf;
        j = sup;
        temp = viagens[inf];
        while (i < j) {
            while (viagens[j].id > temp.id) {
                j--;
            }
            viagens[i] = viagens[j];
            while (i < j && viagens[i].id <= temp.id) {
                i++;
            }
            viagens[j] = viagens[i];
        }
        viagens[i] = temp;
        ordenarViagem(inf, i - 1, viagens);
        inf = i + 1;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////*funcao que vai criar os alunos *////////////////////////////////////////

unsigned int criarViagem(viagem viagens[], const short TAMVIAGENS, agendas agenda[], const short TAMAGENDA,
        int cont_viagem, int cont_agenda) {//Argumentos
    int x, i, ml, mc;

    if (cont_viagem == 20) {
        printf("Base de dados cheia\n");
    } else {
        //getchar();

        x = lerNumViagem("\nNumero de Viagem: ");

        i = pesquisarViagem(x, viagens, cont_viagem);
        if (i != -1) {
            printf("\nESSA VIAGEM JA EXISTE!\n");
        } else {
            viagens[cont_viagem].id = x;

            printf("\nLocal de Saida: ");
            clear_input();
            lerFrase(viagens[cont_viagem].l_inicio, NOME);

            printf("\nLocal de Destino: ");
            lerFrase(viagens[cont_viagem].l_destino, TAM);

            printf("\nNumero de Porta: ");
            scanf("%d", &alunos[cont_aluno].morada.nporta);

            printf("\nCodigo Postal: ");
            clear_input();
            lerFrase(alunos[cont_aluno].morada.cod_postal, SIZE);

            printf("\nLocalidade: ");
            lerFrase(alunos[cont_aluno].morada.localidade, TAM);

            printf("\nTelefone [XXX XXXXXX]: ");
            //lerFrase(alunos[cont_aluno].telefone.prefixo);
            scanf("%hu %d", &alunos[cont_aluno].telefone.indicativo, &alunos[cont_aluno].telefone.numero);

            printf("\nData de Nascimento [DD MM AA]: ");
            scanf("%hu %hu %d", &alunos[cont_aluno].data_nascimento.dia, &alunos[cont_aluno].data_nascimento.mes, &alunos[cont_aluno].data_nascimento.ano);

            printf("\nCategoria de Conducao [A=1,B=2,C=3,D=4]: ");
            scanf("%i", &alunos[cont_aluno].categorias);

            printf("\nRevalidacao da Carta [SIM=1,NAO=0]: ");
            scanf("%i", &alunos[cont_aluno].revalidacoes);

            /*Inicia a matriz com os valor a 0 e com espaÃ§o*/
            for (ml = 0; ml < LINHA; ml++) {
                for (mc = 0; mc < COLUNA; mc++) {
                    alunos[cont_aluno].agenda[ml][mc].id = 0;
                    strncpy(alunos[cont_aluno].agenda[ml][mc].nome, " ", NOME);
                }
            }
            cont_aluno++;
            ordenarAlunos(0, cont_aluno - 1, alunos);
            cont_agenda++;
        }
    }

    return cont_aluno;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////*funÃ§Ã£o para saber se o vector dos alunos estÃ¡ vazio*///////////////////////////

int estaVazioVectorAlunos(unsigned int cont_aluno) {
    return (cont_aluno == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////*funcao que vai remover os alunos*///////////////////////////////////////////////

unsigned int removerAluno(aluno alunos[], const short TAMALUNOS, int cont_aluno) {//Argumentos
    int x, i, z;

    if (estaVazioVectorAlunos(cont_aluno)) {
        printf("Nao existem alunos para remover!\n");
    } else {

        x = lerCartaoCidadao("Introduza o cc para remover: ");

        i = pesquisarAlunos(x, alunos, cont_aluno);

        if (i == -1) {
            printf("\nESSE ALUNO NAO EXISTE\n");
        } else {
            for (z = i; z < cont_aluno; z++) {
                alunos[z] = alunos[z + 1];
            }
            cont_aluno--;
        }
    }

    return cont_aluno;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* funcao que vai listar os alunos*////////////////////////////////

void listarAluno(aluno alunos[], unsigned int cont_aluno) {//Argumentos

    int i;

    if (cont_aluno == 0)
        printf("\nNao existem alunos para listar\n");
    else {
        for (i = 0; i < cont_aluno; i++) {
            printf("\n<---------------------------------->\n");
            printf("\nCartao de Cidadao: %ld", alunos[i].id_aluno);
            printf("\nNome do aluno: %s", alunos[i].nome);
            printf("\nRua: %s", alunos[i].morada.rua);
            printf("\nNumero de Porta: %d", alunos[i].morada.nporta);
            printf("\nCodigo Postal: %s ", alunos[i].morada.cod_postal);
            printf("\nLocalidade: %s ", alunos[i].morada.localidade);
            printf("\nTelefone: %hu-%d", /*alunos[i].telefone.prefixo,*/ alunos[i].telefone.indicativo, alunos[i].telefone.numero);
            printf("\nData de Nascimento: %hu/%hu/%d", alunos[i].data_nascimento.dia, alunos[i].data_nascimento.mes, alunos[i].data_nascimento.ano);

            switch (alunos[i].categorias) {
                case 1: printf("\nCategoria de Conducao: A");
                    break;
                case 2: printf("\nCategoria de Conducao: B");
                    break;
                case 3: printf("\nCategoria de Conducao: C");
                    break;
                case 4: printf("\nCategoria de Conducao: D");
                    break;
                case 5: break;
            }
            switch (alunos[i].revalidacoes) {
                case 1: printf("\nRevalidacao da Carta: SIM");
                    break;
                case 0: printf("\nRevalidacao da Carta: NAO");
                    break;
                case 2: break;
            }
        }
        printf("\n<---------------------------------->\n");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////*funcao que vai alterar os alunos*/////////////////////////////////////

void alterarAluno(aluno alunos[], int cont_aluno) { //Argumentos
    int x, i, a;

    if (estaVazioVectorAlunos(cont_aluno)) {
        printf("\nNao existem alunos para alterar!\n");
    } else {

        x = lerCartaoCidadao("\nIntroduza o cc para alterar: ");
        i = pesquisarAlunos(x, alunos, cont_aluno);
        if (i == -1) {
            printf("\nNao existe o CC introduzido!\n");
        } else {
            x = lerCartaoCidadao("\nCartao de Cidadao do aluno [XXXXXXXXX]: ");
            a = pesquisarAlunos(x, alunos, cont_aluno);
            if (a != -1) {
                printf("\nESSE CC JA EXISTE!\n");
            } else {
                alunos[i].id_aluno = x;

                printf("\nNome do Aluno: ");
                clear_input();
                lerFrase(alunos[i].nome, NOME);

                printf("\nRua: ");
                lerFrase(alunos[i].morada.rua, TAM);

                printf("\nNumero de Porta: ");
                scanf("%d", &alunos[i].morada.nporta);

                printf("\nCodigo Postal: ");
                clear_input();
                lerFrase(alunos[i].morada.cod_postal, SIZE);

                printf("\nLocalidade: ");
                lerFrase(alunos[i].morada.localidade, TAM);

                printf("\nTelefone [XXX XXXXXX]: ");
                //gets(alunos[cont_aluno].telefone.prefixo);
                scanf("%hu-%d", &alunos[i].telefone.indicativo, &alunos[i].telefone.numero);

                printf("\nData de Nascimento [DD MM AA]: ");
                scanf("%hu/%hu/%d", &alunos[i].data_nascimento.dia, &alunos[i].data_nascimento.mes, &alunos[i].data_nascimento.ano);

                printf("\nCategoria de Conducao [A=1,B=2,C=3,D=4]: ");
                scanf("%i", &alunos[i].categorias);

                printf("\nRevalidacao da Carta [SIM=1,NAO=0]: ");
                scanf("%i", &alunos[i].revalidacoes);

                ordenarAlunos(0, cont_aluno - 1, alunos);

            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////*esta e a funcao responsavel pela pesquisa de instrutores */////////////////
//////////////////////////////*o modo de pesquisa e a pesquisa binaria*/////////////////////////////

int pesquisarInstrutor(int x, instrutor instrutores[], int cont_instrutor) {
    int i;
    int l = 0; //Limite inferior
    int u = cont_instrutor - 1; //Limite superior
    while (l <= u) {
        i = l + (l - u) / 2;
        if (x == instrutores[i].numero_instrutor) {
            return i;
        } else if (x < instrutores[i].numero_instrutor) {
            u = i - 1;
        } else {
            l = i + 1;
        }
    }
    return -1; //Nao encontrado
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////*esta e a funcao responsavel pela ordenaÃ§Ã£o de instrutores *////////////////////////
///////////////////////*o modo de pesquisa e a pesquisa binaria*//////////////////////////////////////

ordenarInstrutores(int inf, int sup, instrutor instrutores[]) {
    int i, j;
    instrutor temp;

    while (sup > inf) {
        i = inf;
        j = sup;
        temp = instrutores[inf];
        while (i < j) {
            while (instrutores[j].numero_instrutor > temp.numero_instrutor) {
                j--;
            }
            instrutores[i] = instrutores[j];
            while (i < j && instrutores[i].numero_instrutor <= temp.numero_instrutor) {
                i++;
            }
            instrutores[j] = instrutores[i];
        }
        instrutores[i] = temp;
        ordenarInstrutores(inf, i - 1, instrutores);
        inf = i + 1;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////* funcao que vai criar os instrutores *//////////////////////////////////////////////////

unsigned int criarInstrutor(instrutor instrutores[], const short TAMINSTRUTORES, agendas agenda[], const short TAMAGENDA,
        int cont_instrutor) {

    int x, i, ml, mc;

    if (cont_instrutor == 5)
        printf("Base de dados cheia\n");
    else {
        x = lerLicenca("\nLicenca do instrutor: ");

        i = pesquisarInstrutor(x, instrutores, cont_instrutor);
        if (i != -1) {
            printf("\nESSE NUMERO JA EXISTE!");
        } else {
            instrutores[cont_instrutor].numero_instrutor = x;

            printf("\nNome do Instrutor: ");
            clear_input();
            lerFrase(instrutores[cont_instrutor].nome, NOME);

            printf("\nRua: ");
            lerFrase(instrutores[cont_instrutor].morada.rua, TAM);

            printf("\nNumero de Porta: ");
            scanf("%d", &instrutores[cont_instrutor].morada.nporta);

            printf("\nCodigo Postal: ");
            clear_input();
            lerFrase(instrutores[cont_instrutor].morada.cod_postal, SIZE);

            printf("\nLocalidade: ");
            lerFrase(instrutores[cont_instrutor].morada.localidade, TAM);

            printf("\nTelefone [XXX XXXXXX]: ");
            //gets(instrutores[cont_aluno].telefone.prefixo);
            scanf("%hu %d", &instrutores[cont_instrutor].telefone.indicativo, &instrutores[cont_instrutor].telefone.numero);

            printf("\nData de Nascimento [DD MM AA]: ");
            scanf("%hu %hu %d", &instrutores[cont_instrutor].data_nascimento.dia, &instrutores[cont_instrutor].data_nascimento.mes, &instrutores[cont_instrutor].data_nascimento.ano);

            printf("\nCategoria de Conducao [A=1,B=2,C=3,D=4]: ");
            scanf("%i", &instrutores[cont_instrutor].categorias);

            printf("\nSalario: ");
            scanf("%f", &instrutores[cont_instrutor].salario);

            /*Inicia a matriz com os valor a 0 e com espaÃ§o*/
            for (ml = 0; ml < LINHA; ml++) {
                for (mc = 0; mc < COLUNA; mc++) {
                    instrutores[cont_instrutor].agenda[ml][mc].id = 0;
                    strncpy(instrutores[cont_instrutor].agenda[ml][mc].nome, "_", NOME);
                }
            }
            cont_instrutor++;
            ordenarInstrutores(0, cont_instrutor - 1, instrutores);
        }
    }
    return cont_instrutor;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////*funÃ§Ã£o para saber se o vector dos instrutores estÃ¡ vazio*////////////////////

int estaVazioVectorIntrutor(unsigned int cont_instrutor) {
    return (cont_instrutor == 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////*funcao que vai remover os instrutores*///////////////////////////////////////////

unsigned int removerInstrutor(instrutor instrutores[], const short TAMINSTRUTORES,
        int cont_instrutor) {
    int x, i, z;

    if (estaVazioVectorIntrutor(cont_instrutor)) {
        printf("\nNao existem instrutores para remover!\n");
    } else {

        x = lerLicenca("Licenca do instrutor: ");

        i = pesquisarInstrutor(x, instrutores, cont_instrutor);

        if (i == -1) {
            printf("\nESSE INSTRUTOR NAO EXISTE\n");
        } else {
            for (z = i; z < cont_instrutor; z++) {
                instrutores[z] = instrutores[z + 1];
            }
            cont_instrutor--;

        }
        return cont_instrutor;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* funcao que vai listar os instrutores*///////////////////////////

void listarInstrutor(instrutor instrutores[], const short TAMINSTRUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_instrutor, int cont_agenda) {
    int i;

    if (cont_instrutor == 0)
        printf("\nNao existem instrutores para listar\n");
    else {
        for (i = 0; i < cont_instrutor; i++) {
            printf("\n<---------------------------------->\n");
            printf("\nNumero de licenca: %ld", instrutores[i].numero_instrutor);
            printf("\nNome do instrutor: %s", instrutores[i].nome);
            printf("\nRua: %s", instrutores[i].morada.rua);
            printf("\nNumero de Porta: %d", instrutores[i].morada.nporta);
            printf("\nCodigo Postal: %s ", instrutores[i].morada.cod_postal);
            printf("\nLocalidade: %s ", instrutores[i].morada.localidade);
            printf("\nTelefone: %hu-%d", /*instrutores[i].telefone.prefixo,*/ instrutores[i].telefone.indicativo, instrutores[i].telefone.numero);
            printf("\nData de Nascimento: %hu/%hu/%d", instrutores[i].data_nascimento.dia, instrutores[i].data_nascimento.mes, instrutores[i].data_nascimento.ano);

            switch (instrutores[i].categorias) {
                case 1: printf("\nCategoria de Conducao: A");
                    break;                    
                case 2: printf("\nCategoria de Conducao: B");
                    break;                   
                case 3: printf("\nCategoria de Conducao: C");
                    break;                    
                case 4: printf("\nCategoria de Conducao: D");
                    break;                  
                case 5: break;
            }
            printf("\nSalario: %f", instrutores[i].salario);
        }
        printf("\n<---------------------------------->\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////* funcao que vai alterar os instrutores*/////////////////////////////

void alterarInstrutor(instrutor instrutores[], const short TAMINSTRUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_instrutor, int cont_agenda) {
    int x, i, a;

    if (cont_instrutor == 0) {
        printf("\nNao existem instrutores para alterar\n");
    } else {

        x = lerLicenca("\nLicenca do instrutor: ");

        i = pesquisarInstrutor(x, instrutores, cont_instrutor);
        if (i == -1) {
            printf("\nNao existe o numero introduzido!\n");
        } else {

            printf("\nNumero de licenca?: ");
            scanf("%ld", &x);
            a = pesquisarInstrutor(x, instrutores, cont_instrutor);
            if (a != -1) {
                printf("\nESSE NUMERO JA EXISTE!\n");
            } else {
                instrutores[i].numero_instrutor = x;
                printf("\nNome do Instrutor: ");
                clear_input();
                lerFrase(instrutores[i].nome, NOME);

                printf("\nRua: ");
                lerFrase(instrutores[i].morada.rua, TAM);

                printf("\nNumero de Porta: ");
                scanf("%d", &instrutores[i].morada.nporta);

                printf("\nCodigo Postal: ");
                clear_input();
                lerFrase(instrutores[i].morada.cod_postal, SIZE);

                printf("\nLocalidade: ");
                lerFrase(instrutores[i].morada.localidade, TAM);

                printf("\nTelefone [XXX XXXXXX]: ");
                //gets(instrutores[cont_aluno].telefone.prefixo);
                scanf("%hu %d", &instrutores[i].telefone.indicativo, &instrutores[i].telefone.numero);

                printf("\nData de Nascimento [DD MM AA]: ");
                scanf("%hu %hu %d", &instrutores[i].data_nascimento.dia, &instrutores[i].data_nascimento.mes, &instrutores[i].data_nascimento.ano);

                printf("\nCategoria de Conducao [A=1,B=2,C=3,D=4]: ");
                scanf("%i", &instrutores[i].categorias);

                printf("Salario: ");
                scanf("%f", &instrutores[i].salario);

                ordenarInstrutores(0, cont_instrutor - 1, instrutores);

            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////* funcao responsavel pelo menu dos alunos */////////////////////////

unsigned int menuAlunos(aluno alunos[], const short TAMALUNOS, agendas agenda[], const short TAMAGENDA,
        int cont_aluno , int cont_agenda) { //Argumentos
    int optn;
    do {
        do {
            printf("\n__________________________________________\n");
            printf("\n------------------Alunos------------------\n");
            printf("1----> Criar Aluno\n");
            printf("2----> Remover Aluno\n");
            printf("3----> Listar Aluno\n");
            printf("4----> Alterar Aluno\n");
            printf("5----> Voltar Atras\n");
            printf("__________________________________________\nIntroduza a opcao: ");
            scanf("%d", &optn);
        } while ((optn < 1) || (optn > 5));

        switch (optn) {
            case 1: cont_aluno = criarAluno(alunos, TAMALUNOS, agenda, TAMAGENDA, cont_aluno, cont_agenda);
                break;
                
            case 2: cont_aluno = removerAluno(alunos, TAMALUNOS, cont_aluno);
                break;
                
            case 3: listarAluno(alunos, cont_aluno);
                break;
                
            case 4: alterarAluno(alunos, cont_aluno);
                break;
                
            case 5:
                break;
        }
    } while (optn != 5);

    return cont_aluno;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////* funcao responsavel pelo menu dos instrutores *///////////////////

unsigned int menuInstrutores(instrutor instrutores[], const short TAMINSTRUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_instrutor, int cont_agenda) {

    int optn;
    do {
        do {
            printf("\n__________________________________________\n");
            printf("\n----------------Instrutores---------------\n");
            printf("1----> Criar Instrutor\n");
            printf("2----> Remover Instrutor\n");
            printf("3----> Listar Instrutor\n");
            printf("4----> Alterar Instrutor\n");
            printf("5----> Voltar Atras\n");
            printf("__________________________________________\nIntroduza a opcao: ");
            scanf("%d", &optn);
        } while ((optn < 1) || (optn > 5));

        switch (optn) {
            case 1: cont_instrutor = criarInstrutor(instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor);
                break;
                
            case 2: cont_instrutor = removerInstrutor(instrutores, TAMINSTRUTORES, cont_instrutor);
                break;
                
            case 3: listarInstrutor(instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor, cont_agenda);
                break;
                
            case 4: alterarInstrutor(instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor, cont_agenda);
                break;
                
            case 5:
                break;
        }
    } while (optn != 5);
    return cont_instrutor;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////*funcao que vai criar a aula*/////////////////////////////////////

void criarAula(aluno alunos[], const short TAMALUNOS, instrutor instrutores[], const short TAMINSTRUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_instrutor, int cont_aluno, int cont_agenda) {

    unsigned long int cc, licenca;
    int nlicenca, ncc, dia, hora;


    if ((cont_aluno != 0) && (cont_instrutor != 0)) {

        cc = lerCartaoCidadao("\nCartao de Cidadao do aluno: ");

        ncc = pesquisarAlunos(cc, alunos, cont_aluno);
        if (ncc != -1) {
            do {
                printf("Insira o dia da semana [Segunda=0,Terca=1..Sabado=5]: ");
                scanf("%i", &dia);
                if ((dia < 0) || (dia > 5))
                    printf("Dados Invalidos!\n");

            } while (dia < 0 || dia > 5);
            do {
                printf("Insira a hora [9h=0,10h=1..17h=8]: ");
                scanf("%i", &hora);
                if ((hora < 0) || (hora > 8))
                    printf("Dados Invalidos!\n");

            } while (hora < 0 || hora > 8);

            licenca = lerLicenca("Licenca do instrutor: ");

            nlicenca = pesquisarInstrutor(licenca, instrutores, cont_instrutor);

            alunos[ncc].agenda[hora][dia].id = alunos[ncc].id_aluno;
            strncpy(alunos[ncc].agenda[hora][dia].nome, alunos[ncc].agenda[hora][dia].nome, NOME);
            instrutores[nlicenca].agenda[hora][dia].id = alunos[ncc].id_aluno;
            strncpy(instrutores[nlicenca].nome, instrutores[nlicenca].agenda[hora][dia].nome, NOME);
            
    
        }
    } else if (cont_aluno == 0) {
        printf("Nao existe alunos \n");
    } else if (cont_instrutor == 0) {
        printf("Nao existe instrutores \n");
    } else if ((cont_aluno == 0) && (cont_instrutor == 0)) {
        printf("Nao existe alunos nem instrutores \n");
    }
    cont_agenda++;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////*funcao que vai cancelar a agenda*////////////////////////////////////

void removerAgenda(aluno alunos[], const short TAMALUNOS, instrutor instrutores[], const short TAMINSTRUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_instrutor, int cont_aluno, int cont_agenda) {

    unsigned long int cc, licenca;
    int ncc, nlicenca, dia, hora, x;


    if ((cont_aluno != 0) && (cont_instrutor != 0)) {

        cc = lerCartaoCidadao("Cartao de Cidadao do aluno: ");

        ncc = pesquisarAlunos(cc, alunos, cont_aluno);
        if (ncc != -1) {
            do {
                printf("Insira o dia da semana [Segunda=0,Terca=1..Sabado=5]: ");
                scanf("%i", &dia);
                if ((dia < 0) || (dia > 5))
                    printf("Dados Invalidos!\n");

            } while (dia < 0 || dia > 5);
            do {
                printf("Insira a hora [9h=0,10h=1..17h=8]: ");
                scanf("%i", &hora);
                if ((hora < 0) || (hora > 8))
                    printf("Dados Invalidos!\n");

            } while (hora < 0 || hora > 8);

            licenca = lerLicenca("Licenca do instrutor: ");

            nlicenca = pesquisarInstrutor(licenca, instrutores, cont_instrutor);

            alunos[ncc].agenda[hora][dia].id = 0;
            instrutores[nlicenca].agenda[hora][dia].id = 0;

        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////*funcao que vai listar/consultar a agenda*////////////////////////////////

void listarAgenda(aluno alunos[], const short TAMALUNOS, instrutor instrutores[], const short TAMINSTRUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_instrutor, int cont_aluno, int cont_agenda) {

    unsigned long int cc, licenca;
    int i, ncc, nlicenca, ml, mc, x;
    i = 0;

    //if ((cont_aluno != 0) && (cont_instrutor != 0)) {
    cc = lerCartaoCidadao("\nCartao de Cidadao do aluno: ");

    ncc = pesquisarAlunos(cc, alunos, cont_aluno);
    //x = alunos[ncc].categorias; 
    licenca = lerLicenca("Licenca do instrutor: ");

    nlicenca = pesquisarInstrutor(licenca, instrutores, cont_instrutor);

    i = pesquisarInstrutor(nlicenca, instrutores, cont_instrutor);

    int y = 9;
    printf("Aulas do instrutor : %d\n\n", instrutores[nlicenca].numero_instrutor);
    printf("Horas\tSegunda\tTerca\tQuarta\tQuinta\tSexta\tSabado\n");
    printf("%i\t", y);
    for (ml = 0; ml < LINHA; ml++) {
        for (mc = 0; mc < COLUNA; mc++) {

            printf("%i", alunos[ncc].agenda[ml][mc].id);
            printf("\t");
            if (mc == 5 && y<17) {
                printf("\n%i\t", ++y);
            }
        }
        //   }

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////*funcao que vai alterar a agenda*//////////////////////////////////////////////

void alterarAgenda(aluno alunos[], instrutor instrutores[], int cont_instrutor, int cont_aluno) {
        
    unsigned long int cc, licenca;
    int ncc, nlicenca, dia, hora, x;


    if ((cont_aluno != 0) && (cont_instrutor != 0)) {

        cc = lerCartaoCidadao("Cartao de Cidadao do aluno: ");

        ncc = pesquisarAlunos(cc, alunos, cont_aluno);
        if (ncc != -1) {
            do {
                printf("Insira o dia da semana que vai alterar [Segunda=0,Terca=1..Sabado=5]: ");
                scanf("%i", &dia);
                if ((dia < 0) || (dia > 5))
                    printf("Dados Invalidos!\n");

            } while (dia < 0 || dia > 5);
            do {
                printf("Insira a hora que vai alterar [9h=0,10h=1..17h=8]: ");
                scanf("%i", &hora);
                if ((hora < 0) || (hora > 8))
                    printf("Dados Invalidos!\n");

            } while (hora < 0 || hora > 8);
            licenca = lerLicenca("Licenca do instrutor: ");

            nlicenca = pesquisarInstrutor(licenca, instrutores, cont_instrutor);
            alunos[ncc].agenda[hora][dia].id = 0;
            instrutores[nlicenca].agenda[hora][dia].id = 0;
            
            }
            {
            do {
                printf("Insira o dia da semana [Segunda=0,Terca=1..Sabado=5]: ");
                scanf("%i", &dia);
                if ((dia < 0) || (dia > 5))
                    printf("Dados Invalidos!\n");

            } while (dia < 0 || dia > 5);
            do {
                printf("Insira a hora [9h=0,10h=1..17h=8]: ");
                scanf("%i", &hora);
                if ((hora < 0) || (hora > 8))
                    printf("Dados Invalidos!\n");

            } while (hora < 0 || hora > 8);
            licenca = lerLicenca("Licenca do instrutor: ");

            nlicenca = pesquisarInstrutor(licenca, instrutores, cont_instrutor);
            
            alunos[ncc].agenda[hora][dia].id = alunos[ncc].id_aluno;
            strncpy(alunos[ncc].agenda[hora][dia].nome, alunos[ncc].agenda[hora][dia].nome, NOME);
            instrutores[nlicenca].agenda[hora][dia].id = alunos[ncc].id_aluno;
            strncpy(instrutores[nlicenca].nome, instrutores[nlicenca].agenda[hora][dia].nome, NOME);

        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////* funcao responsavel pelo menu da agenda */////////////////////////////

void menuAgenda(aluno alunos[], const short TAMALUNOS, instrutor instrutores[], const short TAMINSTRUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_instrutor, int cont_aluno, int cont_agenda) {
    int optn;
    do {
        do {
            printf("\n__________________________________________\n");
            printf("\n------------------Agenda------------------\n");
            printf("1----> Criar Aula\n");
            printf("2----> Cancelar Agenda\n");
            printf("3----> Consultar Agenda\n");
            printf("4----> Alterar Agenda\n");
            printf("5----> Voltar Atras\n");
            printf("__________________________________________\nIntroduza a opcao: ");
            scanf("%d", &optn);
        } while ((optn < 1) || (optn > 5));

        switch (optn) {
            case 1: criarAula(alunos, TAMALUNOS, instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor, cont_aluno, cont_agenda);
                break;
                
            case 2: removerAgenda(alunos, TAMALUNOS, instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor, cont_aluno, cont_agenda);
                break;
                
            case 3: listarAgenda(alunos, TAMALUNOS, instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor, cont_aluno, cont_agenda);
                break;
                
            case 4: alterarAgenda(alunos, instrutores, cont_instrutor, cont_aluno);
                break;
                
            case 5:
                break;
        }
    } while (optn != 5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////* funcao responsavel pelo menu principal *///////////////////////////////////////////////
//////////////E apartir desta funcao que vao ser invocados todos os outros menus com respectivas funcoes *///////////

void menu(aluno alunos[], const short TAMALUNOS, instrutor instrutores[], const short TAMINSTRUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_instrutor, int cont_aluno, int cont_agenda) {
    int optn;
    do {
        do {
            printf("__________________________________________\n\n");
            printf("---------O que pretende fazer?------------\n\n");
            printf("1---->Alunos\n");
            printf("2---->Instrutores\n");
            printf("3---->Agendamento\n");
            printf("4---->Abrir\n");
            printf("5---->Guardar\n");
            printf("6---->Sair\n");
            printf("__________________________________________\nIntroduza a opcao: ");
            scanf("%d", &optn);
        } while ((optn < 1) || (optn > 6));

        switch (optn) {
            case 1: cont_aluno = menuAlunos(alunos, TAMALUNOS, agenda, TAMAGENDA, cont_aluno, cont_agenda);
                break;
                
            case 2: cont_instrutor = menuInstrutores(instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor, cont_agenda);
                break;
                
            case 3: menuAgenda(alunos, TAMALUNOS, instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor, cont_aluno, cont_agenda);
                break;
                
            case 4: abrirAluno(alunos, TAMALUNOS, cont_aluno);
                    abrirInstrutor(instrutores, TAMINSTRUTORES, cont_instrutor);
                    abrirAgenda(agenda, TAMAGENDA, cont_agenda);
                break;

            case 5: guardarAluno(alunos, TAMALUNOS, agenda, TAMAGENDA, cont_aluno, cont_agenda);
                    guardarInstrutor(instrutores, TAMINSTRUTORES, agenda, TAMAGENDA, cont_instrutor, cont_agenda);
                    guardarAgenda(agenda, TAMAGENDA, cont_agenda);
                break;

            case 6: //exit(1);
                break;

        }
    } while (optn != 6);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int cont_viagem = 0;
    int cont_condutor = 0;
    int cont_agenda = 0;
    viagem viagens[TAMVIAGENS];
    condutor condutores[TAMCONDUTORES];
    agendas agenda[TAMAGENDA];
    unsigned int x, y;

    menu(viagens, TAMVIAGENS, condutores, TAMCONDUTORES, agenda, TAMAGENDA, cont_viagem, cont_condutor, cont_agenda);
    printf("\nEste trabalho foi realizado por:\nAntonio Santana & Bruno Oliveira\n");
    return (EXIT_SUCCESS);
}