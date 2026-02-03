#include"../Manager/WindowManager.hpp"


class Scoreboard{
    private:
    int board_x;
    WindowManager wmng;
    public:
    WINDOW * Swin;
        Scoreboard(){}
        Scoreboard(int board_x, int y, int x);
        ~Scoreboard();
        void Initialize(unsigned long long  initScore);
        void UpdateScore(unsigned long long  initScore);
        void ScoreClear();
        void ScoreRefresh();
};