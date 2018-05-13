#include "player.h"

#define DEBUG

#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define CYAN 5
#define MAGENTA 6
#define WHITE 7

/*Actual screen dimensions*/
#define XMAP 2
#define SCREENHEIGHT 16
#define SCREENWIDTH 32
/*Logical battlefiled dimension*/
#define BATTLEFIELDHEIGHT SCREENHEIGHT
#define BATTLEFIELDWIDTH SCREENWIDTH/XMAP 



#define MARGINH 15
#define MARGINW 15
#define MROW 2
#define MCOL 5
#define PLAYERWIDTH 5
#define PLAYERPOSY (SCREENHEIGHT-2);
#define SCOREHEIGHT 2
#define SCOREWIDTH 25
#define HEADERHEIGHT 5
#define PREHEIGHT 16
#define PREWIDTH 31
#define MSGHEIGHT 16
#define MSGWIDTH 31


#define GUTF 9787
#define TUTF 0040
#define SADGUTF 9785

/*battlefield utf*/
#define TLC 9487
#define TRC 9491
#define BRC 9499
#define BLC 9495
#define HLN 9473
#define VLN 9475
#define TT 9531
#define TB 9523
#define TL 9507
#define TR 9523
#define FUTF 9752
enum chartype {WALL,ITEM,OBSTACLE,DOOR,FOOD,FLOWER,UNKNOWN,GIULI,TUKI,EMPTY};
typedef enum chartype char_type;


/*engine functions*/
void delay(int milliseconds);
void print_score(char *strscore);
char_type get_char_type(utf8code code);
void giuli_display(int x, int y);
void giuliInit();
int getColor(utf8code u);
void machine_turn();
void playerClear(int x, int y); 
void tuki_display(int x, int y);
void refreshScreen();
void finish();
void graphicEngineInit();
void encodeChar(utf8code code,utf dest);
void print_string_at(int y,int x, char *str,int color);
void printat(int row,int col,utf str,int color);
void battle_field_restore(int x, int y);
void presentation_restore(int x, int y);
void refresh_presentation();
void tuki_pres_clear(int x, int y);
void giuli_pres_clear(int x, int y); 
void tuki_pres_display(int x, int y);
void giuli_pres_display(int x, int y); 
void title_pres_init();
void title_pres_display(int x, int y);
void title_pres_clear(int x, int y);
void sad_giuli_display(int x, int y);
void cleanat(int y,int x,int color);
void print_pres(int row,int col,utf str,int color);
