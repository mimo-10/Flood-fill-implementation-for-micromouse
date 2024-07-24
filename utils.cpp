#include <iostream>
#include <iomanip> 
#include <algorithm>
#include <queue>
#include <stack>
#include "utils.h"

#define defaultHeight 16
#define defaultWidth 16
#define defaultX 7
#define defaultY 8





void setup() {
    Maze maze;
    maze.MazeInit(false);
    maze.MazeInit(true);
    maze.ShowMaze(2);
}


/// Done (sim)
void Show(std::vector<std::vector<int>> maze, const int height, const int width) {
    for(int8_t j = height-1; j>=0; j--){
        std::cerr << "|";
        for(int8_t i = 0; i<width; i++){
            // std::cerr << "-";
            std::cerr << std::setw(3) << maze[i][j];
            // printf("%2d", maze[j][i]);
            std::cerr << "-";
        }
        std::cerr << "|" << std::endl;
        // printf("\n");
    }
}

Maze::Maze(const int &width = defaultWidth, const int &height = defaultHeight, const int &xDesire=defaultX, const int &yDesir=defaultY): width(width), height(height), xDesire(xDesire), yDesire(yDesire) {
    std::cout << "Maze created" << std::endl;
}

Maze::Maze(): width(defaultWidth), height(defaultHeight), xDesire(desiredPosition.x), yDesire(desiredPosition.y) {
    std::cout << "Maze created" << std::endl;
}


/// Correct
void Maze::WallsInit() {
    wallMaze = std::vector<std::vector<int>> (height, std::vector<int> (width));
    for(int8_t j = 0; j<height; j++){
        for(int8_t i = 0; i<width; i++){
        wallMaze[j][i] = empty;
        if(i==0){
            wallMaze[j][i] = top;
        }
        if(j==0){
            wallMaze[j][i] = left;
        }
        if(j==(height-1)){
            wallMaze[j][i] = right;
        }
        if(i==(width-1)){
            wallMaze[j][i] = bottom;
        }
        wallMaze[0][0] = leftBottomCorner;
        wallMaze[height-1][0] = rightBottomCorner;
        wallMaze[0][width-1] = leftTopCorner;
        wallMaze[width-1][height-1] = rightTopCorner;
        }
    }
    // Show(wallMaze, height, width);
}

// Done
std::vector<int> Maze::getInfo() {
    return {width, height, xDesire, yDesire};
}


// Correct 
void Maze::FloodInit() {
    floodMaze = std::vector<std::vector<int>> (height, std::vector<int> (width));
    for(int8_t k = 0; k<=std::max({ desiredPosition.y, height - desiredPosition.y}) + std::max({desiredPosition.x, width - desiredPosition.x}); k++){
        for(int8_t j = 0; j<height; j++){
            for(int i = 0; i<width; i++){ 
                if (j+i == k && ((j + desiredPosition.y) <= height || (i + desiredPosition.x) <= width || (desiredPosition.y - j) >= 0 || (desiredPosition.x - i) >= 0)){
                    if (desiredPosition.x + i < width) {
                        if (desiredPosition.y + j <= height ) {
                            floodMaze[i+desiredPosition.x][j+desiredPosition.y] = k;
                        } 
                        if (desiredPosition.y - j >= 0) {
                            floodMaze[desiredPosition.x+i][desiredPosition.y-j] = k;
                        }
                    } 
                    if (desiredPosition.x - i >= 0) {
                        if (desiredPosition.y - j >= 0) {
                            floodMaze[desiredPosition.x-i][desiredPosition.y-j] = k;
                        } 
                        if (desiredPosition.y + j <= height) {
                            floodMaze[desiredPosition.x-i][desiredPosition.y+j] = k;
                        }
                    }   
                } 
            }
        }
    }
    // Show(floodMaze, height, width);
}


// Done (sim)
void Maze::ShowMaze(const int &config) {
    switch (config) {
        case 0 :
            std::cerr << "Wall data : " << std::endl;
            Show(wallMaze, height, width);
            break;
        case 1 : 
            std::cerr << "Flood data : " << std::endl;
            Show(floodMaze, height, width);
            break;
        case 2 : 
            std::cerr << "Wall data : " << std::endl;
            Show(wallMaze, height, width);
            std::cerr << "Flood data : " << std::endl;
            Show(floodMaze, height, width);
            break;
    }
}


/// Done
void Maze::MazeInit(const bool &isFlood) {
    !isFlood ?
    this->WallsInit() : 
    this->FloodInit(); 
    std::cerr << "Maze Filled" << std::endl;
}

// Correct
int updatedDirection(int &currentDirection, int newDirection) {
    switch (newDirection) {
        case rightDir: 
            if (currentDirection == rightDir) {
                currentDirection = downDir;
            } else if (currentDirection == leftDir) {
                currentDirection = upDir;
            } else if (currentDirection == upDir) {
                currentDirection = rightDir;
            } else {
                currentDirection = leftDir;
            }
            break;
        case leftDir: 
            if (currentDirection == rightDir) {
                currentDirection = upDir;
            } else if (currentDirection == leftDir) {
                currentDirection = downDir;
            } else if (currentDirection == upDir) {
                currentDirection = leftDir;
            } else {
                currentDirection = rightDir;
            }
            break;
        default : 
            switch (currentDirection) {
                case rightDir: 
                    currentDirection = leftDir;
                    break;
                case leftDir: 
                    currentDirection = rightDir;
                    break;
                case downDir: 
                    currentDirection = upDir;
                    break;
                case upDir: 
                    currentDirection = downDir;
                    break;
            }
            break;
    }
    return currentDirection;
}


// Correct
Position updatePostition(Position *currentPosition, int prevDirection) {
    switch (prevDirection) {
        case rightDir: 
            currentPosition->x += 1;
            break;
        case leftDir: 
            currentPosition->x -= 1;
            break;
        case upDir: 
            currentPosition->y += 1;
            break;
        case downDir: 
            currentPosition->y -= 1;
            break;
    }
    return *currentPosition;
}

// Correct (sim)
std::string mapDirection(int direction) {
    std::string mappedDir;
    switch (direction) {
        case rightDir: 
            mappedDir = "Right";
            break;
        case leftDir: 
            mappedDir = "Left";
            break;
        case upDir: 
            mappedDir = "Up";
            break;
        case downDir: 
            mappedDir = "Down";
            break;
    }
    return mappedDir;
}



// Done 
std::vector<std::vector<int>> Maze::FloodMaze(){
    return floodMaze;
};


// Done
std::vector<std::vector<int>> Maze::WallMaze(){
    return wallMaze;
};


// Done (sim) useless
void setFloodMaze(Maze &maze) {
    std::vector<std::vector<int>> floodMaze = maze.FloodMaze();
    for(int y = 0; y<floodMaze.size(); y++){
        for(int x = 0; x<floodMaze[0].size(); x++){ 
            API::setText(x, y, std::to_string(floodMaze[x][y]));
        }
    }
}



// maybe correct
int wallUpdate(std::vector<int> direction, int currentDirection,  Position coord, Maze &maze) {
    int wall;

    if (!direction[0] && direction[1] && direction[2] && (currentDirection == leftDir)) {
        wall = leftTopCorner;
    } else if (direction[0] && !direction[1] && direction[2] && (currentDirection == rightDir)) {
        wall = rightTopCorner;
    } else if (direction[0] && !direction[1] && direction[2] && (currentDirection == upDir)) {
        wall = leftTopCorner;
    } else if (!direction[0] && direction[1] && direction[2] && (currentDirection == upDir)) {
        wall = rightTopCorner;
    } else if (direction[0] && !direction[1] && direction[2] && (currentDirection == leftDir)) {
        wall = leftBottomCorner;
    } else if (!direction[0] && direction[1] && direction[2] && (currentDirection == rightDir)) {
        wall = rightBottomCorner;
    } else if (direction[0] && !direction[1] && direction[2] && (currentDirection == downDir)) {
        wall = rightBottomCorner;
    } else if (!direction[0] && direction[1] && direction[2] && (currentDirection == downDir)) {
        wall = leftBottomCorner;
    } else if (direction[0] && direction[1] && !direction[2] && ((currentDirection == downDir) || (currentDirection == upDir))) {
        wall = leftRight;
    } else if (direction[0] && direction[1] && !direction[2] && ((currentDirection == rightDir) || (currentDirection == leftDir))) {
        wall = topBottom;
    } else if (!direction[0] && !direction[1] && direction[2] && (currentDirection == upDir)) {
        wall = top;
    } else if (!direction[0] && !direction[1] && direction[2] && (currentDirection == leftDir)) {
        wall = left;
    } else if (!direction[0] && !direction[1] && direction[2] && (currentDirection == rightDir)) {
        wall = right;
    } else if (!direction[0] && !direction[1] && direction[2] && (currentDirection == downDir)) {
        wall = bottom;
    } else if (direction[0] && !direction[1] && !direction[2] && (currentDirection == downDir)) {
        wall = right;
    } else if (direction[0] && !direction[1] && !direction[2] && (currentDirection == upDir)) {
        wall = left;
    } else if (!direction[0] && direction[1] && !direction[2] && (currentDirection == leftDir)) {
        wall = top;
    } else if (!direction[0] && direction[1] && !direction[2] && (currentDirection == rightDir)) {
        wall = bottom;
    } else if (direction[0] && !direction[1] && !direction[2] && (currentDirection == leftDir)) {
        wall = bottom;
    } else if (direction[0] && !direction[1] && !direction[2] && (currentDirection == rightDir)) {
        wall = top;
    } else if (!direction[0] && direction[1] && !direction[2] && (currentDirection == downDir)) {
        wall = left;
    } else if (!direction[0] && direction[1] && !direction[2] && (currentDirection == upDir)) {
        wall = right;
    } else if (direction[0] && direction[1] && direction[2] && ((currentDirection == upDir))) {
        wall = bottomOpen;
    } else if (direction[0] && direction[1] && direction[2] && ((currentDirection == downDir))) {
        wall = topOpen;
    } else if (direction[0] && direction[1] && direction[2] && ((currentDirection == rightDir))) {
        wall = leftOpen;
    } else if (direction[0] && direction[1] && direction[2] && ((currentDirection == leftDir))) {
        wall = rightOpen;
    };
    
    maze.updateWallMaze(coord, wall);
    drawWall(wall, coord);
    // maze.ShowMaze(0);
    return wall;
}


// needs update
std::vector<int> wallRead () {
    // updated based on 3 main ir sensors
    std::vector<int> walls = {API::wallLeft(), API::wallRight(), API::wallFront()};
    return  walls;
}


// Done
void Maze::updateWallMaze(Position coord, int value){
    wallMaze[coord.x][coord.y] = value;
}

// Done

void Maze::updateFloodMaze(Position coord, int value){
    floodMaze[coord.x][coord.y] = value;
}



// Done (sim)
void setWallMaze(Maze &maze) {
    std::vector<std::vector<int>> wallMaze = maze.WallMaze();
    for(int y = 0; y<wallMaze.size(); y++){
        for(int x = 0; x<wallMaze[0].size(); x++){ 
            API::setWall(x, y, 'c');
        }
    }
}


/// corrrect (sim)
void drawWall(int wallState, Position coord) {
    std::string wallSting;
    std::string l = "w";
    std::string r = "e";
    std::string b = "s";
    std::string t = "n";
    switch (wallState) {
        case left:
            wallSting = l;
            break;
        case right:
            wallSting = r;
            break;
        case bottom: 
            wallSting = b;
            break;
        case top:
            wallSting = t;
            break;
        case rightOpen:
            wallSting = b+l+t;
            break;
        case bottomOpen: 
            wallSting = t+l+r;
            break;
        case topOpen:
            wallSting = b+r+l;
            break;
        case leftOpen:
            wallSting = r+b+t;
            break;
        case rightBottomCorner:
            wallSting = r+b;
            break;
        case leftBottomCorner: 
            wallSting = b+l;
            break;
        case rightTopCorner:
            wallSting = r+t;
            break;
        case leftTopCorner:
            wallSting = l+t;
            break;
        case leftRight: 
            wallSting = l+r;
            break;
        case topBottom:
            wallSting = t+b;
            break;
        
    }
    for (char c : wallSting) {
        
        API::setWall(coord.x, coord.y, c);
    }
}


/// correct 
std::vector<Position> getNeighbors(Position coord) {
    std::vector<Position> neighbors;
    for(int8_t j = 1; j >= -1; j-- ) {
         for(int8_t i = 1; i >= -1; i-- ){
            if (std::abs(j+i) ==  1) {
                if (coord.x+i >=0 && coord.y+j >=0 && coord.x+i < width && coord.y+j < height ) {
                    Position neighbor;
                    neighbor.x = coord.x+i;
                    neighbor.y = coord.y+j;
                    neighbors.push_back(neighbor);
                }
            }
        }
    }
    
    return neighbors; /// top - right - left - bottom
}


/// correct 
bool possiblePosition(Position currentPosition, Position desirePosition, Maze &maze) {
    int currentWalls = maze.WallMaze()[currentPosition.x][currentPosition.y];
    
    std::vector<int> wallsRight = {right, rightTopCorner, rightBottomCorner, leftRight, leftOpen, topOpen, bottomOpen};
    std::vector<int> wallsLeft = {left, leftBottomCorner, leftTopCorner, leftRight, rightOpen, topOpen, bottomOpen};
    std::vector<int> wallsUp = {top, topBottom, rightTopCorner, leftTopCorner, leftOpen, rightOpen, bottomOpen};
    std::vector<int> wallsDown = {bottom, topBottom, rightBottomCorner, leftBottomCorner, topOpen, rightOpen,leftOpen};

    bool isPossible;

    if (currentPosition.x == desirePosition.x) {
        if (currentPosition.y > desirePosition.y) {
            if (count(wallsDown.begin(), wallsDown.end(), currentWalls)) {
                isPossible= false;
            } else {    
                isPossible = true;
            }
        } else {
            if (count(wallsUp.begin(), wallsUp.end(), currentWalls)) {
                isPossible= false;
            } else {    
                isPossible = true;
            }
        }
    }

    if (currentPosition.y == desirePosition.y) {
        if (currentPosition.x > desirePosition.x) {
            if (count(wallsLeft.begin(), wallsLeft.end(), currentWalls)) {
                isPossible = false; 
            } else {
                isPossible = true;
            }
        } else {
            if (count(wallsRight.begin(), wallsRight.end(), currentWalls)) {
                isPossible = false; 
            } else {
                isPossible = true;
            }
        }
    }
   
    return isPossible;
}

// Correct 
void setDestination(Position destination, Maze &maze) {
    for (int x = 0; x < height; x++) {
        for (int y= 0; y <width; y++) {
            if (x == destination.x && y ==destination.y) {
                maze.updateFloodMaze({x, y}, 0);
            } else {
                maze.updateFloodMaze({x, y}, height*width);
            }
        }
    }

    unexploredCells.push(destination);

}



/// Correct

void newDistinationInit(Maze &maze, Position destination) {
    setDestination(destination, maze);
    while (!unexploredCells.empty()) {
        Position cell = unexploredCells.front();
        unexploredCells.pop();
        std::vector<Position> neighbors = getNeighbors(cell);

        for (Position neighbor : neighbors) {
            if (maze.FloodMaze()[neighbor.x][neighbor.y] == height*width) {
                maze.updateFloodMaze(neighbor, maze.FloodMaze()[cell.x][cell.y] + 1);
                unexploredCells.push(neighbor); 
            }
        }
        // delete(neighbors);
    }
}

/// needs test
// void makeFullFlooded(Maze &maze) {
//     for (int x = 0; x < height; x++) {
//         for (int y= 0; y <width; y++) {
//             if (x == desiredPosition.x && y == desiredPosition.y) {
//                 maze.updateFloodMaze({x, y}, 0); /// 1
//             } else {
//                 maze.updateFloodMaze({x, y}, 0);
//             }
//         }
//     }
    
//     unexploredCells.push({desiredPosition.x, desiredPosition.y});

//     while (!unexploredCells.empty()) {
//         Position cell = unexploredCells.front();
//         unexploredCells.pop();
//         std::vector<Position> neighbors = getNeighbors(cell);

//         for (Position neighbor : neighbors) {
//             if (maze.WallMaze()[neighbor.x][neighbor.y] != empty) {
//                 if (maze.FloodMaze()[neighbor.x][neighbor.y] == 0) {
//                     if (possiblePosition(cell, neighbor, maze)) {
//                         maze.updateFloodMaze(neighbor, maze.FloodMaze()[cell.x][cell.y] + 1);
//                         unexploredCells.push(neighbor); 
//                     }
//                 }
//             }
//         }
//         // delete(neighbors);
//     }
// }


// correct
void makeFullFloodedDestination(Maze &maze ) {
    
    // setDestination({ desiredPosition.x,  desiredPosition.y}, maze);
    while (!unexploredCells.empty()) {
        Position cell = unexploredCells.front();
        unexploredCells.pop();
        std::vector<Position> neighbors = getNeighbors(cell);

        for (Position neighbor : neighbors) {
            if (maze.FloodMaze()[neighbor.x][neighbor.y] == 256) { // update
                if (possiblePosition(cell, neighbor, maze)) {
                        maze.updateFloodMaze(neighbor, maze.FloodMaze()[cell.x][cell.y] + 1);
                        unexploredCells.push(neighbor); 
                    }
            }
        }
        // delete(neighbors);
    }
}

// correct
bool couldFlood(std::vector<Position> possibleNeighbors, Maze &maze, Position currentCell) {
    int currentDistance = maze.FloodMaze()[currentCell.x][currentCell.y];
    bool CFlood;
    std::vector<int> FloodDistance;
    for (Position neighbor : possibleNeighbors) {
        FloodDistance.push_back(maze.FloodMaze()[neighbor.x][neighbor.y]);
    }
    // std::cerr << "lll( " << *(std::min_element(FloodDistance.begin(), FloodDistance.end())) << ", " << currentCell.x << " ," << currentCell.y << " ) " << std::endl; 
    if (*(std::min_element(FloodDistance.begin(), FloodDistance.end())) == currentDistance + 1) {
        CFlood = false;
    } else {
        CFlood = true;
    }

    return CFlood;
}


// correct
void makeFlooded(std::vector<Position> possibleNeighbors, Maze &maze, Position currentCell) {
    std::vector<int> FloodDistance;
    for (Position neighbor : possibleNeighbors) {
        FloodDistance.push_back(maze.FloodMaze()[neighbor.x][neighbor.y]);
    }
    maze.updateFloodMaze(currentCell,  *(std::min_element(FloodDistance.begin(), FloodDistance.end())) + 1);
}


// correct
void FloodFill(Position currentCell, Maze &maze) {
    // std::queue<Position> unexploredCells;

    unexploredCells.push(currentCell);
    // std::vector<Position> neighborsCurrent = getNeighbors(currentCell, height, width);
    //     std::vector<Position> possibleNeighborsCurrent;
    //     for (Position neighbor : neighborsCurrent) {
    //         if (possiblePosition(currentCell, neighbor, maze)) {
    //             unexploredCells.push(neighbor);
    //             possibleNeighborsCurrent.push_back(neighbor);};
    //     }
    //  if (!couldFlood(possibleNeighborsCurrent, maze, currentCell)) {
    //         maze.updateFloodMaze(currentCell, maze.FloodMaze()[PrevPosition.x][PrevPosition.y] + 1);
    //     } 
    
    while (!unexploredCells.empty()) {
        Position cell = unexploredCells.front();
        unexploredCells.pop();
        std::vector<Position> neighbors = getNeighbors(cell);
        std::vector<Position> possibleNeighbors;
        for (Position neighbor : neighbors) {
            // std::cerr << "ggg( " << neighbor.x << ", " << neighbor.y << " ) " << std::endl; 
            if (possiblePosition(cell, neighbor, maze)) possibleNeighbors.push_back(neighbor);
        }
        // delete(neighbors);
        
        // print_queue(unexploredCells);
        if (!couldFlood(possibleNeighbors, maze, cell)) {
            makeFlooded(possibleNeighbors, maze, cell);
            
            for (Position neighbor : possibleNeighbors) {
                unexploredCells.push(neighbor);
            }
            // print_queue(unexploredCells);
        }  
    }
}

void print_queue(std::stack<Position> q)
{
  while (!q.empty())
  {
    std::cerr << q.top().x << " ,,,,, " << q.top().y << " ";
    q.pop();
  }
  std::cout << std::endl;
}


/// Correct

Position move(Maze &maze){ 
    std::vector<Position> neighbors = getNeighbors(currentPosition);
    int prev;
    int maxD = height*width;
    int minVals[4]={maxD,maxD,maxD,maxD};
    for (int i = 0; i<neighbors.size(); i++) {
        if (possiblePosition(currentPosition, neighbors[i], maze)){
            
            if (neighbors[i].x == PrevPosition.x && neighbors[i].y == PrevPosition.y) {
                prev=i;
            }
            minVals[i]= maze.FloodMaze()[neighbors[i].x][neighbors[i].y];
        } 
    }
    int minVal = maxD;
    Position minCell;
    int movNum=0;
    
    
    for (int i=0; i<4;i++){
        if (minVals[i]!= maxD){
            movNum+=1;}
    }
    
    for (int i=0; i<4;i++){
        if (minVals[i]<minVal){
            if (movNum==1){
                minVal= minVals[i];
                minCell= neighbors[i];
                break;
            }
            else{
                if(i!=prev){
                    minVal= minVals[i];
                    minCell= neighbors[i];
                }
            }
        }
    }

    
    return minCell;
}


    


