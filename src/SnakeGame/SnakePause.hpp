#pragma once
#include "../Manager/WindowManager.hpp"
#include "SnakeMenu.hpp"



class Pause : public Menu{
    private:
    public:
        struct LevelList{
            char name[15];
            bool selected;
        };
        LevelList Levels[5];
        bool PressedMenu = false;
        bool PressedResume = false;
        int IndexLevel;
        bool Chosen = false;
        int LvlChosen = -1;

        Pause(){}
        Pause(int board_y, int board_x);
        void run_selected(int index, bool &ExitLoop) override;
        int Choose_Level();
};