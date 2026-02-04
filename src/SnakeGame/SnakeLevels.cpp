#include "SnakeLevels.hpp"

Level::Level(){
    this->curr = this->head = this->tail = nullptr;
    this->Lwin = nullptr;
}


void Level::AddLevel(int NLevel, int ScoreMultiplier, double SpeedMoltiplier,int BonusComplete, int Objective, int TimetoComplete){
    LevelNode *nuovo = new LevelNode;
    nuovo->next = nuovo->prev = nullptr;
    nuovo->NLevel = NLevel;
    nuovo->ScoreMultiplier = ScoreMultiplier;
    nuovo-> SpeedMoltiplier = SpeedMoltiplier;
    nuovo->BonusComplete = BonusComplete;
    nuovo->Objective = Objective;
    nuovo->TimetoComplete = TimetoComplete;
    if (this->head == nullptr && this->tail == nullptr){
        head = tail = nuovo;
    }
    else{
        this->tail->next = nuovo;
        nuovo->prev = tail;
        this->tail = nuovo;
    }
}
    



void Level::InitializeLevels() {
    if(this->head != nullptr){
        ResetCompleted();
        return;
    }

    AddLevel(1, 1, 1, 100, 500, 120);
    AddLevel(2, 2, 1.25, 300, 1500, 150);
    AddLevel(3, 3, 1.50, 700, 4500, 180);
    AddLevel(4, 4, 1.75, 1000, 10000, 240);
    AddLevel(5, 5, 2, 2000, 15000, 300);
    curr = head;
}





void Level::LevelInfo(int board_x, int y, int x){
    if (this->curr == nullptr){
        return;
    }
    if (this->Lwin == nullptr) {
        Lwin = newwin(3, board_x+4, y, x);
    }
    werase(Lwin);
    if(this->curr->completed){
        wattron(Lwin, COLOR_PAIR(8) | A_BOLD);
        mvwprintw(Lwin, 0, 0, "Current Level*: %i [COMPLETED],\nCurrent Level Score: %llu,\nObjective[BONUS ALREADY COLLECTED]: %i", this->curr->NLevel, this->curr->lvscore, this->curr->Objective);
        wattroff(Lwin, COLOR_PAIR(8) | A_BOLD);
    }
    else{
        wattron(Lwin, COLOR_PAIR(curr->NLevel+2) | A_BOLD);
        mvwprintw(Lwin, 0, 0, "Current Level: %i,\nCurrent Level Score: %llu,\nObjective: %i", this->curr->NLevel, this->curr->lvscore, this->curr->Objective);
        wattroff(Lwin, COLOR_PAIR(curr->NLevel+2) | A_BOLD);
    }
    wnoutrefresh(Lwin);
}




void Level::NextLevel(){
    if (this->curr != nullptr && curr->next != nullptr){
        curr = curr->next;
    }
}

void Level::PrevLevel(){
    if (this->curr != nullptr && curr->prev != nullptr){
        curr = curr->prev;
    }
}


Level::LevelNode* Level::getCurr(){
    return this->curr;
}





void Level::LevelUpdate(int lvlc){
    LevelNode * search = this->head;
    while (search != nullptr){
        if(search->NLevel == lvlc){
            this->curr = search;
            return;
        }
        search = search->next;
    }
}





void Level::ResetCompleted(){
    LevelNode* aux = this->head;
    while(aux != nullptr){
        aux->completed = false;
        aux->Timeremaining = 0;
        aux->lvscore = 0;
        aux = aux->next;
    }
    this->curr = this->head;
    this->maxLevel = false;

    if (Lwin != nullptr){
        delwin(Lwin);
        Lwin = nullptr;
    }
}



Level::~Level(){
    LevelNode * temp = head;
    while (temp != nullptr){
        LevelNode * prossimo = temp->next;
        delete temp;
        temp = prossimo;
    }
    if (Lwin != nullptr){
        delwin(Lwin);
    }
}