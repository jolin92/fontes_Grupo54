/* 
 * File:   Alunos.h
 * Author: Antonio Santana &Bruno Oliveira
 *
 * Created on 28 de Dezembro de 2015, 10:29
 */

#define TAM 20
#define SIZE 15
#define NOME 50
#define LINHA 9
#define COLUNA 6

typedef enum {B = 1, C, L}conforto;
typedef enum {SIM = 1, NAO = 0}booleano;

typedef struct {
    unsigned short int dia;
    unsigned short int mes; 
    unsigned int ano;
} data;
typedef struct {
    unsigned short int hora;
    unsigned short int min;     
} hora;
typedef struct {
    //char prefixo[4];
    unsigned short int indicativo;
    unsigned int numero;
} phone;

typedef struct {
    char rua[TAM];
    short int nporta;
    char cod_postal[SIZE];
    char localidade[TAM];
}address;

typedef struct {
    unsigned long int id;
    char nome[NOME];
}agendas;

typedef struct Viagens {
    unsigned long int id;
    char l_inicio[NOME];
    char l_destino[NOME];
    data data_saida;
    hora hora_saida;
    unsigned long int lug_disp;
    conforto t_conforto;             
    float custo;
    booleano revalidacoes; 
    agendas agenda [LINHA][COLUNA];
}viagem;

typedef struct Condutores {
    unsigned long int numero_condutor;
    char nome[NOME];
    phone telefone;
    data data_nascimento;
    agendas agenda [LINHA][COLUNA];
}condutor;

