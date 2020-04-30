#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "taquin/board_taquin.h"

const move_t moves[MAX_BOARD] = {
 /* 0 */ { 2, {1, 3} },
 /* 1 */ { 3, {0, 2, 4} },
 /* 2 */ { 2, {1, 5} },
 /* 3 */ { 3, {0, 4, 6} },
 /* 4 */ { 4, {1, 3, 5, 7} },
 /* 5 */ { 3, {2, 4, 8} },
 /* 6 */ { 2, {3, 7} },
 /* 7 */ { 3, {4, 6, 8} },
 /* 8 */ { 2, {5, 7} } };


// Initialize a new Game according to the difficulty given in the parameters
Item *initGame(int difficulty)
{
  int i;
  Item *node;

    char easy[MAX_BOARD] = {1, 2, 5, 3, 0, 4, 7, 8, 6};
    char medium[MAX_BOARD] = {7, 4, 8, 2, 5, 6, 3, 1, 0};
    char difficult[MAX_BOARD] = {8, 0, 7, 5, 6, 1, 3, 2, 4};

    node = nodeAlloc();

    switch (difficulty)
    {
    case 0:
	    initBoard(node, easy);
        node->blank = 4;
        break;
    case 1:
        initBoard(node, medium);
        node->blank = 8 ;
        break;
    case 2:
        initBoard(node, difficult);
        node->blank = 1;
        break;
    default:
        break;
    }
  
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

// Return the number of pieces well placed
double evaluateBoard(Item *node) {
  int i, nb ;

    nb = 0;
    for (i = 0; i < MAX_BOARD; i++) {
        if (node->board[i] == i + 1) {
          nb ++;
        }
    }
    return MAX_BOARD - nb - 1 ;
}

// Test if position pos is valid with respect to node's state
int isValidPosition( Item *node, int pos )
{
    int i, ii, jj ;

    for (i = 0; i < moves[node->blank].len; i++) {
        if (moves[node->blank].valid[i] == pos ) return 1;
    }

  return 0;
}

Item *getChildBoard( Item *node, int pos )
{
  Item *child_p = NULL;
  char tmp ;
  
	if ( isValidPosition(node, pos) ) {

    /* allocate and init child node */
    child_p = nodeAlloc() ;
    initBoard(child_p, node->board) ;

		/* Make move */
    tmp = child_p->board[pos] ;
    child_p->board[pos] = 0 ;
    child_p->board[node->blank] = tmp ;
    child_p->blank = pos ;

		/* link child to parent for backtrack */
    child_p->parent = node ;

    child_p->depth = node->depth + 1 ;
  }

  return child_p;
}

double getSimpleHeuristic( Item *node )
{
    return evaluateBoard(node);
}

double getManhattanHeuristic(Item *node)
{
    int i,ii,j,jj,nCase,pos,pos_finale;
    double value = 0;
    
    for(nCase=0; nCase < MAX_BOARD; nCase++)
    {
        pos = 0 ;
        while (node->board[pos] != nCase) pos++ ;

        pos_finale = (nCase-1)%MAX_BOARD ;
        if(pos != pos_finale)
        {
            i = pos / WH_BOARD ;
            j = pos % WH_BOARD ;
            ii = pos_finale / WH_BOARD ;
            jj = pos_finale % WH_BOARD ;
            
            value = value + abs(i-ii) + abs(j-jj) ;
        }
    }
    
    return value ;
}