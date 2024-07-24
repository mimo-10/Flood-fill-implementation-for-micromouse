#include<iostream>
#include<vector>



#define width 16
#define height 16


struct mazeData {
    int flood;
    int walls;
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



int main() {
    std::vector<int> wallsRight = {1, 0, 2, 0, 1, 5, 6};
    std::cout << wallsRight.(0) << std::endl;
    
    std::vector<std::vector<mazeData>> maze(width, std::vector<mazeData> (height));

    // mazeData maze[height][width];
    for(int j = 0; j<height; j++){
    for(int i = 0; i<width; i++){
      maze[j][i].walls = empty;
      if(i==0){
        maze[j][i].walls = left;
      }
      if(j==0){
        maze[j][i].walls = top;
      }
      if(j==(height-1)){
        maze[j][i].walls = bottom;
      }
      if(i==(width-1)){
        maze[j][i].walls = right;
      }
      maze[0][0].walls = leftTopCorner;
      maze[height-1][0].walls = leftBottomCorner;
      maze[0][width-1].walls = rightTopCorner;
      maze[width-1][height-1].walls = rightBottomCorner;
    }
  }
  for(int j = 0; j<height; j++){
    std::cout << "|";
    for(int i = 0; i<width; i++){
      std::cout << "-";
      printf("%2d", maze[j][i].walls);
      std::cout << "-";
    }
    std::cout << "|";
    printf("\n");
  }

    return 0;
}