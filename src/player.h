/*Defined direction*/
#ifndef PLAYER
typedef enum  {LEFT,UP,RIGHT,DOWN,IN} direction;
typedef unsigned int utf8code;
typedef char utf[4];
#endif
#define PLAYER

/**
 *Makes the player rotate in the 'd' direction
 */
void player_rotate(direction d);

/**
 *Makes a step in the actual 'd' direction
 *Be aware that at the end of this  function  
 *the control is given to Giuli and
 *the instructions under it will not be executed 
 */
int step();

/**
 *Reads the battle-field at the position next the player one
 *given by the actual player position and direction direction
 *The int value of the player char is returned by the function
 *while the UTF8 represetation of the play-groud is coded in 'r'
 */
utf8code read_battle_field(utf r);

/**
 *Created a delay
 */
void delay(int milliseconds);
