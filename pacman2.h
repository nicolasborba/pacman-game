#ifndef _PACMAN2_H_
#define _PACMAN2_H_

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMB 'b'


int over();
void move(char direction);

int itsADirection(char direction);
void ghosts();
int whereDoesTheGhostGo(int xnow, int ynow, 
  int* xdestination, int* ydestination);

void explodePill();

void explodePill2(int x, int y, int somax, int somay, int qtd);


#endif
