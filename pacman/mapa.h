#ifndef _MAPA_H_
#define _MAPA_H_

#define HEROI '@'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define FANTASMA 'F'
#define PILULA 'P'

struct mapa {
	char** matriz;
	int linhas;
	int colunas; 
};

typedef struct mapa MAPA;

void aloca_mapa(MAPA* m);
void le_mapa(MAPA* m);
void libera_mapa(MAPA* m);

struct posicao {
	int x;
	int y;
};

typedef struct posicao POSICAO;

int encontra_mapa(MAPA* m, POSICAO* p, char c);

int e_valida(MAPA* m, int x, int y);
int e_parede(MAPA* m, int x, int y);
int e_personagem(MAPA* m, char personagem, int x, int y);

void anda_no_mapa(MAPA* m, int xorigem, int yorigem, 
	int xdestino, int ydestino);

void copia_mapa(MAPA* destino, MAPA* origem);

int pode_andar(MAPA* m, char personagem, int x, int y);

#endif