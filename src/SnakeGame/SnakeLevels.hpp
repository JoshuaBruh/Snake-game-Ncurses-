#include "../Manager/WindowManager.hpp"

class Level{
    private:
    struct LevelNode{
        LevelNode* next, *prev;
            int ScoreMultiplier;
            double SpeedMoltiplier;
            int BonusComplete;
            int Objective;
            int NLevel;
            int TimetoComplete;
            bool completed = false;
            unsigned long long int lvscore =  0;
            int Timeremaining = 0;
        };
        
    public:
        WINDOW * Lwin;
        LevelNode* head;
        LevelNode* tail;
        LevelNode* curr;
        bool maxLevel = false;
        Level();
        ~Level();
        void AddLevel(int NLevel, int ScoreMultiplier, double SpeedMoltiplier,int BonusComplete, int Objective, int TimetoComplete);
        void InitializeLevels();
        void LevelInfo(int board_x, int y, int x);
        void NextLevel();
        void PrevLevel();
        void LevelUpdate(int lvl);
        void ResetCompleted();
        LevelNode* getCurr();
};

