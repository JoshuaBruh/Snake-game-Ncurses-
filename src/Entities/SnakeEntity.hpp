#pragma once
#include "../Manager/WindowManager.hpp"
class Entity{
    protected:
        int y, x;
        chtype EntRep;//Entity Representation, ogni Entità nel gioco avrà la sua rappresentazione
    public:
        Entity();
        Entity(int y, int x, chtype ch);
        int getx();
        int gety();
        void setY(int newY);
        void setX(int newX);
        chtype getEnt();
};