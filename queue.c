#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "position.h"

/* Initialize a queue data structure
 * 
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 * Postconditions:
 *   queue_empty(queue) == true
 */
void
queue_initialize (queue_t * queue){
    queue->front = NULL;
    queue->rear = NULL;
}//queue_initialize

/* Determine whether a queue is empty
 * 
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 *   queue_initialize(queue) has been called at some point
 * Postconditions:
 *   Returns true when queue_initialize has been called on the given queue and
 *   both enqueue and dequeue have been called the same number of times
 */
bool
queue_empty (const queue_t * queue){
    return (queue->front == NULL);
}//queue_empty

/* Insert a solution at the rear of a queue
 * 
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 *   initialize(queue) has been called at some point
 * Postconditions:
 *   Returns whether the item was successfully inserted. 
 *   When true, queue_empty(queue)==false and path appears at the end of
 *     the queue
 *   Only the reference path is stored; no deep copy is made and the queue is not 
 *     responsible for managing any memory associated with path
 */
bool
enqueue (queue_t * queue, list_t * path){
 node_t * newNode = malloc(sizeof(node_t));
    if (newNode == NULL){
    return false;
    }//verify if memory allocation is successful
    //assigning values to newNode
    newNode->solution = path;
    newNode->next = NULL;

  if (queue_empty(queue)){
    queue->front = newNode;
    queue->rear = newNode;
  }//if the queue is empty
  else{
    queue->rear->next = newNode;
    queue->rear = newNode;
  }//else
  return true;
}//enqueue

/* Remove and return the item at the front of the queue
 *
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 *   queue_initialize(queue) has been called at some point
 *   queue_empty(queue) is false [verified]
 * Postconditions:
 *   Returns the item at the front of the queue (i.e., the remaining item least
 *     recently enqueued)
 *   The item has been removed from the queue
 */
list_t*
dequeue (queue_t * queue){       
  assert(!queue_empty(queue)); //verify if the queue is not empty
  list_t * removed = queue->front->solution;
  node_t * first = queue->front;
  if (queue->front->next == NULL){
    queue->front = NULL;
    queue->rear =  NULL;} //if the queue has only one node_t
  else {
    queue->front = queue->front->next;} //else
  free(first);  //free the node_t
  return removed;   
}//dequeue

/* Return the solution at the front of the queue
 *
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 *   queue_initialize(queue) has been called at some point
 *   queue_empty(queue) is false [verified]
 * Postconditions:
 *   Returns the item at the front of the queue (i.e., the remaining item least
 *     recently enqueued)
 *   queue is unaltered
 */
list_t*
queue_front (const queue_t * queue){
  assert(!queue_empty(queue)); //verify if the queue is empty
 
  return queue->front->solution;
}//queue_front
