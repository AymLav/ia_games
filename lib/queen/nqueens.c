#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#include <malloc.h>

#include "board/list.h"
#include "board/board.h"


list_t openList_p;
list_t closedList_p;


void showSolution( Item *goal )
{
  int i = 0, j;

  printf("\nSolution:");

  while (goal) {
    printBoard( goal );
		goal = goal->parent;
		i++;
  }

  printf("\nLength of the solution = %d\n", i-1);
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
  return;
}


void bfs( void )
{
  Item *cur_node, *child_p, *temp;
  int i;
  
  initList(&closedList_p);

  while ( listCount(&openList_p) ) { /* While items are on the open list */
   	
		/* Get the first item on the open list */
		cur_node = popFirst(&openList_p);
		

		/* Add it to the "visited" list */
    addLast (&closedList_p, cur_node);

    /* Do we have a solution? */
    if ( evaluateBoard(cur_node) == 0.0 ) {
      showSolution(cur_node);
      return;

    } else {

      /* Enumerate adjacent states */
      for (int i = 0; i < MAX_BOARD; i++) {
        child_p = getChildBoard( cur_node, i );
   			
        if (child_p != NULL) { // it's a valid child!
					
					/* Ignore this child if already visited */
          if (!onList(&closedList_p, child_p->board)) {
					
            /* Add child node to openList */
            addLast( &openList_p, child_p );
          }
        }
      }
    }
  }

  return;
}

void dfs( void )
{
  Item *cur_node, *child_p, *temp;
  int i;
  
  initList(&closedList_p);

  while ( listCount(&openList_p) ) { /* While items are on the open list */
   	
		/* Get the first item on the open list */
		cur_node = popLast(&openList_p);
		
		/* Add it to the "visited" list */
    addLast (&closedList_p, cur_node);

    /* Do we have a solution? */
    if ( evaluateBoard(cur_node) == 0.0 ) {
      showSolution(cur_node);
      return;

    } else {

      /* Enumerate adjacent states */
      for (int i = 0; i < MAX_BOARD; i++) {
        child_p = getChildBoard( cur_node, i );
   			
        if (child_p != NULL) { // it's a valid child!
					
					/* Ignore this child if already visited */
          if (!onList(&closedList_p, child_p->board)) {
					
            /* Add child node to openList */
            addLast( &openList_p, child_p );
          }
        }
      }
    }
  }

  return;
}

int main()
{	
    int choice ;

    initList(&openList_p);
    initList(&closedList_p);

	
    printf("\nInitial:");
    Item *initial_state = initGame();
    printBoard( initial_state );

    printf("\nSearching ...\n");
  
	addLast( &openList_p, initial_state );
    
     printf ("Quel algorithme utiliser ?\n") ;
    printf ("0 - DFS\n1 - BFS\n") ;
    scanf ("%d", &choice) ;

    switch (choice) {
      case 0 :
        dfs();
        break ;
      case 1:
        bfs();
        break;
      default:
        printf("Erreur, le choix par défaut est bfs\n");
        bfs();
        break ;
    }

    printf("Finished!\n");
  
	cleanupList( &openList_p );
    cleanupList( &closedList_p );
	
    return 0;
}