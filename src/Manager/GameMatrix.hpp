#include "WindowManager.hpp"
#include "../Entities/SnakeEntity.hpp"
#include "../Entities/Apple.hpp"
class GameMatrix{
    private:
        int board_y, board_x;
    public:
        bool** Matrix; //da StackOverflow:
        //you can use an array of pointers to arrays to allow 2D syntax like contiguous 2D arrays, even though it's not an efficient single large allocation. You can initialize it using a loop.
        GameMatrix (int board_y, int board_x);
        ~GameMatrix();


        void build_Matrix();
        void GetEmpty(int &y, int &x);
        void setOccupied(Entity ent);
        void setEmpty(int y, int x);
        
};