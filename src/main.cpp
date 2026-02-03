#include "Manager/StateMachine.hpp"


#define BOARD_DIM 20
#define board_y BOARD_DIM
#define board_x BOARD_DIM * 2

int main(){
   initscr();
   cbreak();
   noecho();
   refresh();
   curs_set(0);
   srand(time(NULL));

   
   StateMachine StM (board_y, board_x);
   while (!StM.isGameOver()){
      StM.RunSelected();
   }



   endwin();

   return 0;
}


