#include <stdlib.h>
#include <stdio.h>

char** mapa;
int linhas;
int colunas;

int main(){
    FILE* f;
    f = fopen("mapa.txt", "r");
    if(f == 0){
        printf("Erro na leitura\n");
        exit(1);
    }
    //
    fscanf(f, "%d %d", &linhas, &colunas);

    mapa = malloc(sizeof(char*) * linhas);
    for(int i = 0; i < linhas; i++){
        mapa[i] = malloc(sizeof(char) * colunas + 1);
    }
    //

    for(int i = 0; i < linhas; i++){
        fscanf(f, "%s", mapa[i]);
    }

    for(int i = 0; i < linhas; i++){
        printf("%s\n", mapa[i]);
    }

    fclose(f);
    for(int i = 0; i < linhas; i++){
        free(mapa[i]);
    }
    free(mapa);
}