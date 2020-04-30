#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "knight/board_knight.h"


// Initialize a new Game for the knights problem and place the knight on the first place
Item *initGame()
{
  int i;
  Item *node;

	char *initial = (char*)malloc(MAX_BOARD*sizeof(char));
	for (int i=0; i<MAX_BOARD; i++) initial[i] = 0;

  node = nodeAlloc();

  initBoard(node, initial);
  node->board[0] = 1;
  node->depth = 0;

  return node;
}

// print a board
void printBoard( Item *node )
{
  assert(node);
	printf("\n");
	for (int j=0; j<WH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
	for (int i = 0 ; i < MAX_BOARD ; i++) {
    if (i%WH_BOARD == 0) printf("|");
    if (node->board[i] == 0) printf("   |");
    else printf("%2d |", node->board[i]);
    if (((i+1)%WH_BOARD) == 0) {
			printf("\n");
			for (int j=0; j<WH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
		}
  }
	printf("\n");
}


// initialize node's state from a given board
void initBoard(Item *node, char *board) {
	assert( node );
  int i ;
	
	node->size = MAX_BOARD;
  node->board = calloc(MAX_BOARD, sizeof(char));
  
	/* Copy board */
  for (i = 0; i < MAX_BOARD; i++) {
    node->board[i] = board[i];
  }
}

double evaluateBoard(Item *node) {
  return !(node->board[MAX_BOARD-1] == 1);
}

// Test if position pos is valid with respect to node's state
int isValidPosition( Item *node, int pos )
{
	int ii = pos / WH_BOARD;
	int jj = pos % WH_BOARD;
    int posCaval = node->pos ;
    int ic = posCaval / WH_BOARD ;
    int jc = posCaval % WH_BOARD ;

    return abs(ic - ii) * abs(jc - jj) == 2 ;
}

Item *getChildBoard( Item *node, int pos )
{
  Item *child_p = NULL;
  
	if ( isValidPosition(node, pos) ) {

    /* allocate and init child node */
    child_p = nodeAlloc() ;
    initBoard(child_p, node->board) ;

		/* Make move */
    child_p->board[pos] = 1 ;
    child_p->board[node->pos] = 0 ;
    child_p->pos = pos ;

		/* link child to parent for backtrack */
    child_p->parent = node ;

    child_p->depth = node->depth + 1 ;

    child_p->f = child_p->depth ;
  }

  return child_p;
}
