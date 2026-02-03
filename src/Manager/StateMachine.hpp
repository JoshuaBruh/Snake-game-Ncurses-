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
        char currentstate;
        
    public:
        //enum class GameState {MENU, PLAY, PAUSE, GAMEOVER, EXIT}; //set di valori definiti a priori (in questo caso stati)
        //GameState currentstate;
        StateMachine(int board_y, int board_x);




    void RunSelected();
    bool isGameOver();
    void initColors();
};