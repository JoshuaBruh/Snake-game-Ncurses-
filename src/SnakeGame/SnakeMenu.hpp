#pragma once
#include "../Manager/WindowManager.hpp"
using namespace std;


#define list_obj 4

struct List{
    char name[15];
    bool selected;
};



class Menu{
    protected:
        WINDOW * win;
        int board_y, board_x;
        int index;
        WindowManager wmng;
        
    public:
        List menus[list_obj]{
            {"Play", true},
            {"HighScores", false},
            {"Game Rules", false},
            {"Exit", false},
        };

        bool PressedExit = false;
        Menu(){}

        
        Menu(int board_y, int board_x);

        void print_menu();
        void update_menu();
        void high_scores();
        void rules();
        void selectNextItem();
        void selectPrevItem();
        virtual void run_selected(int index, bool &ExitLoop);
};