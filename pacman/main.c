#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "main.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;

int tem_pilula = 0;

int acabou() {
	POSICAO pos;

	int perdeu = !encontra_mapa(&m, &pos, HEROI);
	int ganhou = !encontra_mapa(&m, &pos, FANTASMA);

	return ganhou || perdeu;
}

int e_direcao(char direcao) {
	return
		direcao == ESQUERDA || 
		direcao == CIMA ||
		direcao == BAIXO ||
		direcao == DIREITA;
}

void move(char direcao) {

	int proximox = heroi.x;
	int proximoy = heroi.y;

	switch(direcao) {
		case ESQUERDA:
			proximoy--;
			break;
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case DIREITA:
			proximoy++;
			break;
	}

	if(!pode_andar(&m, HEROI, proximox, proximoy))
		return;

	if(e_personagem(&m, PILULA, proximox, proximoy)) {
		tem_pilula=1;
	}

	anda_no_mapa(&m, heroi.x, heroi.y, proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;
}

int onde_fantasma_vai(int xatual, int yatual, 
	int* xdestino, int* ydestino) {

	int opcoes[4][2] = { 
		{ xatual   , yatual+1 }, 
		{ xatual+1 , yatual   },  
		{ xatual   , yatual-1 }, 
		{ xatual-1 , yatual   }
	};

	srand(time(0));
	for(int i = 0; i < 10; i++) {
		int posicao = rand() % 4;

		if(pode_andar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];
			return 1;
		}
	}

	return 0;
}

void fantasmas() {
	MAPA copia;

	copia_mapa(&copia, &m);

	for(int i = 0; i < copia.linhas; i++) {
		for(int j = 0; j < copia.colunas; j++) {
			if(copia.matriz[i][j] == FANTASMA) {

				int xdestino;
				int ydestino;

				int encontrou = onde_fantasma_vai(i, j, &xdestino, &ydestino);

				if(encontrou) {
					anda_no_mapa(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}

	libera_mapa(&copia);
}

void explode_pilula2(int x, int y, int somax, int somay, int qtd) {

	if(qtd == 0) return;

	int novox = x+somax;
	int novoy = y+somay;

	if(!e_valida(&m, novox, novoy)) return;
	if(e_parede(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = VAZIO;
	explode_pilula2(novox, novoy, somax, somay, qtd-1);
}

void explode_pilula() {
	if(!tem_pilula) return;
	
	explode_pilula2(heroi.x, heroi.y, 0, 1, 3);
	explode_pilula2(heroi.x, heroi.y, 0, -1, 3);
	explode_pilula2(heroi.x, heroi.y, 1, 0, 3);
	explode_pilula2(heroi.x, heroi.y, -1, 0, 3);
	
	tem_pilula = 0;
}

int main() {
	
	le_mapa(&m);
	encontra_mapa(&m, &heroi, HEROI);

	do {
		printf("Pílula: %s\n", (tem_pilula ? "SIM" : "NÃO"));
		imprime_mapa(&m);

		char comando;
		scanf(" %c", &comando);

		if(e_direcao(comando)) move(comando);
		if(comando == BOMBA) explode_pilula();

		fantasmas();

	} while (!acabou());

	libera_mapa(&m);
}