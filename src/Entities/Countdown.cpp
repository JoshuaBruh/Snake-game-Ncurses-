#include "Countdown.hpp"

Countdown::Countdown(int board_x, int y, int x){
    this->board_x = board_x;
    Ctwin = newwin(1, board_x, y, x);
}
void Countdown::Initialize(int Time){
    duration_sec = Time;
    start_time = std::chrono::steady_clock::now();
    wclear(Ctwin);
    wattron(Ctwin, A_BOLD);
    mvwprintw(Ctwin, 0, 0, "Remaining time: ");
    wattroff(Ctwin, A_BOLD);

}

int Countdown::GetRemainingTime() {
    auto elapsed = std::chrono::steady_clock::now() - start_time;
    int remaining = duration_sec - std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
    if (remaining > 0) {
        return remaining;
    } 
    else {
    return 0;
    }
}

void Countdown::UpdateTimer(){
    int remaining = GetRemainingTime();
    int mins = remaining / 60;
    int secs = remaining % 60;

    wattron(Ctwin, A_BOLD);
    mvwprintw(Ctwin, 0, board_x - 10, "%02d:%02d", mins, secs);
    wattroff(Ctwin, A_BOLD);
    wrefresh(Ctwin);
}
void Countdown::TimerClear(){
    wclear(Ctwin);
}
void Countdown::TimerRefresh(){
    clearok(Ctwin, true);
    wnoutrefresh(Ctwin);
    clearok(Ctwin, false);
}

Countdown::~Countdown(){}



 
 