#include "Scoreboard.hpp"

Scoreboard::Scoreboard(int board_x, int y, int x){
    this->board_x = board_x;
    this->Swin = newwin(1, board_x, y, x);
}
void Scoreboard::Initialize(unsigned long long int initScore){
    wclear(Swin);
    wattron(Swin, A_BOLD);
    mvwprintw(Swin, 0, 0, "Total Score: ");
    wattroff(Swin, A_BOLD);
    UpdateScore(initScore);

}
void Scoreboard::UpdateScore(unsigned long long int initScore){
    wattron(Swin, A_BOLD);
    mvwprintw(Swin, 0, Swin->_maxx-10, "%11llu", initScore); //if %i the score value would be starting at the 11th char and growing to the right instead of the start and growing to the left
    wattroff(Swin, A_BOLD);
}
void Scoreboard::ScoreClear(){
    wclear(Swin);
}
void Scoreboard::ScoreRefresh(){   
    wnoutrefresh(Swin);
}

Scoreboard::~Scoreboard(){}