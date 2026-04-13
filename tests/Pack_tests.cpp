#include "Pack.hpp"
#include "unit_test_framework.hpp"
#include "cassert"
#include "Card.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

// Add more tests here

TEST(test_pack_input) {
    istringstream packInput(
    "Nine of Spades\n"
    "Ten of Spades\n"
    "Jack of Spades\n"
    "Queen of Spades\n"
    "King of Spades\n"
    "Ace of Spades\n"
    "Nine of Hearts\n"
    "Ten of Hearts\n"
    "Jack of Hearts\n"
    "Queen of Hearts\n"
    "King of Hearts\n"
    "Ace of Hearts\n"
    "Nine of Clubs\n"
    "Ten of Clubs\n"
    "Jack of Clubs\n"
    "Queen of Clubs\n"
    "King of Clubs\n"
    "Ace of Clubs\n"
    "Nine of Diamonds\n"
    "Ten of Diamonds\n"
    "Jack of Diamonds\n"
    "Queen of Diamonds\n"
    "King of Diamonds\n"
    "Ace of Diamonds\n"
    );
    Pack pack(packInput);

    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());

    Card second = pack.deal_one();
    ASSERT_EQUAL(TEN, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
}  

TEST(test_pack_deal_one) {
    Pack pack;
    Rank expectedR[] = {NINE, TEN, JACK, QUEEN, KING, ACE};
    Suit expectedS[] = {SPADES, SPADES, SPADES, SPADES, SPADES, SPADES};
    for (int i = 0; i < 6; i++) {
        Card c = pack.deal_one();
        ASSERT_EQUAL(expectedR[i], c.get_rank());
        ASSERT_EQUAL(expectedS[i], c.get_suit());
    }
}

TEST(test_pack_reset){
    Pack pack;
    Card first = pack.deal_one();
    pack.reset();
    Card AfterReset = pack.deal_one();
    ASSERT_EQUAL(first.get_rank(), AfterReset.get_rank());
    ASSERT_EQUAL(first.get_suit(), AfterReset.get_suit());
}

TEST(test_pack_shuffle){
    Pack pack;
    pack.shuffle();
    Card first = pack.deal_one();
    vector<Card> dealt_cards;
    dealt_cards.push_back(first);
    int count = 1;
    while(!pack.empty()){
        pack.deal_one();
        count ++;
    }

    ASSERT_EQUAL(24, count);

    pack.shuffle();
    Card second = pack.deal_one();
    assert(second.get_rank() >= TWO && second.get_rank() <= ACE); 
    assert(second.get_suit() >= SPADES && second.get_suit() <= DIAMONDS);
}

TEST(test_pack_empty){
    Pack pack;
    for(int i = 0; i < 24; ++i){
        pack.deal_one();
    }
    ASSERT_EQUAL(true, pack.empty());
}

TEST_MAIN()
