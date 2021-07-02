#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map2.h"
#include "ui.h"



int itsWall(MAP* m, int x, int y){
  return m->matrix[x][y] == VERTICAL_WALL ||
    m->matrix[x][y] == HORIZONTAL_WALL;
}

int itsCharacter(MAP* m, char character, int x, int y){
  return m->matrix[x][y] == character;
}



int canWalk(MAP* m, char character, int x, int y){
  return
    !itsWall(m, x, y) &&
    !itsCharacter(m, character, x, y) &&
    itsValid(m, x, y);
}







void copyMap(MAP* destination, MAP* origin){
  destination->lines = origin->lines;
  destination->columns = origin->columns;

  allocateMap(destination);
  for(int i = 0; i < origin->lines; i++){
    strcpy(destination->matrix[i], origin->matrix[i]);
  }


}



int itsEmpty(MAP* m, int x, int y){
  return m->matrix[x][y] == EMPTY;
}

void walkOnMap(MAP* m, int x, int y, 
  int nextx, int nexty){

  char character = m->matrix[x][y];
  m->matrix[nextx][nexty] = character;
  m->matrix[x][y] = EMPTY;
  

}




int itsValid(MAP* m, int x, int y){
  if(x >= m->lines)
    return 0;
  if(y >= m->columns)
    return 0;
  
  return 1;
}



int findMap(MAP* m, POSITION* p, char c){
  for(int i = 0; i < m->lines; i++){
    for(int j = 0; j < m->columns; j++){
      if(m->matrix[i][j] == c){
        p->x = i;
        p->y = j;
        return 1;

      }
    }
  }
  return 0;
}



void freeMap(MAP* m){
  for(int i = 0; i < m->lines; i++){
    free(m->matrix[i]);
  }
  free(m->matrix);
}


void allocateMap(MAP* m){

  m->matrix = malloc(sizeof(char*) * m->lines);
  for(int i = 0; i < m->lines; i++){
    m->matrix[i] = malloc(sizeof(char) * (m->columns+1));
  }



}



void readMap(MAP* m){
  FILE* f;
  f = fopen("map2.txt", "r");
  if(f == 0){
    printf("Desculpe, erro ao ler mapa.\n");
    exit(1);
  }

  fscanf(f, "%d %d", &(m->lines), &(m->columns));

  //aloca memória pro mapa

  allocateMap(m);
  

  // le o mapa

  for(int i = 0; i < m->lines; i++){

  
    fscanf(f, "%s", m->matrix[i]);
  }

  fclose(f);
}


