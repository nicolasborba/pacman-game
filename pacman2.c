#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pacman2.h"
#include "map2.h"
#include "ui.h"

MAP m;
POSITION hero;
int hasPill;


int whereDoesTheGhostGo(int xnow, int ynow, 
  int* xdestination, int* ydestination){
    
  int options[4][2] = {
    {xnow, ynow +1},
    {xnow, ynow -1},
    {xnow +1, ynow},
    {xnow -1, ynow}
  };

  srand(time(0));
  for(int i = 0; i < 10; i++){
    int position = rand() % 4;

    if(canWalk(&m, GHOST, options[position][0], options[position][1])){
      *xdestination = options[position][0];
      *ydestination = options[position][1];
      
      return 1;
    }
  }
  return 0;

}


void ghosts(){
  MAP copy;
  copyMap(&copy, &m);



  for(int i = 0; i < m.lines; i++){
    for(int j = 0; j < m.columns; j++){
      
      if(copy.matrix[i][j] == GHOST){

        int xdestination;
        int ydestination;


        int found = whereDoesTheGhostGo(i, j, &xdestination, &ydestination);

        if(found){
          walkOnMap(&m, i, j, xdestination, ydestination);
        }


      }
    }
  }
  freeMap(&copy);
}


int itsADirection(char direction){
  return direction == ESQUERDA ||
    direction == CIMA ||
    direction == BAIXO ||
    direction == DIREITA;
}



void move(char direction){

  if(!itsADirection(direction)){
      return;
    }

  

  
  int nextx = hero.x;
  int nexty = hero.y;


  //reposiciona pacman
  switch(direction){
    case ESQUERDA: 
      nexty--;
      break;
    case DIREITA:
      nexty++;
      break;
    case CIMA:
      nextx--;
      break;
    case BAIXO:
      nextx++;
      break;
  }

  // ja pega o itsValid e itsEmpty
  if(!canWalk(&m, HERO, nextx, nexty))
    return;

  if(itsCharacter(&m, PILL, nextx, nexty)){
    hasPill = 1;
  }


  
  walkOnMap(&m, hero.x, hero.y, nextx, nexty);
  
  hero.x = nextx;
  hero.y = nexty;


}


int over(){
  POSITION pos;
  int pacmanAlive = findMap(&m, &pos, HERO);
  return !pacmanAlive;
}

void explodePill(){
  explodePill2(hero.x, hero.y, 0, 1, 3);
  explodePill2(hero.x, hero.y, 0, -1, 3);
  explodePill2(hero.x, hero.y, 1, 0, 3);
  explodePill2(hero.x, hero.y, -1, 0, 3);
}


void explodePill2(int x, int y, int somax, int somay, int qtd){

  if(qtd == 0) return;

  
  int newx = x + somax;
  int newy = y + somay;

  if(!itsValid(&m, newx, newy)) return;
  if(itsWall(&m, newx, newy)) return;



  m.matrix[newx][newy] = EMPTY;
  explodePill2(newx, newy, somax, somay, qtd - 1);


}



int main(){




  readMap(&m);
  findMap(&m, &hero, HERO);


  do{

    printf("Tem pilula: %s\n", (hasPill ? "SIM" : "NAO"));

  // imprime o mapa
  
    printMap(&m);

    char command;
    scanf(" %c", &command);
    move(command);
    
    if(command == BOMB) explodePill();


    ghosts();




  }while(!over());

  //libera memória
  
  freeMap(&m);





}