#include "Snake.hpp"


SnakeBody::SnakeBody(int y, int x){
    this->y = y;
    this->x = x;
    this->EntRep = '#' | COLOR_PAIR(2) | A_BOLD;
}

SnakeHead::SnakeHead(int y, int x){
    this->y = y;
    this->x = x;
    this->EntRep = 'o' | COLOR_PAIR(2) | A_BOLD;
}


Snake::Snake(int StartY, int StartX, int board_y, int board_x){
    this->board_y = board_y;
    this->board_x = board_x;
    ResetPosition(StartY, StartX);
}

Snake::~Snake(){}


int Snake::GetDirection(){ //Snake::Direction Snake::GetDirection()
    return this->curr;
}

void Snake::SetDirection(int  d){  //void Snake::SetDirection(Direction d)
    if (this->curr + d != 0){
        this->curr = d;
    }
}





void Snake::SnakeMove(int newHeadY, int newHeadX){ 
    for (int i = SnakeLength -1; i > 0; i--){
        SnakeCoord[i][0] = SnakeCoord[i-1][0];
        SnakeCoord[i][1] = SnakeCoord[i-1][1];
    }

    SnakeCoord[0][0] = newHeadY;
    SnakeCoord[0][1] = newHeadX;

    this->HeadY = newHeadY;
    this->HeadX = newHeadX;
}




void Snake::ResetPosition(int StartY, int StartX){
    this->HeadY = StartY;
    this->HeadX = StartX;
    curr = Direction::RIGHT; //Direction::RIGHT;

    int currY = HeadY;
    int currX = HeadX;
    for(int i = 0; i<SnakeLength; i++){
        SnakeCoord[i][0] = currY;
        SnakeCoord[i][1] = currX;
        if (currY > 1 ){
            currY--;
        }
        else if (currX > 1){
            currX--;
        }
        else{
            currX++;
        }
    }
}
