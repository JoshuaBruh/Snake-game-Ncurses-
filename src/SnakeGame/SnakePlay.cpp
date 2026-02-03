#include "SnakePlay.hpp"

Play::Play(int board_y, int board_x):GMx(board_y, board_x),
                                     Sk(board_y/2 , board_x/2, board_y, board_x) //+ (SnakeLength/2)                            
                                     {
    this->board_y = board_y;
    this->board_x = board_x;
    this->game_over = false;
    this->PressedPause = false;
}
Play::~Play(){
    delete apple;
    apple = nullptr;
    wmng.delete_win(Gwin);
    wmng.delete_win(LBwin);
    wmng.delete_win(Ctrlwin);

}



void Play::InitializeGame(){
    int x, y;
    clear();
    this->Gwin = wmng.build_win(board_y, board_x);
    keypad(Gwin, true);


    GMx.build_Matrix();
    InitializeSnake();


    GMx.GetEmpty(y, x);
    apple = new Apple (y, x);
        

    getbegyx(Gwin, Ybeg, Xbeg);
    Sb = Scoreboard(board_x-1, Ybeg+board_y, Xbeg );
    Sb.Initialize(this->totalscore);
    Sb.ScoreRefresh();


    SkL.InitializeLevels();
    SkL.LevelInfo(board_x-1, Ybeg+board_y+2, Xbeg);


    Timer = Countdown(board_x, Ybeg-1, Xbeg);
    Timer.Initialize(SkL.getCurr()->TimetoComplete);
    Timer.TimerRefresh();
    

    highscores_right();
    controls_leftT();
    LvlInfo_leftB();
    this->initialized = true;
}



void Play::RestartGame(){
    if(this->LevelToSet != -1 && SkL.getCurr()->NLevel != this->LevelToSet){
        SkL.LevelUpdate(this->LevelToSet);
        this->LevelToSet = -1;
    } 
        
    if(SkL.getCurr()->Timeremaining > 0){
        Timer.Initialize(SkL.getCurr()->Timeremaining);
    }
    else{
        Timer.Initialize(SkL.getCurr()->TimetoComplete);
    }

    Timer.TimerRefresh();


    Sb.UpdateScore(totalscore);
    Sb.ScoreRefresh();
        
    SkL.LevelInfo(board_x-1, Ybeg+board_y+2, Xbeg);

    highscores_right();
    controls_leftT();
    LvlInfo_leftB();
}



void Play::GameLoop(){
    int y = 0, x = 0;
    if (!this->initialized){
        InitializeGame();
    }
    else{
        RestartGame();
    }

    wrefresh(Gwin);


    while(!game_over){

        wattron(Gwin, COLOR_PAIR(SkL.getCurr()->NLevel+2) | A_BOLD);
        box(Gwin, 0 ,0);
        wattroff(Gwin, COLOR_PAIR(SkL.getCurr()->NLevel+2) | A_BOLD);

        wtimeout(this->Gwin, 100/SkL.getCurr()->SpeedMoltiplier);

        UserI(); 

        if (this->PressedPause){
            wtimeout(this->Gwin, -1);
            SkL.getCurr()->Timeremaining = Timer.GetRemainingTime();
            break;
        }

        Timer.UpdateTimer();
        if (Timer.GetRemainingTime() <= 0) {
            this->game_over = true;
        }
        Timer.TimerRefresh();



        Update(y, x);


        wnoutrefresh(this->Gwin);
        Timer.TimerRefresh();
        doupdate();
    }

    if (!this->PressedPause){
        GameOver();
    }
}









void Play::UserI(){
    int ch = wgetch(Gwin);
    switch(ch){
        case KEY_UP:
            Sk.SetDirection(Snake::Direction::UP);
            break;
        case KEY_DOWN:
            Sk.SetDirection(Snake::Direction::DOWN);
            break;  
        case KEY_LEFT:
            Sk.SetDirection(Snake::Direction::LEFT);
            break;
        case KEY_RIGHT:
            Sk.SetDirection(Snake::Direction::RIGHT);
            break;
        case 110:
            if (SkL.getCurr()->next != nullptr){
                SkL.getCurr()->Timeremaining = Timer.GetRemainingTime();
                SkL.NextLevel();
                Timer.Initialize(SkL.getCurr()->Timeremaining > 0 ? SkL.getCurr()->Timeremaining : SkL.getCurr()->TimetoComplete);
                LvlInfo_leftB();
                SkL.LevelInfo(board_x-1, Ybeg+board_y+2, Xbeg);
            }
            break;
        case 112:
        if (SkL.getCurr()->prev != nullptr){
                SkL.getCurr()->Timeremaining = Timer.GetRemainingTime();
                SkL.PrevLevel();
                Timer.Initialize(SkL.getCurr()->Timeremaining > 0 ? SkL.getCurr()->Timeremaining : SkL.getCurr()->TimetoComplete);
                LvlInfo_leftB();
                SkL.LevelInfo(board_x-1, Ybeg+board_y+2, Xbeg);
            }   
            break;
        case 27:
            SkL.getCurr()->Timeremaining = Timer.GetRemainingTime();
            this->PressedPause = true;
            break; 
        default:
            break;
    }
    flushinp();//Svuota input, rimuove dal buffer gli input extra
}



void Play::Update(int y, int x){
    wattron(this->Gwin, COLOR_PAIR(1) | A_BOLD);
    add(*apple, this->Gwin);
    wattroff(this->Gwin, COLOR_PAIR(1) | A_BOLD);


    int NextY, NextX;
    CollisionManagement(NextY, NextX, y, x);


    delEnt(this->Gwin, Sk.SnakeCoord[SnakeLength-1][0], Sk.SnakeCoord[SnakeLength-1][1]);

    wattron(this->Gwin, COLOR_PAIR(2) | A_BOLD);
    SnakeBody body(Sk.SnakeCoord[0][0], Sk.SnakeCoord[0][1]);
    add(body, this->Gwin);

    Sk.SnakeMove(NextY, NextX);
    
    SnakeHead head(Sk.SnakeCoord[0][0], Sk.SnakeCoord[0][1]);
    add(head, this->Gwin);
    wattroff(this->Gwin, COLOR_PAIR(2) | A_BOLD);

}




void Play::CollisionManagement(int &NextY, int &NextX, int y, int x){
    NextHeadPreview(Sk.HeadY, Sk.HeadX, NextY, NextX);
    char Coll = CheckCollision(NextY, NextX);
    if (Coll == 'B'){
        this->game_over = true;
    }
    else if(Coll == 'A'){

        delEnt(this->Gwin, apple->gety(), apple->getx());
        GMx.GetEmpty(y, x);
        apple->setY(y);
        apple->setX(x);

        this->totalscore = totalscore + 100 * SkL.getCurr()->ScoreMultiplier;
        SkL.getCurr()->lvscore += 100 * SkL.getCurr()->ScoreMultiplier;

        if(SkL.getCurr()->lvscore >= (unsigned int)SkL.getCurr()->Objective){
            if(!SkL.getCurr()->completed){

                this->totalscore = totalscore + SkL.getCurr()->BonusComplete;
                SkL.getCurr()->lvscore += SkL.getCurr()->BonusComplete;

                SkL.getCurr()->Timeremaining = Timer.GetRemainingTime();
                SkL.getCurr()->completed = true;
                SkL.NextLevel();
                LvlInfo_leftB();
                Timer.Initialize(SkL.getCurr()->Timeremaining > 0 ? SkL.getCurr()->Timeremaining : SkL.getCurr()->TimetoComplete);
            }
        }
        highscores_right();
        SkL.LevelInfo(board_x-1, Ybeg+board_y+2, Xbeg);
        Sb.UpdateScore(totalscore);
        Sb.ScoreRefresh();
    }
}



void Play::NextHeadPreview(int headY, int headX, int &nextY, int &nextX){
    nextY = headY;
    nextX = headX;
    switch(Sk.GetDirection()){
        case Snake::Direction::UP:
            nextY--;
            break;
        case Snake::Direction::DOWN:
            nextY++;
            break;
        case Snake::Direction::LEFT:
            nextX--;
            break;
        case Snake::Direction::RIGHT:
            nextX++;
            break;
    }
    if(nextY<=0){
        nextY = board_y-2;
    }
    else if(nextY >= board_y-1){
        nextY = 1; 
    }


    if(nextX<=0){
        nextX = board_x-2;
    }
    else if(nextX >= board_x-1){
        nextX = 1; 
    }
}



char Play::CheckCollision(int y, int x){
    if(GMx.Matrix[y][x]){
        if(apple->gety() == y && apple->getx() == x){
            return 'A';
        }
        for(int i = 0; i<SnakeLength; i++){
            if (Sk.SnakeCoord[i][0] == y && Sk.SnakeCoord[i][1] == x){
                return 'B';
            }
        }

    }    
    
    return ' ';
}





void Play::Top10(){
    int Hby = 10;
    int Hbx = 60;
    WINDOW * HSwin = wmng.popup_win(Hby, Hbx);
    char name[4] = "   ";
    mvwprintw(HSwin, Hby/2-3, 2, "Congratulations! You are now %i° on the Leaderboard,", SkD.position);
    mvwprintw(HSwin, Hby/2-2, 2, "Insert Name, max 3 characters:");
    mvwprintw(HSwin, Hby/2+2, 2, "Press Enter to Confirm and return to Menu");
    echo();
    wrefresh(HSwin);
    curs_set(1);

    wmove(HSwin, Hby/2, Hbx/2);
    wgetnstr(HSwin, name, 3);

    if (name[0] == '\0' || name[0] == ' '){
        strcpy(name, "AAA\0");
    }

    noecho();
    curs_set(0);

    SkD.AddtoList(name, this->totalscore);
    SkD.position = -1;
    wmng.close_popup(HSwin);
}





bool Play::GameOver(){
    nodelay(this->Gwin, false);
    timeout(-1);
    Sk.ResetPosition(board_y/2, board_x/2);
    wmng.delete_win(this->Gwin);
    wmng.delete_win(SkL.Lwin);
    wmng.delete_win(Timer.Ctwin);
    wmng.delete_win(Sb.Swin);
    wmng.delete_win(LBwin);
    wmng.delete_win(Ctrlwin);
    wmng.delete_win(LVLinfo);
    SkL.ResetCompleted();

    clear();
    refresh();


    SkD.LoadScoreboard();

    if (this->exitfrommenu){
        do{
            mvprintw(wmng.yMax/2, (wmng.xMax/2)-12, "You Scored: %llu Points!", totalscore);
            mvprintw(wmng.yMax/2+1, (wmng.xMax/2)-16, "Press m to go back to the Menu:");
        }while( wgetch(stdscr) != 109);
    }

    else if(SkD.isTop10(this->totalscore) && !this->exitfrommenu){
        Top10();
    }

    else{
        do{
            mvprintw(wmng.yMax/2, (wmng.xMax/2)-28, "You Scored: %llu Points! Not enough for the top 10, Try Again!", totalscore);
            mvprintw(wmng.yMax/2+1, (wmng.xMax/2)-16, "Press m to go back to the Menu:");
        }while( wgetch(stdscr) != 109);
    }
    this->totalscore = 0;
    this->initialized = false;
    this->exitfrommenu = false;
    return this->game_over = true;
}








void Play::add(Entity ent, WINDOW * win){
    mvwaddch(win, ent.gety(), ent.getx(), ent.getEnt());
    GMx.setOccupied(ent);
}

void Play::delEnt(WINDOW * win, int y, int x){
    mvwaddch(win, y, x, ' '); 
    GMx.setEmpty(y, x);
}


void Play::InitializeSnake(){
    wattron(this->Gwin, COLOR_PAIR(2) | A_BOLD);
    for(int i = 0; i < SnakeLength; i++){
        if (i==0){
            SnakeHead head(Sk.SnakeCoord[i][0], Sk.SnakeCoord[i][1]);
            add(head, this->Gwin);
        }
        else{
            SnakeBody body(Sk.SnakeCoord[i][0], Sk.SnakeCoord[i][1]);
            add(body, this->Gwin);
        }
    }
    wattroff(this->Gwin, COLOR_PAIR(2) | A_BOLD);
}


int Play::GetCurrLv(){
    return this->SkL.getCurr()->NLevel;
}









void Play::highscores_right(){
    ifstream HighScores("file/High_Scores.txt");
    if(this->LBwin == nullptr){
        this->LBwin = newwin(this->board_y, 25, Ybeg, Xbeg+board_x+1);
    }
    werase(LBwin);
    wattron(LBwin, A_BOLD);
    box(LBwin, 0, '~');
    char name[4];
    unsigned long long int score;
    int position = 1;
    int row = 4;


    mvwprintw(LBwin, 2, 4, "Leaderboard");
    bool alreadytop10 = SkD.isTop10(this->totalscore);
    if (alreadytop10){
        wattron(LBwin, COLOR_PAIR(8) | A_REVERSE);
        box(LBwin, 0, '~');
        wattroff(LBwin, COLOR_PAIR(8) | A_REVERSE);
    }
    while(HighScores >> name >> score){
        bool currentRpos = SkD.position == position;
        if(alreadytop10 && currentRpos){
            wattron(LBwin, COLOR_PAIR(8));
        }
        mvwprintw(LBwin, row++, 1, "%2d°. %-4s:%llu", position++, name, score);
        if(alreadytop10 && currentRpos){
            wattroff(LBwin, COLOR_PAIR(8));
            SkD.setCurrPos(-1);
        }
    }
    wattroff(LBwin, A_BOLD);

    HighScores.close();
    wnoutrefresh(this->LBwin);
    return;
}



void Play::controls_leftT(){
    ifstream Controls("file/Controls.txt");
    if(this->Ctrlwin == nullptr){
        this->Ctrlwin = newwin(7, 26, Ybeg, Xbeg - 28);
    }
    werase(Ctrlwin);
    wattron(Ctrlwin, A_BOLD);
    box(Ctrlwin, 0, '~');


    char ControlRow[25];

    int row = 1;
    while (Controls.getline(ControlRow, sizeof(ControlRow)) && row < 6) {   
        mvwprintw(Ctrlwin, row++, 1, "%s", ControlRow);
    }

    Controls.close();
    wattroff(Ctrlwin, A_BOLD);
    wnoutrefresh(this->Ctrlwin);
}



void Play::LvlInfo_leftB(){
    if(this->LVLinfo == nullptr){
        this->LVLinfo = newwin(7, 30, Ybeg + 9, Xbeg - 32);
    }

    werase(LVLinfo);



    if(SkL.getCurr()->completed){
        wattron(LVLinfo, COLOR_PAIR(8) | A_REVERSE);
    }
    else{
        wattron(LVLinfo, COLOR_PAIR(SkL.getCurr()->NLevel+2));
    }

    wattron(LVLinfo, A_BOLD);
    box(LVLinfo, 0, '~');
    wattroff(LVLinfo, COLOR_PAIR(8) | A_REVERSE);
    wattroff(LVLinfo, COLOR_PAIR(SkL.getCurr()->NLevel+2));

    mvwprintw(LVLinfo, 1, 2, "Level %i Info:", SkL.getCurr()->NLevel);
    mvwprintw(LVLinfo, 2, 2, "Score Multiplier: x%i", SkL.getCurr()->ScoreMultiplier);
    mvwprintw(LVLinfo, 3, 2, "Speed Multiplier: x%.2f", SkL.getCurr()->SpeedMoltiplier);
    mvwprintw(LVLinfo, 4, 2, "Bonus when completed: %i", SkL.getCurr()->BonusComplete);
    int mins = SkL.getCurr()->TimetoComplete / 60;
    int secs = SkL.getCurr()->TimetoComplete % 60;
    mvwprintw(LVLinfo, 5, 2, "Time: %i:%02i", mins, secs);

    wattroff(LVLinfo, A_BOLD);
    wnoutrefresh(this->LVLinfo);
}