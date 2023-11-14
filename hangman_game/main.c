#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char palavra_secreta[30];
char chutes[26];
int tentativas = 0;

void abertura(){
    printf("**********************\n");
    printf("*   Jogo da Forca   *\n");
    printf("**********************\n\n");
}

void pega_chute(){
    char chute;
    scanf(" %c", &chute);

    chutes[tentativas] = chute;
    tentativas++;
}

int achou_na_palavra(char letra){
    int achou = 0;

    for(int j = 0; j < (tentativas); j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenha_forca(){
    for(int i = 0; i < strlen(palavra_secreta); i++){
        int achou = achou_na_palavra(palavra_secreta[i]);
        
        if(achou){
            printf("%c ", palavra_secreta[i]);
        }else{
            printf("_ ");
        }
    }
    printf("\n");
}

void escolhe_palavra_secreta(){
    FILE* f;
    
    f = fopen("palavras.txt", "r");
    int quant_palavras;
    fscanf(f, "%d", &quant_palavras);

    srand(time(0));
    int random = rand() % quant_palavras;

    for(int i = 0; i <= random; i++){
        fscanf(f, "%s", palavra_secreta);
    }
    fclose(f);
}

int enforcou(){
    int erros = 0;
    for(int i = 0; i < tentativas; i++){
        int existe = 0;

        for(int j = 0; j < strlen(palavra_secreta); j++){
            if(chutes[i] == palavra_secreta[j]){
                existe = 1;
                break;
            }
        }

        if(!existe) erros++;
    }

    return erros >= 7;
}

int acertou(){
    for(int i = 0; i < strlen(palavra_secreta); i++){
        if(!achou_na_palavra(palavra_secreta[i])){
            return 0;
        }
    }
    
    return 1;
}

int main(){
    escolhe_palavra_secreta();
    abertura();

    do{
        desenha_forca();
        pega_chute();
        
    }while (!acertou() && !enforcou());

    if(acertou()){
        printf("Parabéns você ganhou!!!\n");
    }else{
        printf("Que pena colega\n");
    }
}