#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h> 
#include <string.h>
#include "machine.h"

#include "view.h"

extern utf8code presentation[PREHEIGHT][PREWIDTH];
extern utf8code battle_field[BATTLEFIELDHEIGHT][BATTLEFIELDWIDTH];
extern utf8code players[BATTLEFIELDHEIGHT][BATTLEFIELDWIDTH];

extern int stdin_copy;
extern int playing;
extern Player giuli_player;
extern Player tuki_player;

extern giuli_pres g_pres;
extern tuki_pres t_pres;
extern int giuli_color;
extern int flowers_number;
extern int t_or_g_1_or_2;
extern int level;
/**/
extern FILE* debug;
#define DEBUG

void giuli_turn();
void tuki_turn();

/*
 *Prepares the presentation array to be printed in the presentation
 *window
 */
void prepare_presentation(){
  int i;
  int h=PREHEIGHT;
  int w=PREWIDTH;
  
  /*
   *maze borders
   */
  
  /*fills the field with flowers*/
  int c=10;
  srand(time(NULL));
  for(int i=10;i<h-10;i+=1)
    for(int j=10;j<w-10;j+=3){
	  presentation[i][j]=FUTF;
    }
  

  /*upper left-hand corner*/
  presentation[0][0]=TLC;

  /*upper wall*/
  for(int j=1;j<PREWIDTH-1;j++)
    {
      presentation[0][j]=HLN;
    }

  /*upper right-hand corner*/
  presentation[0][PREWIDTH-1]=TRC;

  /*right wall*/
  for(i=1;i<PREHEIGHT-1;i++)
    {
      presentation[i][PREWIDTH-1]=VLN;
      
    }
  /*lower right-hand corner*/
  presentation[PREHEIGHT-1][PREWIDTH-1]=BRC;
  /*lower wall*/
  for(i=PREWIDTH-2;i>0;i--)
    {
      presentation[PREHEIGHT-1][i]=HLN;
}
  
  /*lower left-hand corner*/
  presentation[PREHEIGHT-1][0]=BLC;
    
    /*left wall*/
    for(i=PREHEIGHT-2;i>0;i--)
  {
  	presentation[i][0]=VLN;	
    }

}



/*
 *Handles the game presentation to the user 
 */
void presentation_turn()
{
  //prepare_presentation();
  
  /*credits*/
    int w=PREWIDTH*0.8;
  int h=PREHEIGHT*0.8;
  int mw=(PREWIDTH-w)/2;
  int mh=(PREHEIGHT-h)/2;
  char str[4]={0,0,0,0};
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      print_pres(i+mh,j+mw,0,WHITE);

  char one[]="La Scuola Sisini:";
  for (int i=0;i<18;i++)
    {
      
      encodeChar(one[i],str);
      print_pres(mh+1,i+mw+8,str,WHITE);
    }
  refresh_presentation();
  delay(1000);
  
  char caz[]="facebook.com/MatematicaFisicaSisini";
  for (int i=0;i<strlen(caz);i++){
    
    encodeChar(caz[i],str);
    print_pres(mh+2,i+mw,str,WHITE);
  }
  refresh_presentation();
  delay(3000);
  for (int i=0;i<60;i++){
    for (int j=0;j<60;j++)
      {
	encodeChar(0,str);	
	print_pres(mh+i,mw+j,str,WHITE);
      }
  }
  
  char caz2[]="...presenta:";
  for (int i=0;i<strlen(caz2);i++){

    encodeChar(caz2[i],str);
    print_pres(mh+3,i+mw+8+2,str,WHITE);
  }
  refresh_presentation();
  delay(2000);
  
  char two[]="Tuki e Giuli";
  for (int i=0;i<strlen(two);i++){

    encodeChar(two[i],str);
    print_pres(mh+4,i+mw+11,str,WHITE);
  }
  refresh_presentation();
  delay(3000);
for (int i=0;i<60;i++){
    for (int j=0;j<60;j++)
      {
	encodeChar(0,str);	
	print_pres(mh+i,mw+j,str,WHITE);
      }
  }
char three[]="Una produzione \"I Sisini Pazzi\"";
 for (int i=0;i<strlen(three);i++){

    encodeChar(three[i],str);
    print_pres(mh+5,i+mw+3,str,WHITE);
  }
  refresh_presentation();
  delay(2000);

char fo[]="visita www.isisinipazzi.it/tuki";
 for (int i=0;i<strlen(fo);i++){

    encodeChar(fo[i],str);
    print_pres(mh+6,i+mw+3,str,WHITE);
  }
  refresh_presentation();
  delay(3000);

  
  /*cleans the screen*/
  char zero=0;

  for (int i=0;i<60;i++){
    for (int j=0;j<60;j++)
      {
	encodeChar(zero,str);	
	print_pres(mh+i,mw+j,str,WHITE);
      }
  }
  
  
  for (int i=0;i<28;i++){

    encodeChar(zero,str);
    print_pres(mh+1,i+mw+2,str,WHITE);
  }
  for (int i=0;i<8;i++){

    encodeChar(zero,str);
    print_pres(mh+2,i+mw+10,str,WHITE);
  }
  for (int i=0;i<34;i++){

    encodeChar(zero,str);
    print_pres(mh+3,i+mw,str,WHITE);
  }
  refresh_presentation();
  delay(200);

  /*creates a flower stripe*/
  for(int i=0;i<PREWIDTH-1;i++)
    {
      encodeChar(FUTF, str);
      print_pres(PREHEIGHT-1,i,str,GREEN);
      delay(50);
      refresh_presentation();
    }
  refresh_presentation();
  delay(300);
 
      
  int ig;
  /*Giuli enters from left*/
  for(ig=-14;ig<(PREWIDTH-10);ig++){
    if(ig>-10)
    giuli_pres_clear(ig-1, 10);
    delay(10);
    giuli_pres_display(ig, 10);
    delay(100);
    if(ig<-10)delay(300);
    if(ig<-6)delay(100);
    if(ig<0)delay(30);
    if(ig<6)delay(10);
  }
  
  int it;
  /*Tuki enters from top left corner*/
  for(it=0;it<8;it++){
    if(it>0){
      tuki_pres_clear(it-1, it-1);
    }
    tuki_pres_display(it, it);
    delay(80);
  }
  delay(100);

  int jt = it-1;

  title_pres_display(2, 2);
  refresh_presentation();

  delay(2000);
}




/**
 * Creates a l-long wall with center in coordinates (xc, yc) 
 */
void add_square_wall(int xc,int yc,int l){
  if(l<2) return;
  int xl=0+xc-l/2;
  int xr=xl+l-1;
  int yt=0+yc-l/2;
  int yb=yc+l-1;
  if(xl>=0&&xr<BATTLEFIELDWIDTH&&yt>=0&&yb<BATTLEFIELDHEIGHT){
    battle_field[yt][xl]=TLC;
    battle_field[yb][xl]=BLC;
    battle_field[yb][xr]=BRC;
    battle_field[yt][xr]=TRC;
    for(int i=xl+1;i<xr;i++)battle_field[yt][i]=HLN;
    for(int i=xl+1;i<xr;i++)battle_field[yb][i]=HLN;
    for(int i=yt+1;i<yb;i++)battle_field[i][xl]=VLN;
    for(int i=yt+1;i<yb;i++)battle_field[i][xr]=VLN;
    
    /*remove flowers inside the square*/
    for(int i=xl+1; i<xr; i++)
      {
	for(int j=yt+1; j<yb; j++)
	  {
	    battle_field[j][i] = 0;
	  }
      }
    
    //for(int i=xl; i<=xr; i++)
    //battle_field[yt-1][i] = 0;

    for(int i=yt; i<=yb; i++)
      battle_field[i][xr+1] = 0;

    //for(int i=xl; i<=xr; i++)
    //battle_field[yb+1][i] = 0;

    for(int i=yt; i<=yb; i++)
    battle_field[i][xl-1] = 0; 
  }
}

/**
 * Creates the maze borders and the obstacles.
 * fills the battlefield with flowers
 */
void prepare_battle_field(){
  int l=1,i;
  int h=BATTLEFIELDHEIGHT;
  int w=BATTLEFIELDWIDTH;
  

  /*
   *maze borders
   */
  
  /*fills the field with flowers*/
  for(int i=1;i<h-1;i+=1)
    {
      for(int j=1;j<w-1;j+=1)
	{
	  battle_field[i][j]=FUTF;
	}
    }
 
  
  /*upper left-hand corner*/
  battle_field[0][0]=TLC;

  /*upper wall*/
  for(int j=1;j<BATTLEFIELDWIDTH-1;j++)
    {
      battle_field[0][j]=HLN;
    }

  /*upper right-hand corner*/
  battle_field[0][BATTLEFIELDWIDTH-1]=TRC;

  /*right wall*/
  for(i=1;i<BATTLEFIELDHEIGHT-1;i++)
    {
      battle_field[i][BATTLEFIELDWIDTH-1]=VLN;

    }
  /*lower right-hand corner*/
  battle_field[BATTLEFIELDHEIGHT-1][BATTLEFIELDWIDTH-1]=BRC;
  /*lower wall*/
  for(i=BATTLEFIELDWIDTH-2;i>0;i--)
    {
      battle_field[BATTLEFIELDHEIGHT-1][i]=HLN;
    }
  
  /*lower left-hand corner*/
    battle_field[BATTLEFIELDHEIGHT-1][0]=BLC;
    
    /*left wall*/
    for(i=BATTLEFIELDHEIGHT-2;i>0;i--)
      {
	battle_field[i][0]=VLN;	
      }
    
    //battle_field[0][0]=9487;

  /*wall in the middle*/

  //lower vertical
  battle_field[BATTLEFIELDHEIGHT-1][BATTLEFIELDWIDTH/2]=9531;
  battle_field[BATTLEFIELDHEIGHT-2][BATTLEFIELDWIDTH/2]=9475;
  battle_field[BATTLEFIELDHEIGHT-3][BATTLEFIELDWIDTH/2]=9475;

 
  //upper vertical
  battle_field[0][BATTLEFIELDWIDTH/2]=9523;
  battle_field[1][BATTLEFIELDWIDTH/2]=9475;
  battle_field[2][BATTLEFIELDWIDTH/2]=9475;

   //left horizontal
  battle_field[BATTLEFIELDHEIGHT/2][0]=9507;
  battle_field[BATTLEFIELDHEIGHT/2][1]=9473;
  battle_field[BATTLEFIELDHEIGHT/2][2]=9473;

   //right horizontal
  battle_field[BATTLEFIELDHEIGHT/2][BATTLEFIELDWIDTH-1]=9515;
  battle_field[BATTLEFIELDHEIGHT/2][BATTLEFIELDWIDTH-2]=9473;
  battle_field[BATTLEFIELDHEIGHT/2][BATTLEFIELDWIDTH-3]=9473;

 
  
  /*calls add_square_wall to create the walls*/
  switch (level){
  case 0:
    break;//No square
    
  case 1:
    //add_square_wall(BATTLEFIELDWIDTH/2,BATTLEFIELDHEIGHT/2,4);
    srand(time(NULL));
    int gg=rand()%3;
    int gh=rand()%2;
    add_square_wall(BATTLEFIELDWIDTH/(4)-1+gg,BATTLEFIELDHEIGHT/4+gh,2);
    gg=rand()%3;
    gh=rand()%2;
    add_square_wall(BATTLEFIELDWIDTH*(3.0/4.0)+1-gg,BATTLEFIELDHEIGHT/4-gh,2);
    gg=rand()%3;
    gh=rand()%2;
    add_square_wall(BATTLEFIELDWIDTH*(3.0/4.0)+1-gg,BATTLEFIELDHEIGHT*(3.0/4.0)-1-gh,2);
    gg=rand()%3;
    gh=rand()%2;
    add_square_wall(BATTLEFIELDWIDTH*(1./4.0)-1+gg,BATTLEFIELDHEIGHT*(3.0/4.0)-1+gh,2);
    //add_square_wall(5,5,2);
    break;
    }

  /*Now counts the number of flowers*/
  for(int i=0;i<h;i+=1)
    for(int j=0;j<w;j+=1){
      if(battle_field[i][j]==FUTF) flowers_number++;

    }

  
}



/**
 * Implements games's logic.
 */
void machine_turn(){
  t_or_g_1_or_2=2;

  giuli_turn();  
 
  
  /*prints the score*/
  char str[25];
  sprintf(str,"********************");
  print_score(str);
  sprintf(str,"G.score:%d T.score:%d",giuli_player.score,tuki_player.score);
  print_score(str);
  /*waits 100 milliseconds*/
  delay(DELAY);
  t_or_g_1_or_2=1;

  tuki_turn(); 
}

/**
 * Creates a delay
 */  
void delay(int milliseconds){
  long pause;
  clock_t now,then;
  
  pause = milliseconds*(CLOCKS_PER_SEC/1000);
  now = then = clock();
  while( (now-then) < pause )
    now = clock();
}


