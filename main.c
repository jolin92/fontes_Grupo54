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
#include "LP_Leitura.h"
#include "LP_Utils.h"

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////*esta e a funcao necessaria para abrir ficheiro Viagem*////////////////////////////////////

void abrirViagem(viagem viagens[], const short TAMVIAGENS, int cont_viagem) {
    FILE *travel;
    travel = fopen("viagens.txt", "r");
    if ((travel == (FILE*) NULL)) {
        printf("\n\n\tImpossivel abrir o ficheiro Viagem!\n\n");
        travel = fopen("viagens.txt", "w");
    } else {
        cont_viagem = fread(viagens, sizeof (viagem), TAMVIAGENS, travel);
        fclose(travel);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////*esta e a funcao necessaria para abrir ficheiro Condutor*////////////////////////////////////

void abrirCondutor(condutor condutores[], const short TAMCONDUTORES, int cont_condutor) {
    FILE *driver;
    condutor = fopen("condutores.txt", "r");

    if ((condutor == (FILE*) NULL)) {
        printf("\n\n\tImpossivel abrir o ficheiro Condutor!\n\n");
        condutor = fopen("condutores.txt", "w");
    } else {
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

void guardarViagem(viagem viagens[], const short TAMVIAGENS, agendas agenda[], const short TAMAGENDA,
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

    //clrscr();

    if (cont_viagem == 20) {
        printf("Base de dados cheia\n");
    } else {

        i++;
        i = pesquisarViagem(x, viagens, cont_viagem);
        if (i != -1) {
            printf("\nESSA VIAGEM JA EXISTE!\n");
        } else {
            viagens[cont_viagem].id = x;

            cleanInputBuffer();
            readString(viagens[cont_viagem].l_inicio, NOME, "\n\tLocal de Saida: ");

            cleanInputBuffer();
            readString(viagens[cont_viagem].l_destino, TAM, "\n\tLocal de Destino: ");

            cleanInputBuffer();
            printf("\nData de Saida: ");
            scanf("%hu %hu %d", &viagens[cont_viagem].data_saida.dia, &viagens[cont_viagem].data_saida.mes, &viagens[cont_viagem].data_saida.ano);

            printf("\nHora de Saida: ");
            cleanInputBuffer();
            scanf("%hu %hu", &viagens[cont_viagem].hora_saida.hora, &viagens[cont_viagem].hora_saida.min);

            cleanInputBuffer();
            readString("%i", &viagens[cont_viagem].lug_disp, TAM, "\n\tLugares Disponiveis: ");

            printf("\nConforto do Veiculo? [Basico=1,Confortavel=2,Luxuoso=3]: ");
            scanf("%i", &viagens[cont_viagem].t_conforto);

            printf("\nCusto: ");
            scanf("%f", &viagens[cont_viagem].custo);

            printf("\nRevalidacoes?: ");
            scanf("%f", &viagens[cont_viagem].revalidacoes);


            /*Inicia a matriz com os valor a 0 e com espaÃ§o*/
            for (ml = 0; ml < LINHA; ml++) {
                for (mc = 0; mc < COLUNA; mc++) {
                    viagens[cont_viagem].agenda[ml][mc].id = 0;
                    strncpy(viagens[cont_viagem].agenda[ml][mc].nome, " ", NOME);
                }
            }
            cont_viagem++;
            ordenarViagem(0, cont_viagem - 1, viagens);
            cont_agenda++;
        }
    }

    return cont_viagem;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////*funÃ§Ã£o para saber se o vector dos alunos estÃ¡ vazio*///////////////////////////

int estaVazioVectorViagens(unsigned int cont_viagem) {
    return (cont_viagem == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////*funcao que vai remover os alunos*///////////////////////////////////////////////

unsigned int removerViagem(viagem viagens[], const short TAMVIAGENS, int cont_viagem) {//Argumentos
    int x, i, z;

    if (estaVazioVectorViagens(cont_viagem)) {
        printf("Nao existem viagens para remover!\n");
    } else {


        printf("\nIntroduza o numero da Viagem para remover: ");
        x = scanf("%i", &viagens[cont_viagem].id);
        i = pesquisarViagem(x, viagem, cont_viagem);

        if (i == -1) {
            printf("\nESSA VIAGEM NAO EXISTE\n");
        } else {
            for (z = i; z < cont_viagem; z++) {
                viagens[z] = viagens[z + 1];
            }
            cont_viagem--;
        }
    }

    return cont_viagem;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* funcao que vai listar os alunos*////////////////////////////////

void listarViagem(viagem viagens[], unsigned int cont_viagem) {//Argumentos

    int i;

    if (cont_viagem == 0)
        printf("\nNao existem alunos para listar\n");
    else {
        for (i = 0; i < cont_viagem; i++) {
            printf("\n<---------------------------------->\n");
            printf("\nNumero de Viagem: %ld", viagens[i].id);
            printf("\nLocal de Partida: %s", viagens[i].l_inicio);
            printf("\nDestino: %s", viagens[i].l_destino);
            printf("\nData de Saida: %hu/%hu/%d", viagens[i].data_saida.dia, viagens[i].data_saida.mes, viagens[i].data_saida.ano);
            printf("\nLugares Disponiveis: %hu", viagens[i].lug_disp);
            printf("\nTipo de Conforto: %s", viagens[i].t_conforto);


            switch (viagens[i].t_conforto) {
                case 1: printf("\nBasico: 1");
                    break;
                case 2: printf("\nConfortavel: 2");
                    break;
                case 3: printf("\nLuxuoso: 3");
                    break;
                case 4: break;
            }
            switch (viagens[i].revalidacoes) {
                case 1: printf("\nRevalidacao: SIM");
                    break;
                case 0: printf("\nRevalidacao: NAO");
                    break;
                case 2: break;
            }
            printf("\nCusto da Viagem: %s ", viagens[i].custo);
        }
        printf("\n<---------------------------------->\n");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////*funcao que vai alterar os alunos*/////////////////////////////////////

void alterarViagem(viagem viagens[], int cont_viagem) { //Argumentos
    int x, i, a;

    if (estaVazioVectorViagens(cont_viagem)) {
        printf("\nNao existe viagens para alterar!\n");
    } else {

        printf("\nIntroduza o numero da Viagem para remover: ");
        x = scanf("%i", &viagens[cont_viagem].id);
        i = pesquisarViagem(x, viagens, cont_viagem);
        if (i == -1) {
            printf("\nNao existe a viagem introduzido!\n");
        } else {
            printf("\nIntroduza o numero da Viagem para remover: ");
            x = scanf("%i", &viagens[cont_viagem].id);
            a = pesquisarViagem(x, viagens, cont_viagem);
            if (a != -1) {
                printf("\nESSA VIAGEM JA EXISTE!\n");
            } else {
                viagens[i].id = x;

                cleanInputBuffer();
                readString(viagens[cont_viagem].l_inicio, NOME, "\n\tLocal de Saida: ");

                cleanInputBuffer();
                readString(viagens[cont_viagem].l_destino, TAM, "\n\tLocal de Destino: ");

                cleanInputBuffer();
                printf("\nData de Saida: ");
                scanf("%hu %hu %d", &viagens[cont_viagem].data_saida.dia, &viagens[cont_viagem].data_saida.mes, &viagens[cont_viagem].data_saida.ano);

                printf("\nHora de Saida: ");
                cleanInputBuffer();
                scanf("%hu %hu", &viagens[cont_viagem].hora_saida.hora, &viagens[cont_viagem].hora_saida.min);

                cleanInputBuffer();
                readString("%i", &viagens[cont_viagem].lug_disp, TAM, "\n\tLugares Disponiveis: ");

                printf("\nConforto do Veiculo? [Basico=1,Confortavel=2,Luxuoso=3]: ");
                scanf("%i", &viagens[cont_viagem].t_conforto);

                printf("\nCusto: ");
                scanf("%f", &viagens[cont_viagem].custo);

                printf("\nRevalidacoes?: ");
                scanf("%f", &viagens[cont_viagem].revalidacoes);


                ordenarViagem(0, cont_viagem - 1, viagens);

            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////*esta e a funcao responsavel pela pesquisa de instrutores */////////////////
//////////////////////////////*o modo de pesquisa e a pesquisa binaria*/////////////////////////////

int pesquisarCondutor(int x, condutor condutores[], int cont_condutor) {
    int i;
    int l = 0; //Limite inferior
    int u = cont_condutor - 1; //Limite superior
    while (l <= u) {
        i = l + (l - u) / 2;
        if (x == condutores[i].numero_condutor) {
            return i;
        } else if (x < condutores[i].numero_condutor) {
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

ordenarCondutor(int inf, int sup, condutor condutores[]) {
    int i, j;
    condutor temp;

    while (sup > inf) {
        i = inf;
        j = sup;
        temp = condutores[inf];
        while (i < j) {
            while (condutores[j].numero_condutor > temp.numero_condutor) {
                j--;
            }
            condutores[i] = condutores[j];
            while (i < j && condutores[i].numero_condutor <= temp.numero_condutor) {
                i++;
            }
            condutores[j] = condutores[i];
        }
        condutores[i] = temp;
        ordenarCondutor(inf, i - 1, condutores);
        inf = i + 1;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////* funcao que vai criar os instrutores *//////////////////////////////////////////////////

unsigned int criarCondutor(condutor condutores[], const short TAMCONDUTORES, agendas agenda[], const short TAMAGENDA,
        int cont_condutor) {

    int x, i, ml, mc;

    if (cont_condutor == 5)
        printf("Base de dados cheia\n");
    else {
        printf("\nIntroduza o numero do condutor: ");
        x = scanf("%i", &condutores[cont_condutor].numero_condutor);

        i = pesquisarCondutor(x, condutores, cont_condutor);
        if (i != -1) {
            printf("\nESSE NUMERO JA EXISTE!");
        } else {
            condutores[cont_condutor].numero_condutor = x;

            cleanInputBuffer();
            readString(condutores[cont_condutor].nome, NOME, "\n\tNome do Condutor: ");

            cleanInputBuffer();
            printf("\ntelefone [XXX XXXXXX]: ");
            scanf("%hu %d", &condutores[cont_condutor].telefone.indicativo, &condutores[cont_condutor].telefone.numero);

            cleanInputBuffer();
            printf("\nData de Nacimento: ");
            scanf("%hu %hu %d", &condutores[cont_condutor].data_nascimento.dia, &condutores[cont_condutor].data_nascimento.mes, &condutores[cont_condutor].data_nascimento.ano);


            /*Inicia a matriz com os valor a 0 e com espaÃ§o*/
            for (ml = 0; ml < LINHA; ml++) {
                for (mc = 0; mc < COLUNA; mc++) {
                    condutores[cont_condutor].agenda[ml][mc].id = 0;
                    strncpy(condutores[cont_condutor].agenda[ml][mc].nome, "_", NOME);
                }
            }
            cont_condutor++;
            ordenarCondutor(0, cont_condutor - 1, condutores);
        }
    }
    return cont_condutor;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////*funÃ§Ã£o para saber se o vector dos instrutores estÃ¡ vazio*////////////////////

int estaVazioVectorCondutor(unsigned int cont_condutor) {
    return (cont_condutor == 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////*funcao que vai remover os instrutores*///////////////////////////////////////////

unsigned int removerCondutor(condutor condutores[], const short TAMINSTRUTORES,
        int cont_condutor) {
    int x, i, z;

    if (estaVazioVectorCondutor(cont_condutor)) {
        printf("\nNao existem condutores para remover!\n");
    } else {

        printf("\nIntroduza o numero do condutor: ");
        x = scanf("%i", &condutores[cont_condutor].numero_condutor);

        i = pesquisarInstrutor(x, instrutores, cont_instrutor);

        if (i == -1) {
            printf("\nESSE CONDUTOR NAO EXISTE\n");
        } else {
            for (z = i; z < cont_condutor; z++) {
                condutores[z] = condutores[z + 1];
            }
            cont_condutor--;

        }
        return cont_condutor;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* funcao que vai listar os instrutores*///////////////////////////

void listarCondutor(condutor condutores[], const short TAMCONDUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_condutor, int cont_agenda) {
    int i;

    if (cont_condutor == 0)
        printf("\nNao existem condutores para listar\n");
    else {
        for (i = 0; i < cont_condutor; i++) {
            printf("\n<---------------------------------->\n");
            printf("\nNumero do Condutor: %ld", condutores[i].numero_condutor);
            printf("\nNome do Condutor: %s", condutores[i].nome);
            printf("\nTelefone: %hu-%d", /*instrutores[i].telefone.prefixo,*/ condutores[i].telefone.indicativo, condutores[i].telefone.numero);
            printf("\nData de Nascimento: %hu/%hu/%d", condutores[i].data_nascimento.dia, condutores[i].data_nascimento.mes, condutores[i].data_nascimento.ano);
        }
        printf("\n<---------------------------------->\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////* funcao que vai alterar os instrutores*/////////////////////////////

void alterarCondutor(condutor condutores[], const short TAMCONDUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_condutor, int cont_agenda) {
    int x, i, a;

    if (cont_condutor == 0) {
        printf("\nNao existem condutores para alterar\n");
    } else {

        printf("\nIntroduza o numero do condutor: ");
        x = scanf("%i", &condutores[cont_condutor].numero_condutor);

        i = pesquisarCondutor(x, condutores, cont_condutor);
        if (i == -1) {
            printf("\nNao existe o numero introduzido!\n");
        } else {

            printf("\nNumero do Condutor?: ");
            scanf("%ld", &x);
            a = pesquisarCondutor(x, condutores, cont_condutor);
            if (a != -1) {
                printf("\nESSE NUMERO JA EXISTE!\n");
            } else {
                condutores[i].numero_condutor = x;
                cleanInputBuffer();
                readString(condutores[cont_condutor].nome, NOME, "\n\tNome do Condutor: ");

                cleanInputBuffer();
                printf("\ntelefone [XXX XXXXXX]: ");
                scanf("%hu %d", &condutores[cont_condutor].telefone.indicativo, &condutores[cont_condutor].telefone.numero);

                cleanInputBuffer();
                printf("\nData de Nacimento: ");
                scanf("%hu %hu %d", &condutores[cont_condutor].data_nascimento.dia, &condutores[cont_condutor].data_nascimento.mes, &condutores[cont_condutor].data_nascimento.ano);

                ordenarCondutor(0, cont_condutor - 1, condutores);

            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////* funcao responsavel pelo menu dos alunos */////////////////////////

unsigned int menuViagem(viagem viagens[], const short TAMVIAGENS, agendas agenda[], const short TAMAGENDA,
        int cont_viagem, int cont_agenda) { //Argumentos
    int optn;
    do {
        do {
            printf("\n__________________________________________\n");
            printf("\n------------------Viagens------------------\n");
            printf("1----> Criar Viagem\n");
            printf("2----> Remover Viagem\n");
            printf("3----> Listar Viagem\n");
            printf("4----> Alterar Viagem\n");
            printf("5----> Voltar Atras\n");
            printf("__________________________________________\nIntroduza a opcao: ");
            scanf("%d", &optn);
        } while ((optn < 1) || (optn > 5));

        switch (optn) {
            case 1: cont_viagem = criarViagem(viagens, TAMVIAGENS, agenda, TAMAGENDA, cont_viagem, cont_agenda);
                break;

            case 2: cont_viagem = removerViagem(viagens, TAMVIAGENS, cont_viagem);
                break;

            case 3: listarViagem(viagens, cont_viagem);
                break;

            case 4: alterarViagem(viagens, cont_viagem);
                break;

            case 5:
                break;
        }
    } while (optn != 5);

    return cont_viagem;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////* funcao responsavel pelo menu dos instrutores *///////////////////

unsigned int menuCondutor(condutor condutores[], const short TAMCONDUTORES,
        agendas agenda[], const short TAMAGENDA, int cont_condutor, int cont_agenda) {

    int optn;
    do {
        do {
            printf("\n__________________________________________\n");
            printf("\n----------------Condutores---------------\n");
            printf("1----> Criar Condutor\n");
            printf("2----> Remover Condutor\n");
            printf("3----> Listar Condutor\n");
            printf("4----> Alterar Condutor\n");
            printf("5----> Voltar Atras\n");
            printf("__________________________________________\nIntroduza a opcao: ");
            scanf("%d", &optn);
        } while ((optn < 1) || (optn > 5));

        switch (optn) {
            case 1: cont_condutor = criarCondutor(condutores, TAMCONDUTORES, agenda, TAMAGENDA, cont_condutor);
                break;

            case 2: cont_condutor = removerCondutor(condutores, TAMCONDUTORES, cont_condutor);
                break;

            case 3: listarCondutor(condutores, TAMCONDUTORES, agenda, TAMAGENDA, cont_condutor, cont_agenda);
                break;

            case 4: alterarCondutor(condutores, TAMCONDUTORES, agenda, TAMAGENDA, cont_condutor, cont_agenda);
                break;

            case 5:
                break;
        }
    } while (optn != 5);
    return cont_condutor;
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
            if (mc == 5 && y < 17) {
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