#ifndef _MAP2_H_
#define _MAP2_H_

#define HERO '@'
#define GHOST 'F'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'


struct map {
  char** matrix;
  int lines;
  int columns;
};



typedef struct map MAP;

struct position {
  int x;
  int y;
};

typedef struct position POSITION;


int findMap(MAP* m, POSITION* p, char c);



void freeMap(MAP* m);
void allocateMap(MAP* m);
void readMap(MAP* m);

int itsValid(MAP* m, int x, int y);

int itsEmpty(MAP* m, int x, int y);
void walkOnMap(MAP* m, int x, int y, 
  int nextx, int nexty);
void copyMap(MAP* destination, MAP* origin);


int canWalk(MAP* m, char character, int x, int y);

int itsWall(MAP* m, int x, int y);

int itsCharacter(MAP* m, char character, int x, int y);

#endif