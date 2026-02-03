#include "SnakeDatabase.hpp"

Database::Database(){
    this->head = nullptr;
    LoadScoreboard();
    if(this->head == nullptr){
        CreateEmpty();
    }
}
Database::~Database(){
    while(head != nullptr){
        PlayerRecord * temp = head;
        head = head->next;
        delete temp;
    }
}



void Database::CreateEmpty(){
    ofstream HS;
    HS.open("file/High_Scores.txt");
    for (int i = 0; i<10; i++){
        HS << "AAA" << " " << 0 << "\n";
    }
    HS.close();
    LoadScoreboard();
}



void Database::LoadScoreboard(){
    while(head != nullptr){
        PlayerRecord * temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;

    ifstream HS;
    HS.open("file/High_Scores.txt");

    char tch[4];
    unsigned long long int tval;
    PlayerRecord* tail = nullptr;

    while(true){ 
        HS >> tch;
        HS >> tval;
        if (HS.fail()){
            break;
        }
        PlayerRecord * n = new PlayerRecord;
        strncpy(n->name, tch, 3);
        n->name[3] = '\0';
        n->val = tval;
        if (this->head == nullptr){
            head = n;
            tail = head;
        }
        else{
            tail->next = n;
            tail = n;
        }

    }
    HS.close();
}



void Database::WriteScoreBoard(){
    ofstream HS;
    HS.open("file/High_Scores.txt");
    PlayerRecord * curr = head;
    while (curr != nullptr){
        HS << curr->name << " " << curr->val << "\n";
        curr = curr->next;
    }
    HS.close();
}



bool Database::isTop10(unsigned long long int v){
    PlayerRecord * curr = head;
    int count = 1;
    while (curr != nullptr){
        if (v >= curr->val){
            this->position = count;
            return true;
        }
        curr = curr->next;
        count++;
    }
    return false;
}



void Database::AddtoList(char ch[], unsigned long long int v){
    PlayerRecord * n = new PlayerRecord;
    strncpy(n->name, ch, 3);
    n->name[3] = '\0';
    n->val = v;
    n->next = nullptr;
    
    PlayerRecord * curr = head;
    PlayerRecord * prev = nullptr;
    while(curr != nullptr){
        if(n->val >= curr->val){
            
            if (prev == nullptr){
                n->next = head;
                this->head = n;
            }
            else{
                n->next = curr;
                prev->next = n;
            }
            break;
        }
        else{
            prev = curr;
            curr = curr->next;
        }

    }

    PlayerRecord* temp = head;
    for(int i = 1; i<10 && temp != nullptr; i++){
        temp = temp->next;
    }

    if(temp != nullptr && temp->next != nullptr){
        PlayerRecord * Del = temp->next;
        temp->next = nullptr;

        while (Del != nullptr){
            PlayerRecord * nextn = Del->next;
            delete Del;
            Del = nextn;
        }
    }


    WriteScoreBoard();
}



void Database::setCurrPos(int i){
    this->position = i;
}