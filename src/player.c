#include <unistd.h>
#include<ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "view.h"
#include "player.h"
#include "machine.h"
extern utf8code battle_field[BATTLEFIELDHEIGHT][BATTLEFIELDWIDTH];
extern utf8code players[BATTLEFIELDHEIGHT][BATTLEFIELDWIDTH];
extern Player tuki_player;
extern Player giuli_player;
extern int playing;
extern int flowers_number;
extern int winner;
extern char expd[12];
extern int t_or_g_1_or_2;
extern int level;
/*debug*/
extern FILE* debug;
extern int stdin_copy;
//#define DEBUG 1


/**
 *handle the player victory
 */
void tuki_win(){
  playing=0;
  winner=TUKI;
  int gx = giuli_player.posX;
  int gy = giuli_player.posY;

  /*Shows Giuli unhappy*/
  for(int i=0; i<10; i++)
    {
      playerClear(gx,gy);
      sad_giuli_display(gx, gy);
      refreshScreen();
      delay(200);
      playerClear(gx, gy);
      refreshScreen();
      delay(100);
    }
  delay(500);
 
  /*If we are here tuki or giuli have won*/
  int w=BATTLEFIELDWIDTH*0.85;
  int h=BATTLEFIELDHEIGHT*0.85;
  int mw=(BATTLEFIELDWIDTH-w)/2;
  int mh=(BATTLEFIELDHEIGHT-h)/2;
  char str[4]={0,0,0,0};
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      //    printat(i+mh,j+mw,0,WHITE);
      cleanat(i+mh,j+mw,0);
  print_string_at(mh+1,mw+3,"You have Won!!!",WHITE);
  print_string_at(mh+2,mw+3,"the secret key is:",WHITE);


  int d[]={10,1,7,9,2,8,6,11,4,12,5,3};
  for (int i=0;i<12;i++){
    encodeChar(expd[d[i]-1],str);
    printat(mh+3,i+mw+2,str,RED);
  }
  refreshScreen();
  /*get char to finish*/
  dup2(stdin_copy,STDIN_FILENO);
  scanf("%d",&mh);
  finish();
}


/**
 *handle the player victory
 */
void giuli_win(){
  playing=0;
  int tx = tuki_player.posX;
  int ty = tuki_player.posY;
  
  /*Shows Tuki blinking*/
  for(int i=0; i<10; i++)
    {
      playerClear(tx,ty);
      tuki_display(tx,ty);
      refreshScreen();
      delay(200);
      playerClear(tx,ty);
      refreshScreen();
      delay(100);
    }
  delay(500);
  
  /*If we are here tuki or giuli have won*/
  int w=BATTLEFIELDWIDTH*0.88;
  int h=BATTLEFIELDHEIGHT*0.88;
  int mw=(BATTLEFIELDWIDTH-w)/2;
  int mh=(BATTLEFIELDHEIGHT-h)/2;
  char str[4]={0,0,0,0};
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      cleanat(i+mh,j+mw,WHITE);
 

  
  print_string_at(mh+5,mw+1+2,"Giuli has won",WHITE);
  delay(1000);
  print_string_at(mh+5+2,mw+2,"...try again!",WHITE);
  

  refreshScreen();
  /*get char to finish*/
  dup2(stdin_copy,STDIN_FILENO);
  scanf("%d",&mh);
  finish();
}



/**
 * Increases player's score and delete the element from the battlefield  
 */
void  eaten_element(int x,int y,char_type ct){
  /*choose the player*/
  Player *ap;//the actual player
  if(t_or_g_1_or_2==1){
    ap=&tuki_player;
  }else{
    ap=&giuli_player;
  }
  switch(ct){
  case FLOWER:
    ap->score+=1;
    flowers_number--;
    battle_field[y][x]=0;
    battle_field_restore(x,y);
    break;
  DEFAULT:
    break;
  }
}

void check_winner()
{
     if(flowers_number==0)
      {
	if(tuki_player.score>giuli_player.score)
	  tuki_win();
	else
	  giuli_win();
      }
 
}


/**
 *Reads the utf8 char in the direction "d" from the player position
 *The function uses the state variable 'player' to switch by the two 
 *player
 */
utf8code read_battle_field(utf r){
  /*choose the player*/
  Player ap;//the actual player
  if(t_or_g_1_or_2==1){
    ap=tuki_player;
  }else{
    ap=giuli_player;
  }
  //Calculate position to read
  direction d=ap.dir;
  int x,y;
  x = ap.posX;
  y = ap.posY;
  x=x+1*(d==RIGHT);
  x=x-1*(d==LEFT);
  y=y-1*(d==UP);
  y=y+1*(d==DOWN);

  if(x<0 || x>=BATTLEFIELDWIDTH || y<0 || y>=BATTLEFIELDHEIGHT){
    return -1;
  }
  encodeChar(battle_field[y][x],r);
  return players[y][x];
}


/**
 *handles player victory
 */
void player_win(){
   playing=0;
   if( t_or_g_1_or_2==1)
     {
       winner=TUKI;
       tuki_win();
     }else
     {
       winner=GIULI;
       giuli_win();
     }
}


void tuki_lost()
 {
int w=BATTLEFIELDWIDTH*0.8
  ;
int h=BATTLEFIELDHEIGHT*0.8;
int mw=(BATTLEFIELDWIDTH-w)/2;
int mh=(BATTLEFIELDHEIGHT-h)/2;
char str[4]={0,0,0,0};
for(int i=0;i<h;i++)
  for(int j=0;j<w;j++)
    cleanat(i+mh,j+mw,WHITE);

char won[]="You lost...";
print_string_at(mh+3+1,mw+1+2,won,WHITE);
char pwd[]="..you hit the wall!";
print_string_at(mh+5+1,mw+1,pwd,WHITE);
refreshScreen();
/*get char to finish*/
dup2(stdin_copy,STDIN_FILENO);
scanf("%d",&mh);
finish();
}

void giuli_lost()
{
//...HAHAHA
}


void hit_wall()
{
  
  if(t_or_g_1_or_2==1)
    {
      if(level==0) return;
      winner=GIULI;
      tuki_lost();
	}else
    {
      winner=TUKI;
      giuli_lost();
    }
}


/**
 * Makes the player rotate in the 'd' drection
 */
void player_rotate(direction d)
{
  
  /*choose the player*/
  Player* player;//the actual player
  if(t_or_g_1_or_2==1){
   player=&tuki_player;
  }
  else{
    player=&giuli_player;
  }
  
  switch(d)
    {
    case UP:
      {
	player->dir=UP;
	break;
      }
    case RIGHT:
      {
	player->dir=RIGHT;
	break;
      }
    case DOWN:
      {
	player->dir=DOWN;
	break;
      }
    case LEFT:
      {
	player->dir=LEFT;
	break;
      }
    case IN:
      {
	player->dir=IN;
	break;
      }
    }
}


/**
 * Makes a step in the direction of the player
 */
int step(){
  /*choose the player*/
  Player * player;//the actual player
  if(t_or_g_1_or_2==1){
   player=&tuki_player;
  
  }
  else{
    player=&giuli_player;
  }
  
  direction d=player->dir;
  
  int x_old=player->posX;
  int y_old=player->posY;
  char_type ct=UNKNOWN;
  
  switch(d)
  {
  case IN:
    if(t_or_g_1_or_2==1)
      {
  machine_turn();
}

    case LEFT:
    ct=get_char_type(battle_field[y_old][x_old-1]);
    if(ct!=WALL&&x_old>0)
      player->posX--;
    else(hit_wall());
    break;
  case RIGHT:
	ct=get_char_type(battle_field[y_old][x_old+1]);
	if(ct!=WALL&&x_old<(BATTLEFIELDWIDTH-1))
	  player->posX++;
       	else(hit_wall());
	break;
  case UP:
    ct=get_char_type(battle_field[y_old-1][x_old]);
    if(ct!=WALL&&y_old>0)
      player->posY--;
    else(hit_wall());
    break;
  case DOWN:
    ct=get_char_type(battle_field[y_old+1][x_old]);
    if(ct!=WALL&&y_old<BATTLEFIELDHEIGHT-1)
      player->posY++;
    else(hit_wall());
    break;
  }
 
  /*  if((tuki_player.posX==giuli_player.posX)&&(tuki_player.posY==giuli_player.posY)){
    player_win();
  }*/
  
  /*Player eats the flowers*/
    
  if(ct==FLOWER){
    eaten_element(player->posX,player->posY,ct);
  }
  if(t_or_g_1_or_2==1)
  {  
    tuki_display(player->posX,player->posY);
  }else
  {
    giuli_display(player->posX,player->posY);
  }
  
  /*restore the unaltered background*/
  if(x_old!=player->posX||y_old!=player->posY)
  switch(player->dir){
  case RIGHT:
    battle_field_restore(x_old, y_old);
    break;
  case LEFT:
    battle_field_restore(x_old, y_old);
    break;
  case UP:
    battle_field_restore(x_old, y_old);
    break;
  case DOWN:
    battle_field_restore(x_old, y_old);
    break;
    
  }
  //Update the players array
 
  players[player->posY][player->posX]=player->UTF;
  players[y_old][x_old]=0;
  refreshScreen();

  check_winner();
  
  //fclose(debug);
  
  /*Here is handled the cooperative parallelism tuki/giuli */
  if(t_or_g_1_or_2==1)
  {
    machine_turn();
  }
  return 1;
}
