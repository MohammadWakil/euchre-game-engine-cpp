#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;

class Game {
 public:
  Game(vector<Player*> players, Pack pack, bool ynshuffle, int requiredPoints)
  :players(players), pack(pack), ynshuffle(ynshuffle), requiredPoints
  (requiredPoints){}

    void play() {
        int hand = 0;
        while (check_winner() == false) {
            cout << "Hand " << hand << endl;
            cout << players[dealer]->get_name() << " deals" << endl;
            shuffle();
            deal();
            round = 1; 
            make_trump();
            play_hand(); 
            dealer = (dealer + 1) % 4;
            hand++;
        }
    }
  




 private:
  std::vector<Player*> players;
  Pack pack;
  Suit trump;
  Card upcard;
  bool ynshuffle;
  int requiredPoints;
  int dealer = 0;
  int round = 1;
  int teamOneTricks = 0;
  int teamTwoTricks = 0;
  int teamOnePoints = 0;
  int teamTwoPoints = 0;
  bool teamOneMakers = false;

  void shuffle();
  void deal();
  void make_trump();
  void play_hand();
  void play_trick(int &currentLeader);
  void score_hand(int &teamOnePoints, int &teamTwoPoints);
  bool check_winner();
};

void Game::shuffle(){
    if (!ynshuffle){
        pack.reset();
    }
    else {
        pack.shuffle();
    }
}
void Game::deal(){
vector<int> cards ={3,2,3,2,2,3,2,3};
    for (size_t i = 0; i < 8; i++){
        for (int j = 0; j < cards[i]; j++){
            players[(dealer + 1 + i)%4]->add_card(pack.deal_one());
        }
    }
    upcard = pack.deal_one();
    cout << upcard << " turned up" << endl;
}


void Game::make_trump(){
    bool isDealer;
    bool chooseTrump;
    Suit order_up;
    int currentplayer = 0;
    int passcount = 0;

    if (round == 1){
        for (int i = 0; i < 4; ++i) {
           currentplayer = (dealer + 1 + i) % 4;
            if (currentplayer == dealer){
                isDealer = true;
            }
            else {
                isDealer = false;
            }
            chooseTrump = players[currentplayer]->
            make_trump(upcard, isDealer, 1, order_up);

            if (!chooseTrump){
                cout << players[currentplayer]->get_name() << " passes" << 
                endl;
                passcount++;
            }
            else {
                break;
            }
           
        }
        if (passcount == 4){
            round++;
        }
        else if (chooseTrump){
            if (currentplayer == 0 || currentplayer == 2){
                teamOneMakers = true;
            }
            else{
                teamOneMakers = false;
            }
            trump = order_up;
            cout << players[currentplayer]->get_name() << " orders up " << 
            trump << endl;
            
            players[dealer]->add_and_discard(upcard);
            cout << endl;
            return;

        }
    }


    if (round == 2){
        for (int i = 0; i < 4; ++i) {
           currentplayer = (dealer + 1 + i) % 4;
            if (currentplayer == dealer){
                isDealer = true;
            }
            else {
                isDealer = false;
            }
            chooseTrump = players[currentplayer]->
            make_trump(upcard, isDealer, 2, order_up);

            if (!chooseTrump){
                cout << players[currentplayer]->get_name() << " passes" << 
                endl;
            }
            else {
                break;
            }
            

        }
        if (chooseTrump){
            if (currentplayer == 0 || currentplayer == 2){
                teamOneMakers = true;
            }
            else{
                teamOneMakers = false;
            }
            trump = order_up;
            cout << players[currentplayer]->get_name() << " orders up " <<
            trump << endl;
            cout << endl;
        }

    }
    //round = 1;

}
void Game::play_trick(int &currentLeader){
    vector<Card> playedCards(4);
    Card ledCard;
    Card playCard;
    int tempCard = 0;
    ledCard = players[currentLeader]->lead_card(trump);

    cout << ledCard << " led by " << players[currentLeader]->get_name() << 
    endl;
    playedCards[currentLeader] = ledCard;

    for (int i = 1; i < 4; i++){
        playCard = players[(currentLeader  + i ) % 4]->
        play_card(ledCard, trump);
        playedCards[(currentLeader + i ) % 4] = playCard;
        cout << playCard << " played by " << 
        players[(currentLeader + i ) % 4]->get_name() << endl;
    }
    for (size_t k = 0; k < playedCards.size(); k++){
        if(Card_less(playedCards[tempCard], playedCards[k], ledCard, trump)){
            tempCard = k;
        }
    }
    cout << players[tempCard]->get_name() << " takes the trick" << 
    endl << endl;
    if(tempCard == 0 || tempCard == 2){
        teamOneTricks++;
    }
    else if( tempCard == 1 || tempCard == 3){
        teamTwoTricks++;
    } 
    currentLeader = tempCard;

}
void Game::play_hand(){
    teamOneTricks = 0;
    teamTwoTricks = 0;

    int currentLeader = (dealer + 1) % 4;
    for (int i = 0; i < 5; ++i){
        play_trick(currentLeader);
    }
    score_hand(teamOnePoints, teamTwoPoints);


}
void Game::score_hand(int &teamOnePoints, int &teamTwoPoints){
    if (teamOneMakers){
        if (teamOneTricks == 3 || teamOneTricks == 4 ){
            teamOnePoints++;
        }
        if (teamOneTricks == 5){
            teamOnePoints+= 2;
        }
        if (teamTwoTricks >= 3){
            teamTwoPoints+=2;
        }
        
    }
    else {
        if (teamTwoTricks == 3 || teamTwoTricks == 4 ){
            teamTwoPoints++;
        }
        if (teamTwoTricks == 5){
            teamTwoPoints+=2;
        }
        if (teamOneTricks >= 3){
            teamOnePoints+=2;
        }        
    }
    if (teamOneTricks > teamTwoTricks){
        cout << players[0]->get_name() << " and " << 
        players[2]->get_name() << " win the hand" << endl;
        if (teamOneTricks == 5 && teamOneMakers){
            cout << "march!" << endl;
        }
        if (teamOneTricks >= 3 && !teamOneMakers){
            cout << "euchred!" << endl;

        }
    }
    else {
        cout << players[1]->get_name() << " and " << 
        players[3]->get_name() << " win the hand" << endl;
        if (teamTwoTricks == 5 && !teamOneMakers){
            cout << "march!" << endl;
        }
        if (teamTwoTricks >= 3 && teamOneMakers){
            cout << "euchred!" << endl;

        }        

    }
    cout << players[0]->get_name() << " and " << players[2]->get_name() << 
    " have " << teamOnePoints << " points" << endl;
    cout << players[1]->get_name() << " and " << players[3]->get_name() << 
    " have " << teamTwoPoints << " points" << endl;
    cout << endl;
}
bool Game::check_winner(){
    if(teamOnePoints >= requiredPoints){
    cout << players[0]->get_name() << " and " << players[2]->get_name() << 
    " win!" << endl;
        return true;
    }
    else if (teamTwoPoints >= requiredPoints ){
        cout << players[1]->get_name() << " and " << 
        players[3]->get_name() << " win!" << endl;
        return true;
    }
    else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" << 
        endl;
        return 1;
    }
    string fileName = argv[1];
    string shuffleArgument = argv[2];
    int pointsToWin = stoi(argv[3]);
    if (pointsToWin < 1 || pointsToWin > 100) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" << 
        endl;
        return 1;
    }
    bool shuffleEnabled;
    if (shuffleArgument == "shuffle") {
        shuffleEnabled = true;
    } else if (shuffleArgument == "noshuffle") {
        shuffleEnabled = false;
    } else {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" << 
        endl;
        return 1;
    }
    for (int i = 5; i < 12; i += 2) {
        string playerType = argv[i];
        if (playerType != "Simple" && playerType != "Human") {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" 
            << endl;
            return 1;
        }
    }
    ifstream packFile(fileName);
    if (!packFile) {
        cout << "Error opening " << fileName << endl;
        return 1;
    }
    Pack pack(packFile);
    vector<Player*> players;
    for (int i = 4; i < 12; i += 2) {
        string playerName = argv[i];
        string playerType = argv[i + 1];
        players.push_back(Player_factory(playerName, playerType));
    }

    Game game(players, pack, shuffleEnabled, pointsToWin);

    game.play();
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
      }
    return 0;
}