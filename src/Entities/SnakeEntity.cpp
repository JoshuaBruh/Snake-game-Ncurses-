#include "SnakeEntity.hpp"

Entity::Entity(){
    y = 0;
    x = 0;
    EntRep = ' ';
}

Entity::Entity(int y, int x, chtype ch){
    this->y = y;
    this->x = x;
    this->EntRep = ch;
}

int Entity::getx(){
    return x;
}

int Entity::gety(){
    return y;
}

chtype Entity::getEnt(){
    return EntRep;
}
    
void Entity::setY(int newY){
    this->y = newY;
}

void Entity::setX(int newX){
    this->x = newX;
}