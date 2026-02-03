#include "SnakePause.hpp"       

Pause::Pause(int board_y, int board_x) : Menu (board_y, board_x){
    this->board_y = board_y;
    this->board_x = board_x;
    strcpy(menus[0].name, "Resume");
    strcpy(menus[1].name, "Choose Level");
    strcpy(menus[2].name, "Game Rules");
    strcpy(menus[3].name, "Menu");
}


void Pause::run_selected(int index, bool &ExitLoop){
    switch(index){
        case 0:
          this->PressedResume = true;
          ExitLoop = true;
          break;
        case 1:
          this->LvlChosen = Choose_Level();
          this->PressedResume = true;
          ExitLoop = true;
          break;
        case 2:
          rules();
          break;
        case 3:
          this->PressedMenu = true;
          ExitLoop = true;
          break;
        default:
          break;
    }
}




int Pause::Choose_Level(){
  this->Chosen = false;
  this->IndexLevel = 0;
  LevelList Levels[5]{
            {"Level1", true},
            {"Level2", false},
            {"Level3", false},
            {"Level4", false},
            {"Level5", false}};
  
  

  WINDOW* levelwin = wmng.popup_win(board_y,15);
  int yWin,xWin;
  getmaxyx(levelwin, yWin, xWin);
  
  



  while (!this->Chosen){  
    for (int i = 0; i < 5; i++){
      string name = Levels[i].name;
      if(Levels[i].selected){
        wattron(levelwin, A_STANDOUT);
      }
      mvwprintw(levelwin, (yWin/2)-(list_obj/2)+i, (xWin-name.length())/2, name.c_str());
      wattroff(levelwin, A_STANDOUT);
    }
    wrefresh(levelwin);

    keypad(levelwin,true);
      
    int ch = wgetch(levelwin);
      switch (ch){
          case KEY_DOWN:
            Levels[IndexLevel].selected = false;
            if(IndexLevel == 4){IndexLevel = -1;}
            IndexLevel = IndexLevel+1;
            Levels[IndexLevel].selected = true;
            break;
          case KEY_UP:
            Levels[IndexLevel].selected = false;
            if(IndexLevel == 0){IndexLevel = 5;}
            IndexLevel = IndexLevel-1;
            Levels[IndexLevel].selected = true;
            break;
          case 10:
            this->Chosen = true;
            break; 
          case 27:
            this->Chosen = true;
            break;             
          default:
            break;
      }

  }
  wmng.close_popup(levelwin);
  return IndexLevel+1;
}