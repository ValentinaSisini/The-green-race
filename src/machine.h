#include "player.h"
#define DELAY 50
#define PRESDELAY 2000

typedef enum {UL, UR, DR,DL,FC} corner;
typedef struct  {
  int posX; // horizontal position of player
  int posY; // vertical position of player
  direction dir; //movement direction
  int score;
  char name[10];
  utf8code UTF;
 } Player;


typedef struct {
  int posX; // horizontal position of player
  int posY; // vertical position of player
  direction dir; //movement direction
} giuli_pres;


typedef struct {
  int posX; // horizontal position of player
  int posY; // vertical position of player
  direction dir; //movement direction
} tuki_pres;



void machine_turn();
void prepare_battle_field();
void presentation_turn();
void delay(int milliseconds);
