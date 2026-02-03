#pragma once
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iomanip>
using namespace std;

class WindowManager{
    private:
        int board_y, board_x;
    public:
        WindowManager(){}
        int yMax, xMax;

        WINDOW * build_win(int board_y, int board_x);
        void delete_win(WINDOW * &win);
        void reload_win(WINDOW * win);
        WINDOW * popup_win(int board_y, int board_x);
        void close_popup(WINDOW * &win);
};


