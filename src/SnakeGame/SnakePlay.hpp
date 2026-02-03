#include "../Manager/WindowManager.hpp"
#include "../Manager/GameMatrix.hpp"
#include "../Manager/SnakeDatabase.hpp"
#include "../Entities/SnakeEntity.hpp"
#include "../Entities/Snake.hpp"
#include "../Entities/Scoreboard.hpp"
#include "../Entities/Countdown.hpp"
#include "SnakeLevels.hpp"
#include "SnakePause.hpp"
class Play{
    private:
        WindowManager wmng;
        int board_y, board_x;
        WINDOW * Gwin;
        Apple * apple;
        GameMatrix GMx;
        Snake Sk;
        Scoreboard Sb;
        Countdown Timer;
        bool initialized = false;
        int Timeremaining;
        Level SkL;
        Database SkD;
        unsigned long long  totalscore = 0;
        int Ybeg, Xbeg;
        WINDOW * LBwin;
        WINDOW * Ctrlwin;
        WINDOW * LVLinfo;

    public:
        Play(int board_y, int board_x);

        ~Play();
        bool game_over;
        bool PressedPause;
        int LevelToSet = -1;
        bool exitfrommenu = false;


        
        void GameLoop();
        void UserI();
        void Update(int y, int x);
        bool GameOver();


        void delEnt(WINDOW * win, int y, int x);
        void add(Entity ent, WINDOW * win);

        void InitializeSnake();
        void NextHeadPreview(int headY, int headX, int &nextY, int &nextX);
        char CheckCollision(int y, int x);
        void CollisionManagement(int &nextY, int &nextX, int y, int x);
        int GetCurrLv();

        void InitializeGame();
        void RestartGame();
        void Top10();

        void highscores_right();
        void controls_leftT();
        void LvlInfo_leftB();
};
