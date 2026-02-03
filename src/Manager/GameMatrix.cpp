#include "GameMatrix.hpp"

GameMatrix::GameMatrix (int board_y, int board_x){
    this->board_y = board_y;
    this->board_x = board_x;
    Matrix = new bool*[board_y];
    for (int i = 0; i < board_y; i++){
        Matrix[i] = new bool[board_x];
    }
}

GameMatrix::~GameMatrix(){
    for (int i= 0; i<board_y; i++){
        delete[] Matrix[i];
    }
    delete[] Matrix;
}


void GameMatrix::build_Matrix(){
    for(int i = 0; i<board_y; i++){
        for(int j = 0; j<board_x; j++){
            if((i == 0) || (j == 0) || (i==board_y-1) || (j==board_x-1) ){
                Matrix[i][j] = true;
            }
            else{
                Matrix[i][j] = false;
            }
        }
    }
}

void GameMatrix:: GetEmpty(int &y, int &x){
    bool found = false;
    while (!found){
        y = (rand() % (board_y-2))+1;
        x = (rand() % (board_x-2))+1;
        if(!Matrix[y][x]){
            found = true;
        }
    }
}

void GameMatrix::setOccupied(Entity ent){
    Matrix[ent.gety()][ent.getx()] = true;

}

void GameMatrix::setEmpty(int y, int x){
    Matrix[y][x] = false;
    
}
