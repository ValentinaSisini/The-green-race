#include "tuki_turn.h"
#include <stdio.h>
typedef enum {CRUISE, ESCAPING, CROSS,RUNAWAY} navigation;
typedef enum {CLOCKWISE, ANTICLOCKWISE} circuit;
typedef struct  {
  int posX; //horizontal position of player
  int posY; //vertical position of player
  int speed; //0: no movement; 1: one per turn; etc.
  direction dir; //direction of the motion
} Tuki;
typedef struct  {
  int posX; // horizontal position of player
  int posY; // vertical position of player
  int speed; // 0: no movement; 1: one per turn; etc.
  direction dir; //movement direction
  direction block_dir; //the direction that blocked the motion
  int steps; // the nomber of steps giuli has to do in a direction
  int eating; // flag 
  int score; // eaten elements
  navigation  nav_state; //indicates what giuli is doing
  circuit circ;
} Giuli;


extern Giuli giuli_player;
extern Giuli tuki_player;
extern FILE* debug;

void tuki_turn(){
  
  /*
  for(int j=0;j<500;j++){
     
    for(int i=0; i < 3; i++)
      {
	step(RIGHT);
      }
    for(int i=0; i < 8; i++)
      {
      step(DOWN);
      }
    for(int i=0; i < 12; i++)
      {
	step(LEFT);
      }
    for(int i=0; i < 6; i++)
      {
	step(UP);
      }
    for(int g=0;g<15;g++)
  */
    step(RIGHT);

    
    while(1){
      char r[4];
      int rd=read_battle_field(r);
      //fprintf(debug,"tuki_turn_c\txt=%d\tyt=%d\t;xb=%d\tyb=%d\t; read%d\n",tuki_player.posX,tuki_player.posY,giuli_player.posX,giuli_player.posY,rd);
       direction d;
      if(tuki_player.posX>giuli_player.posX) step(LEFT);
      if(tuki_player.posX<giuli_player.posX) step(RIGHT);
      if(tuki_player.posY>giuli_player.posY) step(UP);
      if(tuki_player.posY<giuli_player.posY) step(DOWN);
      
      if(rd==9787) {
	step(RIGHT);
      }
      else step (IN);
	 //if(rd==9752) step(RIGHT);else  step(DOWN);
    }



}







