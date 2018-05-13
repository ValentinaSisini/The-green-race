#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "view.h"
//#include "tuki.h"

WINDOW *wBattleField;
WINDOW *wTuki; // Tuki
WINDOW *wEmpty;
WINDOW *wGiuli; //Giuli
WINDOW *wScore;
WINDOW *wMsg;
WINDOW *wSad_giuli;

WINDOW *wPresentation;
WINDOW *wTuki_pres;
WINDOW *wGiuli_pres;
WINDOW *wTitle_pres;

extern utf8code presentation[PREHEIGHT][PREWIDTH];
extern utf8code battle_field[BATTLEFIELDHEIGHT][BATTLEFIELDWIDTH];
extern utf8code players[BATTLEFIELDHEIGHT][BATTLEFIELDWIDTH];
extern int giuli_color;
//extern FILE *debug;

int map_x_in_cols(int x){
  return x*XMAP;
}


/**
 * Creates a new window in battlefield[col][row] that contains str
 * and the color specified
 */
void _printat(int row,int col,utf str,int color){
  
  WINDOW* w=newpad(1,1);
  wattrset(w,COLOR_PAIR(color));
  waddstr(w,str);
  copywin(w,wBattleField,0,0,row+MROW,col+MCOL,row+MROW,col+MCOL,0);
}

/**
 * Receives an utf8code and a char array.
 * Creates a mask.
 * Fills the array with the mask and the bytes of the utf8code
 */
void encodeChar(utf8code code,utf dest){
  unsigned int mB1,mB2,mB3,m6bits,m4bits;
  /*creates the masks*/
  m4bits=15;
  m6bits=63;
  mB3=128;
  mB2=128;
  mB1=224;

  /*if "code" is an ascii character the function writes it in the first
   byte of dest and fills the second byte with zeros*/
  if(code<128)
    {
      int mm=127;
      dest[0]=code&mm;
      dest[1]=0;
      return;
    }

  /*fills the three first bytes of dest with the mask and the bytes of
   "code"*/
  dest[3]=0;
  dest[2]=(m6bits&code)+mB2;
  dest[1]=(m6bits&(code>>6))+mB3;
  dest[0]=(m4bits&(code>>12))+mB1;
}



/**
 * Creates a new pad for messages
 */
void msg_init()
{
  wMsg = newpad(MSGHEIGHT, MSGWIDTH);
}


/**
 * Prints only one character in the presentation 
 */
void print_pres(int row,int col,utf str,int color){
  WINDOW* w=newpad(1,1);
  wattrset(w,COLOR_PAIR(color));
  waddstr(w,str);
  copywin(w,wPresentation,0,0,row+MROW,col+MCOL,row+MROW,col+MCOL,0);
}


void title_pres_init(){
  wTitle_pres = newpad(3, 30);
  wclear(wTitle_pres);

  wattrset(wTitle_pres,COLOR_PAIR(YELLOW));
  waddstr(wTitle_pres,"_____      .   _   _ .      .\n");
  waddstr(wTitle_pres,"  |  |  ||/|  |_  | _||  || |\n");
  waddstr(wTitle_pres,"  |  |__||\\|  |_  |_|||__||_|\n");
}
  

/**
 * Creates a new pad for Tuki in the presentation window
 */
void tuki_pres_init(){
  wTuki_pres = newpad(5,15);
  wclear(wTuki_pres);			// clear pad  
  char str[4];
  encodeChar(TUTF,str);
  int color=getColor(TUTF);
  wattrset(wTuki_pres,COLOR_PAIR(color));	// set color
  
  waddstr(wTuki_pres," __\\|__\n");
  waddstr(wTuki_pres,"/ o\\/ o\\\n");
  waddstr(wTuki_pres,"\\__/\\__/\n");
  waddstr(wTuki_pres,"  /\\/\\  \n");
  waddstr(wTuki_pres,"_/    \\_\n");  
}

/**
 * Creates a new pad for Giuli in the presentation window
 */
void giuli_pres_init(){
  wGiuli_pres = newpad(5,15);
  wclear(wGiuli_pres);			// clear pad
  char str[4];
  encodeChar(GUTF,str);
  int color=getColor(GUTF);
  
  wattrset(wGiuli_pres,COLOR_PAIR(color));	// set color
  waddstr(wGiuli_pres,"     \\__/\n");
  waddstr(wGiuli_pres,"   _ /..\\\n");
  waddstr(wGiuli_pres,"  / \\\\__/\n");
  waddstr(wGiuli_pres,"/\\\\_/    \n");
  waddstr(wGiuli_pres,"\\/       \n");
}

/**
 * Displaies presentation window with its pads
 */
void presentation_restore(int x, int y){
  char str[4];
  x=map_x_in_cols(x);
  encodeChar(presentation[y][x],str);
  print_pres(y,x,str,getColor(presentation[y][x]));
}

/**
 * Updates resentation window
 */
void refresh_presentation()
{
	redrawwin(wPresentation); // needed to display graphics properly at startup on some terminals
	wrefresh(wPresentation);
}

/**
 * Displaies giuli_pres's pad on the presentation window
 */
void title_pres_display(int x, int y){
  x=map_x_in_cols(x);
  copywin(wTitle_pres,wPresentation,0,0,MROW+y,MCOL+x,MROW+2+y,MCOL+29+x,0);
  refresh_presentation();
}



/**
 * Displaies title_pres's pad on the presentation window
 */
void giuli_pres_display(int x, int y){
  x=map_x_in_cols(x);
  copywin(wGiuli_pres,wPresentation,0,0,MROW+y,MCOL+x,MROW+4+y,MCOL+14+x,0);
  refresh_presentation();
}

/**
 * Displaies tuki_pres's pad on the presentation window
 */
void tuki_pres_display(int x, int y) 
{
  x=map_x_in_cols(x);
  copywin(wTuki_pres,wPresentation,0,0,MROW+y,MCOL+x,MROW+4+y,MCOL+14+x,0);
  refresh_presentation();
}

void tuki_pres_clear(int x, int y) 
{
  x=map_x_in_cols(x);
  copywin(wEmpty,wPresentation,0,0,MROW+y,MCOL+x,MROW+4+y,MCOL+14+x,0);
  //copywin(wEmpty,wPresentation,0,0,y+MROW,x+MCOL,y+MROW,x+MCOL,0);
  refresh_presentation();
}

void giuli_pres_clear(int x, int y)
{
  x=map_x_in_cols(x);
  copywin(wEmpty,wPresentation,0,0,MROW+y,MCOL+x,MROW+4+y,MCOL+14+x,0);
  refresh_presentation();
}

void title_pres_clear(int x, int y)
{
  x=map_x_in_cols(x);
  copywin(wEmpty,wPresentation,0,0,MROW+y,MCOL+x,MROW+2+y,MCOL+29+x,0);
  refresh_presentation();
}

/**
 * Creates a new pad for scores
 */
void score_init()
{
  wScore = newpad(SCOREHEIGHT, SCOREWIDTH);
}

/**
 * Creates a new pad for presentation
 */
void presentation_init()
{
  
  /*creates a new window*/
  wPresentation = newwin(PREHEIGHT+MARGINH, PREWIDTH+MARGINW, 0, 0);
  
  /*clears the window*/
  wclear(wPresentation);
  
  /*move window*/
  mvwin(wPresentation, 0, 0);
  
  /*associates the character or the utf8code to its position in the
    battlefield*/
  char str[4];
  for(int i=0;i<PREWIDTH;i++)
    {
      for(int j=0;j<PREHEIGHT;j++){
	
	encodeChar(presentation[j][i],str);
	print_pres(j,i,str,getColor(presentation[j][i]));
      }
    }
}



/**
 * Creates a new pad for the battle_field and sets the 
 * battlefield elements on it
 */
static void battleFieldInit(){
  wEmpty = newpad(SCREENHEIGHT+10, SCREENWIDTH+10);
  wclear(wEmpty);
  
  /*creates a new window*/
  wBattleField = newwin(SCREENHEIGHT+MARGINH, SCREENWIDTH+MARGINW, 0, 0);
  
  /*clears the window*/
  wclear(wBattleField);
  
  /*move window*/
  mvwin(wBattleField, 20, 20);
  
  /*associates the character or the utf8code to its position in the
    battlefield*/
  char str[4];
  for(int i=0;i<BATTLEFIELDWIDTH;i++)
    {
      for(int j=0;j<BATTLEFIELDHEIGHT;j++){
	utf8code uc=battle_field[j][i];
	encodeChar(uc,str);
	if(uc==HLN)
	  {
	    _printat(j,map_x_in_cols(i),str,getColor(battle_field[j][i]));
	     _printat(j,map_x_in_cols(i)+1,str,getColor(battle_field[j][i]));
	  }else 
	if(uc==TLC||uc==BLC||uc==TT||uc==TB||uc==TL)
	  {
	    _printat(j,map_x_in_cols(i),str,getColor(battle_field[j][i]));
	    encodeChar(HLN,str);
	    _printat(j,map_x_in_cols(i)+1,str,getColor(battle_field[j][i]));
	  }
	
	else
	 
	_printat(j,map_x_in_cols(i),str,getColor(battle_field[j][i]));
      }
    }
  
}

/**
 * Prints the scores
 */
void print_score(char *strscore){
  wattrset(wScore,COLOR_PAIR(WHITE));
  wclear(wScore);
  waddstr(wScore,strscore);
  copywin(wScore,wBattleField,0,0,SCREENHEIGHT+MROW,MCOL+1,SCREENHEIGHT+MROW,SCOREWIDTH+MCOL+1,1);
}

void cleanat(int y,int x,int color){
  x=map_x_in_cols(x);
  _printat(y,x, 0, color);
   _printat(y,x+1, 0, color);
}

void printat(int y,int x,utf str,int color){
  x=map_x_in_cols(x);
  _printat(y,x, str, color);
}
void print_string_at(int y,int x, char *str,int color){
  int l=strlen(str);
  x=map_x_in_cols(x);
  WINDOW* w=newpad(1,l);
  wattrset(w,COLOR_PAIR(color));
  waddstr(w,str);
  copywin(w,wBattleField,0,0,y+MROW,x+MCOL,y+MROW,x+MCOL+l-1,0);
}

/**
 * Creates a new pad for Tuki in battle_field window
 */
void playerInit(){
  wTuki = newpad(1,2);
  wclear(wTuki);			// clear pad  
  char str[4];
  encodeChar(9928,str);
  int color=getColor(9928);
  wattrset(wTuki,COLOR_PAIR(color));	// set color
  //waddstr(wTuki,str);
  waddstr(wTuki,"@>");
}

/**
 * Creates a new pad for Giuli in battle_field window
 */
void giuliInit(){
  wGiuli = newpad(1,1);
  wclear(wGiuli);			// clear pad
  char str[4];
  encodeChar(GUTF,str);
  int color=getColor(GUTF);
  wattrset(wGiuli,COLOR_PAIR(color));	// set color
  waddstr(wGiuli,str);
}

/**
 * Creates a new pad for Sad Giuli
 */
void sad_giuli_init(){
  wSad_giuli = newpad(1,1);
  wclear(wSad_giuli);			// clear pad
  char str[4];
  encodeChar(SADGUTF,str);
  int color=getColor(GUTF);
  wattrset(wSad_giuli,COLOR_PAIR(color));	// set color
  waddstr(wSad_giuli,str);
}

/**
 * Displaies battle_field window with its pads
 */
void battle_field_restore(int x, int y){
  char str[4];
  int  xp=map_x_in_cols(x);
  encodeChar(battle_field[y][x],str);
  _printat(y,xp,str,getColor(battle_field[y][x]));
  _printat(y,xp+1,0,getColor(battle_field[y][x]));
 
}

/**
 * Dispalyes Giuli's pad
 */
void giuli_display(int x, int y){
  x=map_x_in_cols(x);
  copywin(wGiuli,wBattleField,0,0,y+MROW,x+MCOL,y+MROW,x+MCOL,0);
  refreshScreen();
}

/**
 * Displaies Sad Giuli's pad
 */
void sad_giuli_display(int x, int y){
  x=map_x_in_cols(x);
  copywin(wSad_giuli,wBattleField,0,0,y+MROW,x+MCOL,y+MROW,x+MCOL,0);
  refreshScreen();
}

/**
 * Displaies score pad
 */
void score_display()
{ 
  copywin(wScore,wScore,0,0,0,0,0,0,0);
}

/**
 * Displaies Tuki's pad
 */
void tuki_display(int x, int y) 
{
  x=map_x_in_cols(x);
  copywin(wTuki,wBattleField,0,0,y+MROW,x+MCOL,y+MROW,x+1+MCOL,0);
}

/**
 * Clears Tuki's pad
 */
void playerClear(int x, int y) 
{
  x=map_x_in_cols(x);
  copywin(wEmpty,wBattleField,0,0,y+MROW,x+MCOL,y+MROW,x+MCOL,0);
  copywin(wEmpty,wBattleField,0,0,y+MROW,x+MCOL+1,y+MROW,x+MCOL+1,0);
}

/**
 * refresh screen so that modified graphic buffers get visible
 */
void refreshScreen()
{
  redrawwin(wBattleField); // needed to display graphics properly at startup on some terminals
  wrefresh(wBattleField);
}

/**
 * do proper cleanup
 */
void finish()
{
  endwin();	// <curses.h> reset terminal into proper non-visual mode
  exit(0);
}

void graphicEngineInit()
{
  (void) initscr();		// <curses.h> do initialization work 
  keypad(stdscr, TRUE);		// <curses.h> enable keypad for input
  (void) nonl();			// <curses.h> disable translation return/ newline for detection of return key
  (void) cbreak();		// <curses.h> do not buffer typed characters, use at once
  (void) noecho();		// <curses.h> do not echo typed characters
  start_color();
  init_pair(RED, COLOR_RED, COLOR_BLACK);		// <curses.h> define color-pair
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);	// <curses.h> define color-pair
  init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);	// <curses.h> define color-pair
 
  
  battleFieldInit();

  playerInit();
  giuliInit();
  score_init();
  
  
  tuki_pres_init();
  presentation_init();
  giuli_pres_init();
  msg_init();
  title_pres_init();
  sad_giuli_init();
  
}

char_type get_char_type(utf8code code){
  if(code==TLC||code==TRC||code==BRC||code==BLC||code==HLN||code==VLN||code==TT||code==TB){
    return WALL;
  }
  
  if(code==0){
    return EMPTY;
  }
  
  if(code==FUTF){
    return FLOWER;
  }
  if(code==GUTF){
    return GIULI;
  }
  if(code==TUTF){
    return TUKI;
  }
  
  if(code==10210||code==9830){
    return ITEM;
  }
  return UNKNOWN;
}

int getColor(utf8code u){
  switch(u){
  case 9752:
    return GREEN;
  case 9928:
    return CYAN;
  case GUTF:
    return RED;
  default:
    return MAGENTA;
  }
}
