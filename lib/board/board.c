#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board/board.h"


// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{
  int i;
  Item *node;

	char *initial = (char*)malloc(MAX_BOARD*sizeof(char));
	for (int i=0; i<MAX_BOARD; i++) initial[i] = 0;

  node = nodeAlloc();
	initBoard(node, initial);
  
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

// Return 0 if all queens are placed. Positive otherwise
// Ie: nb queens that still need to be placed.
double evaluateBoard(Item *node) {
  int nb = 0;
  int i = 0;

  while (i < node->size) {
    if (node->board[i] == 1) {
      nb++;
    }
    i++;
  }
	
  return WH_BOARD - nb;
}

// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition( Item *node, int pos )
{
	int ii = pos / WH_BOARD;
	int jj = pos % WH_BOARD;
  int pos2 = pos ;

  for (int i=0; i<WH_BOARD; i++) {
  	for (int j=0; j<WH_BOARD; j++) {
      pos2 = i*WH_BOARD+j;
      if (pos2 != pos) {
        if (i == ii && node->board[pos2] == 1) { // Ligne
          return 0 ;
        } else if (j == jj && node->board[pos2] == 1) { //Colonne
          return 0 ;
        } else if (abs(ii-i) == abs(jj-j) && node->board[pos2] == 1) {
          return 0;
        } 
      }
    }
  }

  return 1;
}

// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Item *getChildBoard( Item *node, int pos )
{
  Item *child_p = NULL;
  
	if ( isValidPosition(node, pos) ) {

    /* allocate and init child node */
    child_p = nodeAlloc() ;
    initBoard(child_p, node->board) ;

		/* Make move */
    child_p->board[pos] = 1 ;

		/* link child to parent for backtrack */
    child_p->parent = node ;

    child_p->depth = node->depth + 1 ;
  }

  return child_p;
}
