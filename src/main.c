#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
#include "machine.h"
#include "player.h"
#include <locale.h>


#define MAJOR    0
#define MINOR    1
#define RELEASE  1


int stdin_copy;
utf8code presentation[PREHEIGHT][PREWIDTH];
utf8code battle_field[SCREENHEIGHT][SCREENWIDTH];
utf8code players[SCREENHEIGHT][SCREENWIDTH];

/*The game player*/
Player giuli_player, tuki_player;

/*Game status*/
int playing;
int winner;
int danger=0;
int flowers_number;
char expd[]={'r','o','o','e','t','l','i','g','f','t','i','t'};
int giuli_color;
int skip;
int t_or_g_1_or_2;
int level;
/*Debug*/
//FILE * debug;
//#define DEBUG

void tuki_turn();

/*
 * evaluate command line parameters 
 */
static void evaluateCommandLine(int argc, char **argv){

  
  if (argc == 2 && strcmp(argv[1], "-student") == 0) {
    level = 0; 
    return;
  }
  
  if(argc == 2 && strcmp(argv[1], "-gpl") == 0) {
    fprintf(stderr,"GPL");
  }else
    if ((argc == 2 && strcmp(argv[1], "-h") == 0)||argc==1)
      {
	
	
	fprintf(stderr,"Usage  ./tuki [OPTIONS]\n");
	fprintf(stderr,"-p\tPLAY THE GAME\n");
	//fprintf(stderr,"-i\tprint game instructions\n");
	fprintf(stderr,"-v\tgame version\n");
	fprintf(stderr,"-s\tskip intro and play\n");
	fprintf(stderr,"-h\tthis help\n");
	fprintf(stderr,"-c\tthis credits\n");
	//fprintf(stderr,"-GPL\tprint GPL license\n");
	exit(0);
      }
    else if (argc == 2 && strcmp(argv[1], "-v") == 0) {
      fprintf(stderr, "*** tuki %i.%i.%i\nCopyleft 2018 iSisiniPazzi\n", MAJOR, MINOR, RELEASE);
      getchar();
      exit(1);
    }
    else if (argc == 2 && strcmp(argv[1], "-p") == 0) {
    return;
    }
  else if (argc == 2 && strcmp(argv[1], "-i") == 0) {

    fprintf(stderr,"Edit tuki_turn.c and implement your code in order to make Tuki eats more flowers of Giuli\n");
    fprintf(stderr,"Use the player.h API to interact with the environment.\n");
	fprintf(stderr,"Compile and link your code to the rest of the binary object by typeing \"make\" at the prompt\n");
      
      getchar();
      exit(1);
    }
  else if (argc == 2 && strcmp(argv[1], "-c") == 0) {
    fprintf(stderr,"\nCredits:\n\n");
    fprintf(stderr,"A game developed by \"Scuola Sisini\" facebook.com/MatematicaFisicaSisini/\n");
    fprintf(stderr,"Francesco Sisini \t Main developer\t (francescomichelesisini@gmail.com)\n");
    fprintf(stderr,"Valentina Sisini \t Assistant developer\n");
    fprintf(stderr,"Giorgio Dall'Aglio \t Beta testing and MacOS porting\n");
    exit(1);
  }
  else if (argc == 2 && strcmp(argv[1], "-s") == 0) {
    skip=1;
    }
  else if (argc >1) {
    fprintf(stderr," ");
    exit(1);
  }
}



int main(int argc, char **argv)
{
  level=1;
  skip=0;
  strcpy(tuki_player.name, "tuki");
  strcpy(giuli_player.name, "giuli");
  evaluateCommandLine(argc, argv);

  /*Disable keyboard control*/
  stdin_copy = dup(STDIN_FILENO);
  close(STDIN_FILENO);
  getchar();
  
  setlocale(LC_CTYPE,"");
  /*establishes Giuli and Tuki's starting positions*/
  //tuki_player.posX=(SCREENWIDTH/4)+2;
  tuki_player.posX=1;
  tuki_player.posY=1;
  tuki_player.UTF=TUTF;
  giuli_player.posX=14;
  giuli_player.posY=14;
  giuli_player.UTF=GUTF;
  
   
  /*prepares the battlefield*/
  prepare_battle_field();
  graphicEngineInit();
  
  
  
  /**
   *PRESENTAZIONE
   */
  if(!skip)
    presentation_turn();
    
  /**
   *START GAME
   */
  
  /*starts the loop that gives the control to the engine and to the 
    gamer alternatively*/
  playing=1;
  refreshScreen();
  while(playing){
    t_or_g_1_or_2=2;
    machine_turn();
    t_or_g_1_or_2=1;
    tuki_turn();
  }  
  /*end of the game*/
  finish();
}


