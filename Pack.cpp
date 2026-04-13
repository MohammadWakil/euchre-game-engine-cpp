#include <iostream> 
#include "Pack.hpp"
#include <string>
#include <cassert>
#include <array>

using namespace std;

Pack::Pack(){
    int index = 0;
    for(int s = SPADES; s <= DIAMONDS; ++s){
        for(int x = NINE; x <= ACE; ++x){
            cards.at(index) = Card((Rank)x, (Suit)s);
            ++index;
        }
    }
    next = 0;
}

Pack::Pack(std::istream& pack_input) {
    for(int i = 0; i <PACK_SIZE; ++i){
        Card c;
        pack_input >> c;
        cards.at(i) = c; 
    }
    next = 0;
}

Card Pack::deal_one(){
    assert(next < PACK_SIZE);
    Card c = cards.at(next);
    ++next;
    return c;
}

void Pack::reset(){
        next = 0;
}

void Pack::shuffle(){
    for(int i = 0; i < 7; ++i){
        array<Card, PACK_SIZE> shuffleddeck;
        array<Card, PACK_SIZE> deck = cards;
        int firsthalf = deck.size()/2;
        for(int i = 0; i < firsthalf; ++i){
            shuffleddeck.at(2*i) = deck.at(firsthalf+i);
            shuffleddeck.at(2*i + 1) = deck.at(i);
        }
        for(int i = 0; i < PACK_SIZE; ++i){
            cards.at(i) = shuffleddeck.at(i); 
        }    
    }
    next = 0;
}

bool Pack::empty() const{
    if(next >= PACK_SIZE){
        return true;
    } else {
        return false;
    }
}