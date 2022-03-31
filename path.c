#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include "path.h"
#include "position.h"
/* Add the given position to the front of a list
 *
 * Produces:
 *   added
 * Preconditions:
 *   current is NULL or points to a valid list_t
 * Postconditions:
 *   added is a newly allocated list_t with
 *     added->next = current
 *     added->position = position 
 *   or added is NULL if memory allocation fails
 */
list_t * 
list_add ( position_t position, list_t* current){
  list_t * added = malloc(sizeof(list_t));
  if (added == NULL){
    return added;
  }//verify if memory allocation is success
  added->next = current;
  added->position = position;
  return added;
}//list_add

/* Get the front of the list (the most recently added item)
 * 
 * Preconditions:
 *   current points to a valid list
 *   current != NULL [verified]
 * Postconditions:
 *   Returns the position in the node at the front of the list
 */
position_t
list_front (list_t* current){
  assert(current != NULL); //verify if current is not NULL
  position_t front = current -> position;
  return front;
}//position_t

/* Prints the given list in reverse order, with each position in "row,col" form
 * followed by a newline. The last position printed also includes a newline.
 * 
 * Pattern (example):
 *   0,14
 *   1,14
 *   1,13
 *   (etc)
 */
void
list_print_reverse ( list_t* list){
  if (list == NULL){
    return;//base case
  }
  list_print_reverse(list->next); //recursive call
  position_t current = list->position;
  printf("%d,%d\n", current.row, current.col); //print
}//list_print_reverse

/* Releases all the memory associated with the list.
 *
 * Preconditions:
 *   [No additional.]
 * Preferences:
 *   The list is singly connected (that is, there are no other references to 
 *     the nodes in this list
 * Postconditions:
 *   Every node in the list is freed
 */
void
list_free ( list_t* list){
  list_t * current = list;
  list_t * next = list->next;
        
  while(next!= NULL){
    next=current->next;
    free(current);
    current=next;
  } //while
  free(current);
  
}//list_free
