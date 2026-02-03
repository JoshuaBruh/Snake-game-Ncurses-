#include "WindowManager.hpp"
class Database{
    private:
        struct PlayerRecord{
           char name[4];
            unsigned long long int val;
            PlayerRecord * next = nullptr;
        };
        PlayerRecord * head = nullptr;
    public:
        int position = -1;
        Database();
        ~Database();
        void LoadScoreboard();
        void WriteScoreBoard();
        void CreateEmpty();
        bool isTop10(unsigned long long int v);
        void AddtoList(char ch[], unsigned long long int v);
        void setCurrPos(int i);
};