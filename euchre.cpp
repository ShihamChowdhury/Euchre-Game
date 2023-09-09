// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cassert>
#include <array>

using namespace std;

class Game {
    private:
    Player* players[4];
    int wincondition;
    bool shuffle;
    Pack pack;
    bool gamerunning;
    int dealer;
    int eldesthand;
    int handcount;
    Card upcard;

    public:
    std::vector<int> trickwinners;
    int orderupplayer;
    int team1score;
    int team2score;
    int indexleader;
    std::string trumpsuit;

    Game(const std::string argarray[], int pointstowin, 
    std::string shufflerule, std::istream& file){
        for(int i = 0; i < 8; i += 2){
            players[i/2] = Player_factory(argarray[i],
            argarray[i+1]);
        }
        wincondition = pointstowin;
        if(shufflerule == "shuffle"){
            shuffle = true;
        }
        else {
            shuffle = false;
        }
        pack = Pack(file);
        team1score = 0;
        team2score = 0;
    }

    void deal_x_times(int x, int index) {
        for (int i = 0; i < x; i++)
        {
            players[index]->add_card(pack.deal_one());
        }
    }

    void play(){
       gamerunning = true;
       dealer = -1;
       eldesthand = 0;
       handcount = -1;
    }

    void end_game(){
        if(team1score >= wincondition ||
         team2score >= wincondition){
            if(team1score > team2score){
                 cout << *players[0] << " and " << *players[2] 
                 << " win!" << endl;
            }
            else{
                 cout << *players[1] << " and " << *players[3] 
                 << " win!" << endl;
            }
            gamerunning = false;
            for (int i = 0; i < 4; i++)
            {
             delete players[i];
            }
            delete[] *players;
        }
    }

    bool game_status(){
        return gamerunning;
    }

    Card current_upcard(){
        return upcard;
    }

    int getdealer(){
        return dealer;
    }

    int geteldesthand(){
        return eldesthand;
    }

    int getorderupplayer(){
        return orderupplayer;
    }

    void start_hand(){
        handcount++;
        if(dealer == 2){
            dealer++;
            eldesthand = 0;
        }
        else if(dealer == 3){
            dealer = 0;
            eldesthand++;
        }
        else{
           dealer++;
           eldesthand++;
        }
        if(shuffle == true){
        pack.shuffle();
        }
        indexleader = eldesthand;
        cout << "Hand " << handcount << endl;
        cout << *players[dealer] << " deals" << endl;
        for (int i = 0; i < 4; i = i + 2)
        {
                deal_x_times(3, (eldesthand + i)%4);
                deal_x_times(2, (eldesthand + 1 + i)%4);
        }
        for (int i = 0; i < 4; i = i + 2)
        {
                deal_x_times(2, (eldesthand + i)%4);
                deal_x_times(3, (eldesthand + 1 + i)%4);
        }
        upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
    }

    void set_trump(std::string orderupsuit){
       trumpsuit = orderupsuit;
    }

    void make_trump(){
    for(int round = 1; round < 3; round++){
          for(int i = 0; i < 4; i++){
          std::string orderupsuit;
          bool condition = players[(geteldesthand() + i)%4]->make_trump(
            current_upcard(),(i == getdealer()), 
            round, orderupsuit);
          if(condition == true && round == 1){
               set_trump(orderupsuit);
                players[getdealer()]->add_and_discard
                (current_upcard());
               orderupplayer = (geteldesthand() + i)%4;
               i = 5;
               round = 4;
           }
          else if(condition == true && round == 2){
               set_trump(orderupsuit);
               orderupplayer = (geteldesthand() + i)%4;
               i = 5;
               round = 4;
           }
        }     
       }
}
    
    void play_trick(){
    Card *playedcards = new Card[4]();
    for(int trick = 0; trick < 5; trick++){
        for (int i = 0; i < 4; i++)
          {
            if(i == 0){
                playedcards[i] = players[indexleader]->lead_card(trumpsuit);
                cout << playedcards[i]
                 << " led by " 
                << *players[(indexleader + i)%4] << endl;
            }
            else {
                playedcards[i] = (players[(indexleader+i)%4]->
                play_card(playedcards[0],trumpsuit));
                cout << playedcards[i]
                 << " played by " 
                << *players[(indexleader + i)%4] << endl;
            }
         } 
        Card highestcard = playedcards[0];
        int index = 0;
        for(int x = 0; x < 5; x++){
           if(Card_less(highestcard, playedcards[x], playedcards[0], 
           trumpsuit) == true){
                highestcard = playedcards[x];
                index = x;
           }
        }
        indexleader = (indexleader+index)%4;
        trickwinners.push_back(indexleader);
        delete[] playedcards;
        cout << *players[indexleader] << " takes the trick" << endl << endl;
    }
}

    void assign_score(){
        bool team1order = false; 
        bool team2order = false;
        int team1wins = 0; 
        int team2wins = 0;
        for (int i = 0; i < trickwinners.size(); i++)
        {
        if (trickwinners[i] == 0 || trickwinners[i] == 2)
        {
            team1wins++;
            if(orderupplayer == 0 || orderupplayer == 2){
                 team1order = true;
            }
        }
        else if(trickwinners[i] == 1 || trickwinners[i] == 3){
            team2wins++;
            if(orderupplayer == 1 || orderupplayer == 3){
                 team2order = true;
        }
        }
        }
    if(team1wins >= 3){
        int score1 = 1;
        cout << *players[0] << " and " << *players[2] 
        << " win the hand" << endl;
        if(team1order != true){
            score1 = 2;
            cout << "euchred!" << endl;
        }
        else if(team1wins == 5){
            score1 = 2;
            cout << "march!" << endl;
        }
        team1score += score1;
    }
    else{
        int score2 = 0;
        score2 = 1;
        cout << *players[1] << " and " << *players[3] 
        << " win the hand" << endl;
        if(team2order != true){
            score2 = 2;
            cout << "euchred!" << endl;
        }
        else if(team2wins == 5){
            score2 = 2;
            cout << "march!" << endl;
        }
        
        team2score += score2;
    }
    cout << *players[0] << " and " << *players[2] << " have " 
    << team1score << " points" << endl;
    cout << *players[1] << " and " << *players[3] << " have "
    << team2score << " points" << endl << endl;
    pack.reset();
    trickwinners.clear();
}
};

int main(int argc, char *argv[]) {
    if(argc != 12){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
    if(atoi(argv[3]) < 1 || atoi(argv[3]) > 100){
       cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
    std::string argument2 = argv[2];
    if(!(argument2 == "shuffle" || argument2 == "noshuffle")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
    for(int i = 5; i < argc; i = i + 2){
        std::string argument = argv[i];
        if(!(argument == "Simple" || argument == "Human")){
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
              << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
              << "NAME4 TYPE4" << endl;
             return 1;
        }
    }
    ifstream file(argv[1]);
    if(file.is_open() != true){
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }
    std::string argarray[8];
    for(int x = 4; x < 12; x++){
        argarray[x-4] = argv[x];
    }
    Game euchre = Game(argarray, atoi(argv[3]), argument2, file);
    euchre.play();
    for(int i = 0; i < argc; i++){
        cout << argv[i] << " "; 
    }
    cout << endl;
    while(euchre.game_status() == true){
       euchre.start_hand();
       string upcard = euchre.current_upcard().get_suit();
       euchre.make_trump();
       euchre.play_trick();
       euchre.assign_score();
       euchre.end_game();       
    }
}