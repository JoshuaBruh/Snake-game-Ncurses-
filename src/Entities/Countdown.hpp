#include"../Manager/WindowManager.hpp"
#include <chrono>



class Countdown{
    private:
    int board_x;
    std::chrono::steady_clock::time_point start_time;
    int duration_sec;
    WindowManager wmng;
    public:
    WINDOW * Ctwin;


        Countdown(){}
        Countdown(int board_x, int y, int x);
        ~Countdown();
        void Initialize(int Time);
        void UpdateTimer();
        void TimerClear();
        void TimerRefresh();
        int GetRemainingTime();
};