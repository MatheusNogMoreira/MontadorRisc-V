#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
//Pergunta ao usuário se deseja ler um arquivo já existente ou se quer digitar as instruções via teclado
int OpcaoLeitura(FILE **fp,FILE **fpS);

void comandoentrada(FILE **fp,FILE **fpS);

//Para todas as funções,remove o primeiro caractere do registrador,ou seja,o 'x'
char* remover_caractere(char *p);

//Utilizado logo após o remover_caractere,converte o resto da string para inteiro
char* Rs_converte(char *variavel);

//Função Utilizada para Funções Tipo I e do Tipo Sb,converte o número inteiro da instrução para forma binária 12 bits
char* converteImediato(char *variavel);

//Conta as linhas de Fp,ajuda no armazenamento do conteúdo do arquivo
int contagem_linhas(FILE *fp);

//Printar o contéudo do arquivo
void PrintarArquivo(char*nomeArquivo);

//Desloca apenas um bit para a direita,utilizado exclusivamente para a conversão dos tipos Sb
char* desloca_bit_direita(char *binario);

//Utilizada para instruções tipo R,separa as partes de acordo com a ordem do formato
void TipoR(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *funct7,char *opcode);

//Utilizada para instruções tipo I,separa as partes de acordo com a ordem do formato
void TipoI(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *opcode);

//Utilizada especificamente para instruções tipo Load e Store,já que apresentam uma gráfia diferente
void TipoILw(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *opcode);

void TipoISw(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *opcode);
//Utilizada para beq,bne,Tipos Sb
void TipoB(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *opcode);

//Utilizado para escrever no arquivo as instruções R,I,Lw em binário
void escreve_saida(FILE* fpS, char** MatrizBinario, char* funct3, char* opcode);
//Utilizado para escrever no arquivo as instruções de store em binário
void escreve_saidaSw(FILE* fpS, char** MatrizBinario, char* funct3, char* opcode);

//Utilizado para escrever no arquivo as instruções SB em binário
void escreve_saidaB(FILE* fpS, char** MatrizBinario, char* funct3, char* opcode);

void auxmain(FILE* fpS,char** MatrizBinario,char *p);
