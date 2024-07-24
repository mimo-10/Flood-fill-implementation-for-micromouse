#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

#include "API.h"
#include "utils.h"

#define log(text) std::cerr << text << std::endl;


uint8_t state;

Position startingPoint;

int main(int argc, char* argv[]) {

    // uint8_t x = 0;
    // uint8_t y = 0;
    uint8_t distance = 0;
    log("Begin maze exploring...");
    API::setColor(0, 0, 'Y');
    API::setText(0, 0, "S");
    startingPoint = {0, 0};
    currentPosition= startingPoint;
    PrevPosition = currentPosition;
    height = 16;
    width = 16;
    currentDirection = upDir;
    desiredPosition = {8, 7};
    Maze maze; // needs update
    // setup();
    
    maze.MazeInit(false);
    maze.MazeInit(true);
    maze.ShowMaze(2);
    
    
    // desiredPosition.x = maze.getInfo()[2];
    // desiredPosition.y = maze.getInfo()[3];
    // maze.ShowMaze(0);
    while (true) {
        
        API::setColor(currentPosition.x, currentPosition.y, 'B');
        setWallMaze(maze);
        // if (maze.FloodMaze()[currentPosition.x][currentPosition.y] == 0) {
        //     currentPosition = {0, 0};
        //     currentDirection = upDir;
        //     API::ackReset();
        //     continue;
        // };
        
        uint8_t prevWall = maze.WallMaze()[currentPosition.x][currentPosition.y];
        uint8_t wall = wallUpdate(wallRead(), currentDirection,  currentPosition, maze);
        if (maze.FloodMaze()[currentPosition.x][currentPosition.y] !=0) {
            if (state != finalRun) {
                if (true) {
                FloodFill( currentPosition, maze);}
            } else {
                // makeFullFloodedDestination(maze);
                std::cerr << "Done" << std::endl;
                
                // break;
            }
            if (state == end) {
                // //display done
                break;
            }
                
        } else  {
            switch(state) {
                case firstRun :
                    newDistinationInit(maze, {0, height-1});
                    state = explore1;
                    break;
                case explore1 : 
                    newDistinationInit(maze, {0, 0});
                    state = explore2;
                    break;
                case explore2 : 
                    newDistinationInit(maze, {(int)width/2 , (int)height/2});
                    state = explore3;
                    break;
                case explore3 : 
                    newDistinationInit(maze, desiredPosition);
                    state = explore4;
                    break;
                case explore4 :
                    newDistinationInit(maze, {width-1, 0});
                    state = explore5;
                    break;
                case explore5 :
                    newDistinationInit(maze, {width-1, height-1});
                    state = explore6;
                    break;
                case explore6 :
                    newDistinationInit(maze, desiredPosition);
                    state = explore7;
                    break;
                case explore7 :
                 
                 
                    break;
                case start :
                    setDestination(desiredPosition, maze);
                    makeFullFloodedDestination(maze);
                    state = finalRun;
                    break;
                case finalRun:
                    state = end;
                    break;

                
            };
        }
        setFloodMaze(maze);
        

        test = 0;
        // std::vector<Position> neighbors = getNeighbors(currentPosition);
        // std::vector<Position> PossibleNeighbors;
        // uint8_t minDistance = height*2; 
        // uint8_t minIndex;
        // for (auto index=neighbors.begin(); index <= neighbors.end(); index++) {
        //     if (possiblePosition(currentPosition, *(index), maze)) {
        //         if (minDistance > maze.FloodMaze()[(index->x)][(index->y)]) {
        //             minDistance = maze.FloodMaze()[(index->x)][(index->y)];
        //             minIndex = index - neighbors.begin();
        //         }
        //     }
        // }
        maze.ShowMaze(1);
        Position minPostion = move(maze);
        switch (currentDirection) {
            case leftDir : 
                    if (currentPosition.x > minPostion.x) {
                        
                    } else if (currentPosition.x < minPostion.x) {
                        API::turnRight();
                        API::turnRight();
                        updatedDirection(currentDirection, -1);}
                    else if (currentPosition.y > minPostion.y) {
                        API::turnLeft();
                        updatedDirection(currentDirection, leftDir);
                    } else if (currentPosition.y < minPostion.y){
                        API::turnRight();
                        updatedDirection(currentDirection, rightDir);
                }   
                break;
            case rightDir : 
                if (currentPosition.x > minPostion.x) {
                        API::turnRight();
                        API::turnRight();
                        updatedDirection(currentDirection, -1);
                    } else if (currentPosition.x < minPostion.x) {
                        
                    } else if (currentPosition.y < minPostion.y) {
                        API::turnLeft();
                        updatedDirection(currentDirection, leftDir);
                    } else if (currentPosition.y > minPostion.y){
                        API::turnRight();
                        updatedDirection(currentDirection, rightDir);
                }  
                break;
            case upDir : 
                if (currentPosition.x > minPostion.x) {
                        API::turnLeft();
                        updatedDirection(currentDirection, leftDir);
                    } else if (currentPosition.x < minPostion.x) {
                        API::turnRight();
                        updatedDirection(currentDirection, rightDir);
                    } else if (currentPosition.y > minPostion.y) {
                        API::turnRight();
                        API::turnRight();
                        updatedDirection(currentDirection, -1);
                    } else if (currentPosition.y < minPostion.y){
                        
                }  
                break;
            case downDir : 
                if (currentPosition.x < minPostion.x) {
                        API::turnLeft();
                        updatedDirection(currentDirection, leftDir);
                    } else if (currentPosition.x > minPostion.x) {
                        API::turnRight();
                        updatedDirection(currentDirection, rightDir);
                    } else if (currentPosition.y < minPostion.y) {
                        API::turnRight();
                        API::turnRight();
                        updatedDirection(currentDirection, -1);
                    } else if (currentPosition.y > minPostion.y){
                        
                }   
                break;
        }
        API::moveForward();
        // for (Position neighbor: neighbors){
        //     // std::cerr << "( " << neighbor.x << ", " << neighbor.y << " ) " <<  possiblePosition(currentPosition, neighbor, maze) << std::endl; 
        //     possiblePosition(currentPosition, neighbor, maze);
        // }
        // if (!API::wallLeft()) {
        //     API::turnLeft();
        //     updatedDirection(currentDirection, leftDir);
        // }
        // while (API::wallFront()) {
        //     test ++;
        //     API::turnRight();

        // }
        // if (test == 1) {
        //     updatedDirection(currentDirection, rightDir);
        // } else if (test == 2) {
        //     updatedDirection(currentDirection, -1);
        // }
        
        // API::moveForward();
        PrevPosition = currentPosition;
        updatePostition(&currentPosition, currentDirection);
    }
}
