#include "player.h"
#include <stdio.h>
#include <stdlib.h>

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

enum chartype {WALL,ITEM,OBSTACLE,DOOR,FOOD,FLOWER,ZORZ,UNKNOWN,Tuki,TUKI,EMPTY};
typedef enum chartype char_type;
/**
 *Battlefield cells graph representation
 */
typedef struct data
{
  int readed;
  int visited;
  char_type cell_type;
  int cont;
} Data;

typedef struct cell {
  Data d;
  struct cell* right;
  struct cell* down;
  struct cell* left;
  struct cell* up;
} Cell;
typedef Cell* graph;

/**
 *Cell path list
 */
typedef struct node{
  graph pcell;
  struct node * next;
  struct node * prev;
}Node;
typedef Node* path;  



/*Functions*/

char_type get_cell_type2(utf8code code);
direction symmetry2(direction d);
void new_graph2(graph* g);
graph add_to_graph2(graph pcell,Data d,direction dir);
void new_path2(path* p);
void add_head2(path* l, graph g);
int decode_char2(unsigned char* r);
Cell* get_neighbor2(path ap,direction inquired_dir);

FILE *f;


int nn2=0;
int moves2=0;
/**
 * Tuki algorithm based on The Boustrophedon Cellular Decomposition
 * Choset e Pignon
 */
void tuki_turn(){
  
  
  static int init=0;
  static graph g=NULL;
  static path p=NULL;
  static path l=NULL;
  moves2++;
 
 
  if(!init)
    {
     
      init=1;
      /* 1)Start with any cell in the decomposition. 
       * Insert itinto the path list. Mark it as visited*/
      /* The list of visited cells*/

      /*the battlefield*/
      new_graph2(&g);      
      graph fn=(graph)malloc(sizeof(Cell));
      g=fn;
      g->d.visited=1;
      g->d.cell_type=EMPTY;
      g->d.cont=-1;
      /*The cell list (path in the battlefield)*/
      new_path2(&p);
      add_head2(&p,g);
      
	}else
    {
     
    }
  
  /*Assigns the neighbors cells */
  unsigned char c[4];
  int r,cx;

  /*This is the cell where Tuki is*/
  g=p->pcell;
  if(!g) exit(-1);


  //Up
  player_rotate(UP);
  r =read_battle_field(c);
  cx=decode_char2(c);
  if(g->up==NULL)
    {
      graph gc=get_neighbor2(p,UP);
      if(gc){
	g->up=gc;
	gc->down=g;

	
      }else
	{

	  Data d={1,0,get_cell_type2(cx)};
	  graph tg=add_to_graph2(g,d,UP);


	}
    }else
    {
      g->up->d.readed=1;
      g->up->d.cell_type=get_cell_type2(cx);

     
    }

  
	//Down
  player_rotate(DOWN);
  r =read_battle_field(c);
  cx=decode_char2(c);
  if(g->down==NULL)
    {
      graph gc=get_neighbor2(p,DOWN);
      if(gc)
	{
	  g->down=gc;
	  gc->up=g;

	  
	}
      else
	{
	  Data d={1,0,get_cell_type2(cx)};
	  graph tg=add_to_graph2(g,d,DOWN);
	 

	}
    }else
    {
      g->down->d.readed=1;
      g->down->d.cell_type=get_cell_type2(cx);


    }



  //Right
  player_rotate(RIGHT);
  r =read_battle_field(c);
  cx=decode_char2(c);
  if(g->right==NULL)
    {
      /*check if the cell already exists*/
      graph gc=get_neighbor2(p,RIGHT);
      if(gc){
	g->right=gc;
	gc->left=g;

      }else
	{
	  Data d={1,0,get_cell_type2(cx)};
	  graph tg=add_to_graph2(g,d,RIGHT);

	}
    }else
    {
      g->right->d.readed=1;
      g->right->d.cell_type=get_cell_type2(cx);

      
    }
  
  
  //Left
  player_rotate(LEFT);
  r =read_battle_field(c);
  cx=decode_char2(c);
  if(g->left==NULL)
    {
      graph gc=get_neighbor2(p,LEFT);
      if(gc)
	{
	  g->left=gc;
	  gc->right=g;
	 
	  
	}else
	{
	  Data d={1,0,get_cell_type2(cx)};
	  graph tg=add_to_graph2(g,d,LEFT);


	}
    }else
    {
      g->left->d.readed=1;
      g->left->d.cell_type=get_cell_type2(cx);


    }
  


  

  
  /*
    2)Go to the rst unvisited cell in the neighbor list of
    the current cell (i.e., go to the rst clockwise
    unvisited cell). Insert this cell into the beginn2ing of
    the path list and mark it as visited.
   */
  delay(1);
 
 //chekcs L
  //if(g->left->d.cell_type==WALL)g->left->d.visited=1;
  if(g->left->d.visited==0&&g->left->d.cell_type!=WALL)
    {
      player_rotate(LEFT);
//      step();
      g=g->left;
      g->d.visited=1;
      add_head2(&p,g);
      l=p;

step();      
           
      return;
    }
//chekcs U
  //if(g->up->d.cell_type==WALL)g->up->d.visited=1;
  if(g->up->d.visited==0&&g->up->d.cell_type!=WALL)
    {
      player_rotate(UP);
  
      g=g->up;
      g->d.visited=1;
      add_head2(&p,g);
      l=p;


	    step();  
    
      return;
    }
      


 //chekcs R
  //if(g->right->d.cell_type==WALL)g->right->d.visited=1;
  if(g->right->d.visited==0&&g->right->d.cell_type!=WALL)
    {
      player_rotate(RIGHT);
      g=g->right;
      g->d.visited=1;
      add_head2(&p,g);
      l=p;
      step();

      return;
    }
  //chekcs D
  //if(g->down->d.cell_type==WALL)g->down->d.visited=1;
  if(g->down->d.visited==0&&g->down->d.cell_type!=WALL)
    {
      player_rotate(DOWN);
      g=g->down;
      g->d.visited=1;
      add_head2(&p,g);
      l=p;
      step();      

      
      return;
    }
 
  

  /*
    3) At this point, back track until a cell with unvis-
    ited neighbors is encountered. This back tracking is
    achieved by walking forward through the path list,
    inserting each element that is visited to the front
    of the path list, until an element with an unvisited
    neighbor is encountered. Insert this element to the
    front of the path list and repeat the above procedure
    (i.e., goto step 2).
   */
 
  /*back to previous cell*/
  l=l->prev;
if(l==NULL) exit(-1);
  /*Add it to the path list*/
  add_head2(&p,l->pcell);
  /*get the diretion*/
  direction nd;//next step direction
  if(g->right==l->pcell) nd=RIGHT;
  else
  if(g->left==l->pcell) nd=LEFT;
  else
  if(g->up==l->pcell) nd=UP;
  else
  if(g->down==l->pcell) nd=DOWN;

  /*Set as the online cell*/
  //g=l->pcell;
  /*move to the previous one*/
  player_rotate(nd);
  step();
  
}

Cell* get_neighbor2(path ap,direction dir){
  int R=0,U=0;
  int found=0;
  
  while(ap->prev){
    if(ap->pcell->right==ap->prev->pcell) R++;
    if(ap->pcell->left==ap->prev->pcell) R--;
    if(ap->pcell->up==ap->prev->pcell) U++;
    if(ap->pcell->down==ap->prev->pcell) U--;
    /*check neighbor condition*/
    //RIGHT
    if(dir==RIGHT&&R==1&&U==0)
      {
	return ap->prev->pcell;
      }
    //R-U
    if(dir==RIGHT&&(R==1)&&U==+1)
      {
	return ap->prev->pcell->down;
      }
    //R-D
    if(dir==RIGHT&&(R==1)&&U==-1)
      {
	return ap->prev->pcell->up;
      }


    if(dir==RIGHT&&R==2&&U==0)
      {
	//return ap->prev->pcell->left;
      }



    
    //L
    if(dir==LEFT&&R==-1&&(U==0))
      {
	return ap->prev->pcell;
      }
    //L-U
    if(dir==LEFT&&(R==-1)&&U==+1)
      {
	return ap->prev->pcell->down;
      }
    //L-D
    if(dir==LEFT&&(R==-1)&&U==-1)
      {
	return ap->prev->pcell->up;
      }


    if(dir==LEFT&&R==-2&&U==0)
      {
	//return ap->prev->pcell->right;
      }
    //UP
    if(dir==UP&&R==0&&U==1)
      {
	return ap->prev->pcell;
      }
    //U-L
    if(dir==UP&&(R==-1)&&U==+1)
      {
	return ap->prev->pcell->right;
      }
    //U-R
    if(dir==UP&&(R==1)&&U==+1)
      {
	return ap->prev->pcell->left;
      }

    
    if(dir==UP&&R==0&&U==2)
      {
	//return ap->prev->pcell->down;
      }
    // D
    if(dir==DOWN&&R==0&&U==-1)
      {
	return ap->prev->pcell;
      }
    //D-L
    if(dir==DOWN&&(R==-1)&&U==-1)
      {
	return ap->prev->pcell->right;
      }
    //D-R
    if(dir==DOWN&&(R==1)&&U==-1)
      {
	return ap->prev->pcell->left;
      }

    if(dir==DOWN&&R==0&&U==-2)
      {

	//return ap->prev->pcell->up;
      }
    ap=ap->prev;
  }
  return NULL;
}



char_type get_cell_type2(utf8code code){
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
    return Tuki;
  }
  if(code==TUTF){
    return TUKI;
  }
  
  if(code==10210||code==9830){
    return ITEM;
  }
  return UNKNOWN;
}
direction symmetry2(direction d){
  direction sd=IN;
  switch(d){
  case LEFT:
    sd=RIGHT;
    break;
  case RIGHT:
    sd=LEFT;
    break;
  case UP:
    sd=DOWN;
    break;
   case DOWN:
    sd=UP;
    break;
  }
  return sd;
  
}

void new_graph2(graph* g)
{
  *g = NULL;
}


/**
 *Add a cell to the graph after checking that a cell
 *was already present at the same poistion.
 *For each cell of the actual Tuki path is supposed
 *to exist another 4 cells at the ajacent direction
 *This functions.
 *The existence of a possible unlinked cell in the 'd' 
 *direction is tested scann2ing the path_list untill a
 *cell 
 */
graph add_to_graph2(graph pcell,Data d,direction dir){
  nn2++;
  Cell* n=(Cell*)malloc(sizeof(Cell));
  n->d=d;
  n->d.cont=nn2;
 
  switch(dir)
    {
    case UP:
      pcell->up=n;
      n->down=pcell;
      break;
    case DOWN:
      pcell->down=n;
      n->up=pcell;
      break;
    case RIGHT:
      pcell->right=n;
      n->left=pcell;
      break;
    case LEFT:
      pcell->left=n;
      n->right=pcell;
      break;
    }
  return n;
}

void new_path2(path* p){
  *p=0;
}
void add_head2(path* l, graph g) {
  Node* aux = (Node*)malloc(sizeof(Node));
  
  aux->prev = *l;
  aux->next = NULL;  
  aux->pcell = g;
  if(*l)(*l)->next=aux;
  *l = aux;
}
int decode_char2(unsigned char* r){ 
  unsigned int mB1,mB2,mB3,m6bits,m4bits;
  /*creates the masks*/
  m4bits=15;
  m6bits=63;
  int by4=0;
  int by1=r[0]&m4bits;
  int by2=r[1]&m6bits;
  int by3=r[2]&m6bits;
  int code=by4+by3+(by2<<6)+(by1<<12);
  return code;
}



