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
        //enum Direction {UP = -1, DOWN = +1, LEFT = -2, RIGHT =+2};

        struct Direction{
            static const int UP = -1;
            static const int DOWN = +1;
            static const int LEFT = -2;
            static const int RIGHT = +2;
        };
        int curr;
        //Direction curr;
        Snake(int StartY, int StartX, int board_y, int board_x);
        ~Snake();


        int GetDirection();
        void SetDirection(int  d);
        void SnakeMove(int newHeadY, int newHeadX);
        void ResetPosition(int startY, int startX);
    
};