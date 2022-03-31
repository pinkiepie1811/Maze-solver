#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "maze.h"
#include "path.h"
#include "queue.h"
#include "position.h"

/*
 * Precondition: 
 *maze points to a valid maze_t 
 * Postcondition:
 * return 1 if position is a valid open or end cell in maze
 * return 0 if position is not an open or end cell
 */
int
position_open(maze_t * maze, position_t position){
  int row = position.row;
  int col = position.col;

  int height = maze->height;
  int width = maze->width;

  if ( 0 <= row && row < height
       && 0 <= col && col < width){
    return (maze->cells[offset(maze,position)] == OPEN
            ||maze->cells[offset(maze,position)] == END);
  }//if position is inside maze
  return 0;
}//position_open

/*
 *Precondition:
 * maze points to a valid maze_t
 * queue points to a valid queue_t
 * path points to a valid list_t
 *
 *Postcondition:
 * if the neighbor position to the input position is open and unvisited, 
 * add that position to a path and enqueue that path to the queue
 */
void
addneighbor(maze_t * maze, queue_t * queue, list_t * path, position_t position){
  int row = position.row;
  int col = position.col;
  position_t east = {row, col+1};
  position_t west = {row, col-1};
  position_t north = {row-1, col};
  position_t south = {row+1, col};
  
  if (position_open(maze, east)){
    list_t * path_east = list_add(east, path);
    enqueue(queue, path_east);
  }//add path_east to the queue if east is a valid open position
  if (position_open(maze, west)){
    list_t * path_west = list_add(west, path);
    enqueue(queue, path_west);
  }//add path_west to the queue if west is a valid open position
  if (position_open(maze, north)){
    list_t * path_north = list_add(north, path);
    enqueue(queue, path_north);
  }//add path_north to the queue if north is a valid open position
  if (position_open(maze, south)){
    list_t *path_south = list_add(south, path);
    enqueue(queue, path_south);
  } //add path_south to the queue if south is a valid open position 
}// addneighbor

/* This program read a maze and return the shortest path from the 
 * start to the end position (if possible)
 */
int
main(void){
  //read the maze
  maze_t * maze = readMaze(stdin);
  
  if (maze == NULL){
    return 0;} //if the maze is blank, return 
  
  queue_t * queue = malloc(sizeof(queue_t));
  if (queue == NULL){
    perror("Unable to allocate memory for queue");
    return 1;}
  queue_initialize(queue); //initialize the queue

  list_t * path = NULL; //initialize the path 
  path  = list_add(maze->start, path); 
  enqueue(queue, path); //enqueue the path with the start position

  while(!queue_empty(queue)){
    path = dequeue(queue);
    position_t current = list_front(path);

    if (maze->cells[offset(maze, current)] == END){
      list_print_reverse(path);//print the path from the start
      freeMaze(maze); //free the maze
      list_free(path); //free the path
      free(queue); //free the queue
      return 0;}//if
       
    else{
      //mark the current position as visited
      maze->cells[offset(maze, current)] = VISITED;
      //add neighbor positions to the path and enqueue the augnmented path
      addneighbor(maze, queue, path, current);
    }//else
  }//while
    
  free(queue);
  freeMaze(maze);
  return 0;
}//main
    
     
