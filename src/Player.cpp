#include "Player.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm> 


class SimplePlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;
public:
    SimplePlayer(const std::string& PlayerName_in)
        : name(PlayerName_in){}

    const std::string& get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round, 
        Suit &order_up_suit) const override {
        assert(round == 1 || round == 2);
        Suit up_suit = upcard.get_suit();
        if(round == 1){
            int count = 0;
            for(const Card& c: hand){
                if(c.get_suit(up_suit) == up_suit && c.is_face_or_ace()){
                    ++count;
                } 
            }
            if(count >= 2){
                order_up_suit = up_suit;
                return true;
            }
        }
        if(round == 2){
            Suit next_trump = Suit_next(up_suit);
            if (is_dealer) {
                order_up_suit = next_trump;
                return true;
            }
            for(const Card& c: hand){
                if(c.get_suit() == next_trump && c.is_face_or_ace()){
                    order_up_suit = next_trump;
                    return true;
                }
            }
        }
        return false;
    }
    
    void add_and_discard(const Card &upcard) override{
        assert(hand.size() > 0);
        hand.push_back(upcard);
        Suit trump = upcard.get_suit();
        int discard_index = 0;
        for(int i = 0; i < hand.size(); ++i){
            if(Card_less(hand.at(i), hand.at(discard_index), trump)){
                discard_index = i;
            }
        }
        hand.erase(hand.begin() + discard_index);
    }

    Card lead_card(Suit trump) override {
        assert(hand.size() > 0);
        int trumpcount = 0;
        int index = 0;

        for (size_t i = 0; i < hand.size(); ++i){
            if (hand[i].is_trump(trump)){
                trumpcount++;
            }
        }

        if(trumpcount == hand.size()){
            for (int i = 0; i < hand.size(); ++i) {
                if (Card_less(hand[index], hand[i], trump)) {
                    index = i;
                }
            }
            Card lead = hand[index];
            hand.erase(hand.begin() + index);
            return lead;

        }
        // else {
        Card maxCard;
        for (size_t i = 0; i < hand.size(); ++i){
            if(hand[i].get_suit(trump) != trump ){
                maxCard = hand[i];
                index = i;
                break;
            }
        }
        for (size_t k = 0; k < hand.size(); ++k){
            if(hand[k].get_suit(trump) != trump ){
                if(Card_less(maxCard, hand[k], trump)){
                    maxCard = hand[k];
                    index = k;
                }
                
                
            }

            }
        // }

    Card lead = hand[index];
    hand.erase(hand.begin() + index);
    return lead;
    }


    Card play_card(const Card &led_card, Suit trump) override{
        assert(hand.size() > 0);
        int index = -1;

        Suit led_suit = led_card.get_suit(trump);
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].get_suit(trump) == led_suit) {
                if (index == -1 || Card_less(hand[index], hand[i], trump)) {   
                index = i;
                }
            }
        }

        if (index == -1) {
            index = 0;
            for (int i = 1; i < hand.size(); ++i) {
                if (Card_less(hand[i], hand[index], trump)) {
                index = i;
                }
            }
        }
        Card played_card = hand.at(index);
        hand.erase(hand.begin() + index);
        return played_card;    
    }
};        

class HumanPlayer : public Player {
public:

    HumanPlayer(const std::string &name) : name(name) {}
    
    const std::string & get_name() const override {
        return name;
    }
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());

    }
    
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override{

        assert(round == 1 || round == 2);
        std::string decision;       

        print_hand();

        std::cout << "Human player " << name << 
        ", please enter a suit, or \"pass\":\n";
        std::cin >> decision;
        if (decision != "pass") {
            order_up_suit = string_to_suit(decision);
            return true;
        }
        else {
            return false;
        }

    }
    
    void add_and_discard(const Card &upcard) override{
        assert(hand.size() > 0);
        int decision = 0;


        std::sort(hand.begin(), hand.end());
        print_hand();
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << name << 
        ", please select a card to discard:\n";
        std::cin >> decision;

        if (decision != -1){
            hand.erase(hand.begin() + decision);
            hand.push_back(upcard);
            std::sort(hand.begin(), hand.end());

        }

            return;        
    }
    
    Card lead_card(Suit trump) override{
        assert(hand.size() > 0);
        int decision = 0;

        Card ledcard;

        print_hand();
        std::cout << "Human player " << name << 
        ", please select a card:\n";

        std::cin >> decision;
        ledcard = hand.at(decision);

        hand.erase(hand.begin() + decision);

        return ledcard;
    
    }
    
    Card play_card(const Card &led_card, Suit trump) override{
        assert(hand.size() > 0);
        int decision;

        Card playedcard;


        print_hand();

        std::cout << "Human player " << name << ", please select a card:\n";
        std::cin >> decision;
        playedcard = hand.at(decision);

        hand.erase(hand.begin() + decision);

        return playedcard;

      }

private:

    std::string name;
    std::vector<Card> hand;
    void print_hand() const{
        for (size_t i=0; i < hand.size(); ++i){
            std::cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
        }
    }
};

Player * Player_factory(const std::string &name, const std::string &strategy) 
{
    if (strategy == "Simple"){
        return new SimplePlayer(name);
    }
    else if (strategy == "Human"){
        return new HumanPlayer(name);
    }
    return nullptr;
}
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;

}
