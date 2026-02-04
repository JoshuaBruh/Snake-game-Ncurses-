#include "Apple.hpp"


Apple::Apple(int y, int x){
            this->y = y;
            this->x = x;
            this->EntRep = '@' | COLOR_PAIR(1) | A_BOLD;
        }