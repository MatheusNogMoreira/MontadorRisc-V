#include "C:\Users\mathe\Documents\CC++\C\Proprios\Montador\Funcoes\funct.h"
int main(void) {
    setlocale(LC_ALL, "");
    //Declaração das variàveis.
    char **MatrizBinario, conteudo[25], *nomeArquivo, *p;
    FILE *fp, *fpS;
    int opcao;
    opcao = OpcaoLeitura(&fp,&fpS);
    MatrizBinario = (char **)malloc(contagem_linhas(fp) * sizeof(char *));
    for(int i = 0; i < contagem_linhas(fp); i++) {
        MatrizBinario[i] = (char*)malloc(sizeof(char)*3);
    }
    while (fgets(conteudo, 25, fp ? fp : stdin)) {
        p = strtok(conteudo, ", ");
        auxmain(fpS,MatrizBinario,p);
    }
    if(opcao==1){
        PrintarArquivo("saida.bin");
    }
    fclose(fp);
    fclose(fpS);
    return 0;
}