#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    printf("Bem vindo(a) ao jogo de adivinhação\n\n");

    int seed = time(0);
    srand(seed);

    int numero_secreto = rand() % 101;
    int chute;
    int tentativas;
    double pontos = 500;

    int nivel;
    printf("Escolha a dificuldade:\n");
    printf("(1) Fácil | (2) Médio | (3) Difícil\n");
    scanf("%d", &nivel);

    switch (nivel){
        case 1:
            tentativas = 15;
            break;
        case 2:
            tentativas = 10;
            break;
        default:
            tentativas = 5;
            break;
    }

    for(int i = 1; i <= tentativas; i++){
        printf("Tentativas: %d de %d\n", i, tentativas);
        printf("Qual é seu chute? ");
        scanf("%d", &chute);

        if(chute < 0){
            printf("Chute números positivos\n");
            i--;
            continue;
        }

        if(chute < numero_secreto){
            printf("Seu chute foi MENOR que o número secreto\n\n");
        }else if(chute > numero_secreto){
            printf("Seu chute foi MAIOR que o número secreto\n\n");
        }else{
            printf("Você acertou\n\n");
            break;
        }

        double pontos_perdidos = abs(chute - numero_secreto) / 2.0;
        pontos = pontos - pontos_perdidos;
    }
    printf("Sua pontuação: %.2f\n", pontos);
    printf("Fim de jogo!\n");
    return 0;
}