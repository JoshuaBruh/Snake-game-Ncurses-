#include "StateMachine.hpp"

StateMachine::StateMachine(int board_y, int board_x) : board_y(board_y), board_x(board_x),
                                                       SnakeMenu(board_y, board_x),
                                                       SnakePlay(board_y, board_x),
                                                       SnakePause(board_y, board_x)
                                                       {
                                                       //currentstate(GameState::MENU){
                                                            initColors();
                                                            currentstate='M';
                                                       }









void StateMachine::initColors(){
    if (!has_colors()) return; 
    start_color();
    if (can_change_color()){
        init_color(8, 1000, 500, 0); //Orange
        init_color(9, 466, 0, 0); //Dark Red
        init_color(10, 840, 680, 200); //Gold
        init_pair(6, 8, COLOR_BLACK);
        init_pair(7, 9, COLOR_BLACK);
        init_pair(8, 10, COLOR_BLACK);
    }
    else{
        init_pair(6, COLOR_YELLOW, COLOR_BLACK); 
        init_pair(7, COLOR_RED, COLOR_BLACK);
        init_pair(8, COLOR_BLACK, COLOR_YELLOW);
    }

   init_pair(1, COLOR_RED, COLOR_BLACK);
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
   init_pair(3, COLOR_CYAN, COLOR_BLACK);
   init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
   init_pair(5, COLOR_YELLOW, COLOR_BLACK);
}

void StateMachine::RunSelected(){
    switch (currentstate){


        case 'M': //GameState::MENU:
            SnakeMenu.update_menu();

            if(SnakeMenu.PressedExit){
                SnakeMenu.PressedExit = false;
                currentstate = 'E';//GameState::EXIT;
            }
            else{
                currentstate = 'G';//GameState::PLAY;
            }
            
            break;



        case 'G': //GameState::PLAY:
            SnakePlay.GameLoop();
            if (SnakePlay.game_over){
                currentstate = 'M';//GameState::MENU;
                SnakePlay.game_over = false;
            }
            else if(SnakePlay.PressedPause){
                SnakePause.LvlChosen = SnakePlay.GetCurrLv();
                SnakePlay.PressedPause = false;
                currentstate = 'P';//GameState::PAUSE;
            }
            else{
                currentstate = 'E';//GameState::EXIT;
            }
            break;



        case 'P': //GameState::PAUSE:
            SnakePause.update_menu();
            if (SnakePause.PressedResume){
                SnakePlay.LevelToSet = SnakePause.LvlChosen;
                SnakePause.PressedResume = false;
                currentstate = 'G';//GameState::PLAY;
            }
            else if (SnakePause.PressedMenu){
                SnakePause.PressedMenu = false;
                SnakePlay.game_over = true;
                SnakePlay.exitfrommenu = true;
                currentstate = 'G';//GameState::PLAY;
            }
            break;

        case 'E'://GameState::EXIT:
            break;
    }
}


bool StateMachine::isGameOver(){
    return (currentstate == 'E');//GameState::EXIT
}