#include "player.h"
#include <stdio.h>


/*
 *ImplemenT this function to capture giuli
 *feel free ti use all you want
 */

void tuki_turn(){
  static cicle=0;
  cicle++;
  if(cicle%2)
    {
      player_rotate(DOWN);
    }
  else
    {
      player_rotate(UP);
      
    }
  step();
  }
