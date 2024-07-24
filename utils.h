#include<iostream>
#include <vector>
#include "API.h"
#include <stack>
#include <queue>
#include <cstdint>



#ifndef UTILS_H_
#define UTILS_H_
inline int currentDirection; // determined first;


inline int test;

struct Position {
    int x;
    int y;
};


inline Position currentPosition = {0, 0};
inline Position PrevPosition = {0, 0};
inline std::queue<Position> unexploredCells;
inline Position desiredPosition;
inline int height, width;


enum states {
    firstRun,
    explore1,
    explore2,
    explore3,
    explore4,
    explore5,
    explore6,
    explore7,
    finalRun,
    start,
    end
};




enum wallsConfig {
    left = 1,
    right,
    top,
    bottom,
    leftOpen,
    rightOpen,
    topOpen,
    bottomOpen,
    leftTopCorner,
    leftBottomCorner,
    rightTopCorner,
    rightBottomCorner,
    leftRight,
    topBottom,
    empty,
    full,
};

class Maze {
    private: 
        int width;
        int height;
        int xDesire;
        int yDesire;
        std::vector<std::vector<int>> floodMaze;
        std::vector<std::vector<int>> wallMaze;  
    public: 
        Maze();
        Maze(const int &width, const int &height, const int &xDesire, const int &yDesire);
        void MazeInit(const bool &isFlood);
        void WallsInit();
        void FloodInit();
        void ShowMaze(const int &config);
        std::vector<std::vector<int>> FloodMaze();
        std::vector<std::vector<int>> WallMaze();
        void updateWallMaze(Position coord, int value);
        void updateFloodMaze(Position coord, int value);
        std::vector<int> getInfo();
        
};


enum Directions {
    upDir= 1,
    rightDir,
    leftDir,
    downDir,
};

void setup();

int updatedDirection(int &currentDirection, int newDirection);


Position updatePostition(Position *currentPosition, int prevDirection);

std::string mapDirection(int direction);

void setFloodMaze(Maze &maze);
void setWallMaze(Maze &maze);

std::vector<int> wallRead();
int wallUpdate(std::vector<int> direction, int currentDirection,  Position coord, Maze &maze);
void drawWall(int wallState, Position coord);

std::vector<Position> getNeighbors(Position coord);
bool possiblePosition(Position currentPosition, Position desirePosition, Maze &maze);
bool couldFlood(std::vector<Position> possibleNeighbors, Maze &maze, Position currentCell);
void makeFlooded(std::vector<Position> possibleNeighbors, Maze &maze, Position currentCell);
void FloodFill(Position currentCell, Maze &maze);

void print_queue(std::stack<Position> q);


void makeFullFloodedDestination(Maze &maze);
// void makeFullFlooded(Maze &maze);
void newDistinationInit(Maze &maze, Position destination);
void setDestination(Position destination, Maze &maze);
Position move(Maze &maze);


#endif