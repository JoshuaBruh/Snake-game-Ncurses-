#include "SnakeMenu.hpp"


Menu::Menu(int board_y, int board_x){
  this->board_y = board_y;
  this->board_x = board_x;
}

void Menu::print_menu(){

    wmng.reload_win(this->win);

    int yWin,xWin;
    getmaxyx(this->win, yWin, xWin);


    for (int i = 0; i < list_obj; i++){
        string name = menus[i].name;
        if(menus[i].selected){
            wattron(this->win, A_STANDOUT);
            this->index = i;
        }
        mvwprintw(this->win, (yWin/2)-(list_obj/2)+i, (xWin-name.length())/2, name.c_str());
        wattroff(this->win, A_STANDOUT);
        }
    wrefresh(this->win);
}


void Menu::update_menu(){

    this->win = wmng.build_win(this->board_y, this->board_x);
    keypad(win,true);
    bool ExitLoop = false;
    print_menu();
    int ch;
    while (!ExitLoop){
        ch = wgetch(this->win);
        switch (ch){
            case KEY_DOWN:
              selectNextItem();
              break;
            case KEY_UP:
              selectPrevItem();
              break;
            case 10:
              run_selected(this->index, ExitLoop);
              break;              
            default:
              break;
        }
    print_menu();
    }
    wmng.delete_win(this->win);
    clear();
    refresh();
}




void Menu::run_selected(int index, bool &ExitLoop){
    switch(this->index){
        case 0:
          ExitLoop = true;
          break;
        case 1:
          high_scores();
          break;
        case 2:
          rules();
          break;
        case 3:
          this->PressedExit = true;
          ExitLoop = true;
          break;
        default:
          break;
    }
}




void Menu::selectNextItem(){
    if (this->index == list_obj-1){
        menus[this->index].selected = false;
        menus[0].selected = true;
        this->index = 0;
    }
    else{
        menus[this->index].selected = false;
        menus[this->index+1].selected = true;
        this->index = this->index+1;
    }
    return;
}     
void Menu::selectPrevItem(){
    if (index == 0){
        menus[this->index].selected = false;
        menus[list_obj-1].selected = true;
        this->index = list_obj-1;
    }
    else{
        menus[this->index].selected = false;
        menus[this->index-1].selected = true;
        this->index = this->index-1;
    }
    return;
}







void Menu::high_scores(){

    ifstream HighScores("file/High_Scores.txt");

    WINDOW * Hwin = wmng.popup_win(this->board_y-2, 24);
    
    char name[4];
    unsigned long long int score;
    int position = 1;
    int row = 4;


    mvwprintw(Hwin, 2, 4, "Leaderboard");
    while(HighScores >> name >> score){
        mvwprintw(Hwin, row++, 4, "%2d°. %-4s:   %llu", position++, name, score);
    }
    mvwprintw(Hwin, board_y-4, 1, "Press any key to exit");
    HighScores.close();
    wgetch(Hwin);
    wmng.close_popup(Hwin);
    clear();
    refresh();
    return;


}




void Menu::rules(){
    ifstream rules("file/Rules.txt");
    char RuleRow[130];
    
    WINDOW * rule_win = wmng.popup_win(50, 100);
    int row = 2;
    while (rules.getline(RuleRow, sizeof(RuleRow)) && row < 132) {   
        mvwprintw(rule_win, row++, 1, "%s", RuleRow);
    }
    rules.close();
    wgetch(rule_win);
    wmng.close_popup(rule_win);
    clear();
    refresh();
    return;
}


