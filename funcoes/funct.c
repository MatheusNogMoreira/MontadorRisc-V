#include "funct.h"
void PrintarArquivo(char*nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    char c;
    if (file) {
        while ((c = fgetc(file)) != EOF) {
            printf("%c", c);
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo!\n");
    }
}
int OpcaoLeitura(FILE **fp, FILE **fpS) {
    char nomeArquivo[15], nomeArquivoSaida[15];
    int resposta, tamanho = 0;
    printf("\n\t\t\t  Montador\n");
    printf("\t----------------------------------\n");
    printf("\t| Digite a opçao desejada:       |\n");
    printf("\t| [1] ==> Leitura de um arquivo  |\n");
    printf("\t|         ja existente.          |\n");
    printf("\t| [2] ==> Digitar o conteudo     |\n");
    printf("\t|         via teclado.           |\n");
    printf("\t----------------------------------\n");
    scanf("%d", &resposta);
    if (resposta == 1) {
        printf("\tDigite o nome do arquivo:");
        scanf("%s", nomeArquivo);
        *fp = fopen(nomeArquivo, "r");
        if (*fp == NULL) {
            printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
            exit(1);
        }
        printf("\tAs instrucoes em binário serao salvas em saida.bin.\n");
        *fpS = fopen("saida.bin","w");
        return 1;
    } else if (resposta == 2) {
        printf("\tInsira o comando:\nExemplo:./binario_programa entrada.asm -o saida\n");
        char input[50],var1[10],var2[10];
        scanf(" %[^\n]", input); // lê a entrada completa até a quebra de linha
        sscanf(input, "%s %s %s %s",var1,nomeArquivo,var2, nomeArquivoSaida); 
        // separa as informações necessárias
        memset(var1, 0, sizeof(var1));
        memset(var1, 0, sizeof(var2));
        // abre os arquivos de entrada e saída
        *fp = fopen(nomeArquivo, "w");
        if (*fp == NULL) {
            printf("Erro ao criar o arquivo %s\n", nomeArquivo);
            exit(1);
        }
        *fpS = fopen(nomeArquivoSaida, "w");
        if (*fpS == NULL) {
            printf("Erro ao criar o arquivo %s\n", nomeArquivoSaida);
            exit(1);
        }
        printf("\tDigite as Instrucoes: \n");
        char ViaTeclado;
        while((ViaTeclado=getchar())!=EOF){
            putc(ViaTeclado,*fp);
        }
        fclose(*fp);
        *fp = fopen(nomeArquivo,"r");
        return 2;
    } else {
        printf("\nOpcao Invalida!\n");
        exit(1);
    }
}

//Converte o Imediato de instruções para binário,valores negativos e positivos
char* converteImediato(char *variavel){
    int decimal,rI,aux = 0, negativo = 0;
    char *vetor_binario;
    vetor_binario = (char*)malloc(sizeof(char)*12);
    //imediato será retornado com 12 bits
    decimal = atoi(variavel);

    if(decimal < 0) {
        // número é negativo, aplicar complemento de dois
        decimal = abs(decimal); // obtém o valor absoluto do número
        decimal = ~decimal + 1; // inverte todos os bits e adiciona 1
        negativo = 1;
    }
    for(int i = 11;i>=0;i--){
        rI = decimal>>i;
        if((rI&1)){
            vetor_binario[aux] = '1';
        }else{
            vetor_binario[aux] = '0';
        }
        aux+=1;
    }
    if(negativo) {
        // adiciona o bit de sinal (1 para negativo)
        vetor_binario[0] = '1';
    }
    vetor_binario[12] = '\0';
    return vetor_binario;
}
//Remove o 'x' dos registradores
char* remover_caractere(char *p){
    memmove(p,p+1,strlen(p));
    return p;
}
//Conta as linhas do arquivo
int contagem_linhas(FILE *fp){
    char contagem;
    int linhas = 1;
    while((contagem=fgetc(fp))!=EOF){
        if(contagem=='\n'){
            linhas +=1;
        }
    }
    fseek(fp,0,SEEK_SET);
    return linhas;
}
char* Rs_converte(char *variavel){
    //Para Tipo R
    //essa função será responsável para converter os valores para binário de rs1,rd,rs2;
    int decimal,rI,aux = 0;
    char *vetor_binario;
    vetor_binario = (char*)malloc(sizeof(char)*5);
    //número retornado é 5 bits
    //o parâmetro terá formato de um registor,ou seja,x3,a posição [1] da string
    //será o valor para ser convertido para binário.
    decimal = atoi(variavel);
    
    for(int i = 4; i >= 0; i--) {
        rI =  decimal>>i;
    if((rI & 1)) {
        vetor_binario[aux] = '1';
    } else {
        vetor_binario[aux] = '0';
    }aux+=1;
    }
    vetor_binario[5] = '\0';
    return vetor_binario;
}

char* desloca_bit_direita(char *binario){
    int len = strlen(binario);
    char *novo_binario = (char*) malloc((len + 1) * sizeof(char));
    novo_binario[len] = '\0';
    novo_binario[0] = '0';
    for (int i = 1; i < len; i++) {
        novo_binario[i] = binario[i-1];
    }
    return novo_binario;
}
void escreve_saidaB(FILE* fpS, char** MatrizBinario, char* funct3, char* opcode){
    int aux = 2;
    
    //bit 12 do imediato
    fputc(MatrizBinario[aux][0],fpS);
    for(int i = 2;i<=6;i++){
        fputc(MatrizBinario[aux][i],fpS);
    }
    fprintf(fpS,MatrizBinario[aux-1]);
    fprintf(fpS,MatrizBinario[aux-2]);
    fprintf(fpS,funct3);
    for(int i = 7;i<=11;i++){
        fputc(MatrizBinario[aux][i],fpS);
    }
    //Bit 11 do imediato
    fputc(MatrizBinario[aux][1],fpS);
    fprintf(fpS,opcode);
    
    fputc('\n',fpS);  
}
void escreve_saida(FILE* fpS, char** MatrizBinario, char* funct3, char* opcode) {
    fprintf(fpS, MatrizBinario[2]);
    fprintf(fpS, MatrizBinario[1]);
    fprintf(fpS, funct3);
    fprintf(fpS, MatrizBinario[0]);
    fprintf(fpS, opcode);
    fprintf(fpS, "\n");
}
void TipoR(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *funct7,char *opcode) {
    int aux = -1;
    while (p != NULL) {
        if (aux == -1) {
            fprintf(fpS, funct7);
            //funct 7 Tipo R
        } else {
            p = remover_caractere(p);
            //elimina a primeira posição de p,no caso x
            char* valor = Rs_converte(p);
            if (aux == 0) {
                //armazena rd
                MatrizBinario[aux] = valor;
            } else if (aux == 1) {
                //armazena rs1
                MatrizBinario[aux] = valor;
            } else if (aux == 2) {
                //armazena rs2
                MatrizBinario[aux] = valor;
                escreve_saida(fpS, MatrizBinario, funct3, opcode);
                return;
            }
        }
        aux += 1;
        p = strtok(NULL, " ,");
    }
}

void TipoI(char* p, FILE* fpS, char** MatrizBinario, char* funct3, char* opcode) {
    int aux = 0;
    p = strtok(NULL, " ,");
    //avança na string
    while (p != NULL) {
        if (aux == 0) {
            //recebe rd
            p = remover_caractere(p);
            MatrizBinario[aux] = Rs_converte(p);
        } else if (aux == 1) {
            //recebe rs1
            p = remover_caractere(p);
            MatrizBinario[aux] = Rs_converte(p);
        } else if (aux == 2) {
            //recebe imediato
            MatrizBinario[aux] = converteImediato(p);
            escreve_saida(fpS, MatrizBinario, funct3, opcode);
            return;
        }
        aux += 1;
        p = strtok(NULL, " ,");
    }
}
void TipoILw(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *opcode){
    int aux = 0;
    p = strtok(NULL," ,()");
    while(p!=NULL){
        if(aux==0){
            p = remover_caractere(p);
            MatrizBinario[aux] = Rs_converte(p);
        }else if(aux==1){
            MatrizBinario[aux+1] = converteImediato(p);
        }else if(aux==2){
    
            p = remover_caractere(p);
            MatrizBinario[aux-1] = Rs_converte(p);
           
            escreve_saida(fpS,MatrizBinario,funct3,opcode);
        }
        aux+=1;
        p = strtok(NULL," ,()");
    }
}
void TipoB(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *opcode){
    int aux = 0;
    p = strtok(NULL," ,");
    while(p!=NULL){
        if(aux==0){
            p = remover_caractere(p);
            MatrizBinario[aux] = Rs_converte(p);
        }else if(aux==1){
            p = remover_caractere(p);
            MatrizBinario[aux] = Rs_converte(p);
        }else if(aux==2){
            if(p[0]=='x'){
                p = remover_caractere(p);
                p = converteImediato(p);
                MatrizBinario[aux] = desloca_bit_direita(p);
            }else{
                p = converteImediato(p);
                MatrizBinario[aux] = desloca_bit_direita(p);
            }
            escreve_saidaB(fpS,MatrizBinario,funct3,opcode);
            
        }
        aux +=1;
        p = strtok(NULL," ,");
    }


}
void TipoISw(char *p,FILE *fpS,char **MatrizBinario,char *funct3,char *opcode){
    int aux = 0;
    p = strtok(NULL," ,()");
    while(p!=NULL){
        if(aux==0){
            p = remover_caractere(p);
            MatrizBinario[aux] = Rs_converte(p);
        }else if(aux==1){
            MatrizBinario[aux+1] = converteImediato(p);
        }else if(aux==2){
    
            p = remover_caractere(p);
            MatrizBinario[aux-1] = Rs_converte(p);
           
            escreve_saidaSw(fpS,MatrizBinario,funct3,opcode);
        }
        aux+=1;
        p = strtok(NULL," ,()");
    }

}

void escreve_saidaSw(FILE* fpS, char** MatrizBinario, char* funct3, char* opcode){
        int aux = 2;
        for(int i = 0;i<=6;i++){
            fputc(MatrizBinario[aux][i],fpS);
        }
        printf("\n");
        fprintf(fpS,MatrizBinario[aux-2]);
        fprintf(fpS,MatrizBinario[aux-1]);
        fprintf(fpS,funct3);
        for(int i = 7;i<=11;i++){
            fputc(MatrizBinario[aux][i],fpS);
        }
        fprintf(fpS,opcode);
        fprintf(fpS,"\n");

}

void auxmain(FILE* fpS,char** MatrizBinario,char *p){
    if (!(strcmp(p, "add"))) {
            TipoR(p, fpS, MatrizBinario, "000","0000000","0110011");
        } else if(!(strcmp(p, "and"))){
            TipoR(p, fpS, MatrizBinario, "111","0000000","0110011");
        }else if(!(strcmp(p, "sub"))){
            TipoR(p, fpS, MatrizBinario, "000","0100000","0110011");
        }else if (!(strcmp(p, "xor"))) {
            TipoR(p, fpS, MatrizBinario, "100","0000000","0110011");
        }else if(!(strcmp(p, "or"))){
            TipoR(p, fpS, MatrizBinario, "110","0000000","0110011");
        }else if (!(strcmp(p, "sll"))) {
            TipoR(p, fpS, MatrizBinario, "001","0000000","0110011");
        }else if(!(strcmp(p, "srl"))){
            TipoR(p, fpS, MatrizBinario, "101","0000000","0110011");
        } else if (!(strcmp(p, "addi"))) {
            TipoI(p, fpS, MatrizBinario, "000", "0010011");
        }else if(!(strcmp(p, "andi"))){
            TipoI(p, fpS, MatrizBinario, "111", "0010011");
        }else if(!(strcmp(p, "ori"))){
            TipoI(p, fpS, MatrizBinario, "110", "0010011");
        } else if (!(strcmp(p, "lw"))) {
            TipoILw(p, fpS, MatrizBinario, "010", "0000011");
        }else if(!(strcmp(p, "lb"))){
            TipoILw(p, fpS, MatrizBinario, "000", "0000011");
        }else if(!(strcmp(p, "lh"))){
            TipoILw(p, fpS, MatrizBinario, "001", "0000011");
        }else if (!(strcmp(p, "sw"))) {
            TipoISw(p, fpS, MatrizBinario, "010", "0100011");
        }else if(!(strcmp(p, "sb"))){
            TipoISw(p, fpS, MatrizBinario, "000", "0100011");
        }else if(!(strcmp(p, "sh"))){
            TipoISw(p, fpS, MatrizBinario, "010,", "0100011");
        }else if(!(strcmp(p,"bne"))){
            TipoB(p,fpS,MatrizBinario,"001","1100011");
        }else if(!(strcmp(p,"beq"))){
            TipoB(p,fpS,MatrizBinario,"000","1100011");

        }
}