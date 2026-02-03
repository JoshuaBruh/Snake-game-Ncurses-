#pragma once
#include "../SnakeGame/SnakeMenu.hpp"
#include "../SnakeGame/SnakePlay.hpp"
#include "../SnakeGame/SnakePause.hpp"

class StateMachine{
        WindowManager wmng;
        int board_y, board_x;
        Menu SnakeMenu;
        Play SnakePlay;
        Pause SnakePause;
        Countdown Timer;
        
    public:
        enum class GameState {MENU, PLAY, PAUSE, GAMEOVER, EXIT}; //set di valori definiti a priori (in questo caso stati)
        GameState currentstate;
        StateMachine(int board_y, int board_x);
        //Lista di inizializzazione, quando costruisco Gamestate costruisco istantaneamente anche board_y,
        //board_x, SnakeMenu e currentstate




    void RunSelected();
    bool isGameOver();
    void initColors();
};