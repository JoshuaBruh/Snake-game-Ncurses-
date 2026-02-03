#include "WindowManager.hpp"



WINDOW * WindowManager::build_win(int board_y, int board_x){
    clear();
    refresh();
    getmaxyx(stdscr, this->yMax, this->xMax);

    int win_y = min(board_y, yMax-2);
    int win_x = min(board_x, xMax-2);// solo per evitare che in terminali troppo piccoli non appaia la window

    WINDOW * win = newwin (win_y, win_x, (yMax/2)-(win_y/2), (xMax/2)-(win_x/2));
    box (win, 0, 0);
    wrefresh(win);
    return win;
}


void WindowManager::delete_win(WINDOW * &win){
    if (win != nullptr){
        delwin(win);
        win = nullptr;
    }
}


void WindowManager::reload_win(WINDOW * win){
    if (win != nullptr){
        wclear(win);
        box(win, 0 ,0);
        wrefresh(win);
    }
} 



WINDOW * WindowManager::popup_win(int board_y, int board_x){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);


    int win_y = min(board_y, yMax-2);
    int win_x = min(board_x, xMax-2);



    WINDOW * popup_win = newwin (win_y, win_x, (yMax/2)-(win_y/2), (xMax/2)-(win_x/2));
    box (popup_win, 0, 0);
    wrefresh(popup_win);
    return popup_win;

}

void WindowManager::close_popup(WINDOW * &popup){
    if (popup != nullptr) {
            delwin(popup);    // elimina la finestra popup
            popup = nullptr;  // opzionale, evita dangling pointer
        }
}
