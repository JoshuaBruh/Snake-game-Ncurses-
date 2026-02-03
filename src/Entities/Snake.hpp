#include "SnakeEntity.hpp"
#define SnakeLength 26
class SnakeBody : public Entity{
    public:
        SnakeBody(int y, int x);
};

class SnakeHead : public Entity{
    public:
        SnakeHead(int y, int x);
};
class Snake : public Entity{
    public:
        int SnakeCoord[SnakeLength][2];  
        int HeadY, HeadX;
        int board_y, board_x;    
        enum Direction {UP = -1, DOWN = +1, LEFT = -2, RIGHT =+2};
        Direction curr;
        Snake(int StartY, int StartX, int board_y, int board_x);
        ~Snake();


        Direction GetDirection();
        void SetDirection(Direction  d);
        void SnakeMove(int newHeadY, int newHeadX);
        void ResetPosition(int startY, int startX);
    
};