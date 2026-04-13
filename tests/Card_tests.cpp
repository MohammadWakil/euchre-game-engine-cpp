#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <cassert>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_get_suit_left_bower){
    Suit trump(CLUBS);
    Card c(JACK, SPADES);
    Card c1(ACE, HEARTS);
    assert(c.get_suit(trump) == CLUBS);
    assert(c1.get_suit(trump) == HEARTS);
}

TEST(test_card_ace_or_face){
    Card ace(ACE, HEARTS);
    Card face(KING, HEARTS);
    Card neither(NINE, DIAMONDS);
    ASSERT_TRUE(ace.is_face_or_ace());
    ASSERT_TRUE(face.is_face_or_ace());
    ASSERT_FALSE(neither.is_face_or_ace());
}

TEST(test_bowers){
    Suit trump(CLUBS);
    Card right_bower(JACK, CLUBS);
    Card left_bower(JACK, SPADES);
    Card c(TEN, SPADES);
    ASSERT_TRUE(left_bower.is_left_bower(trump));
    ASSERT_TRUE(right_bower.is_right_bower(trump));
    ASSERT_FALSE(c.is_left_bower(trump));
    ASSERT_FALSE(c.is_right_bower(trump));
}

TEST(test_is_trump){
    Suit trump(HEARTS);
    Card c(KING, HEARTS);
    Card c1(JACK, DIAMONDS);
    Card c2(NINE, SPADES);
    ASSERT_TRUE(c.is_trump(trump));
    ASSERT_TRUE(c1.is_trump(trump));
    ASSERT_FALSE(c2.is_trump(trump));
}

TEST(test_overload_operators){
    Card c(KING, SPADES);
    ostringstream os;
    os << c;
    assert(os.str() == "King of Spades");
    istringstream is("Jack of Clubs");
    Card c1;
    is >> c1;
    assert(c1.get_rank() == JACK);
    assert(c1.get_suit() == CLUBS);
}

TEST(test_overload_inequalities){
    Card c(ACE, SPADES);
    Card c1(NINE, HEARTS);
    Card c2(ACE, CLUBS);
    Card c3(NINE, DIAMONDS);
    ASSERT_TRUE(c1 < c3);
    ASSERT_TRUE(c1 <= c3);
    ASSERT_FALSE(c1 == c2);
    ASSERT_TRUE(c != c2);
}

TEST(test_suit_next){
    assert(Suit_next(SPADES) == CLUBS);
    assert(Suit_next(CLUBS) == SPADES);
    assert(Suit_next(HEARTS) == DIAMONDS);
    assert(Suit_next(DIAMONDS) == HEARTS);
}

TEST(test_card_less){
    Suit trump = DIAMONDS;
    Card right_bower(JACK, DIAMONDS);
    Card left_bower(JACK, HEARTS);
    Card ledcard(ACE, HEARTS);
    Card c1(NINE, HEARTS);
    Card c2(TEN, DIAMONDS);
    Card c3(TEN, SPADES);
    Card c4(KING, DIAMONDS);
    Card c5(QUEEN, HEARTS);
    ASSERT_TRUE(Card_less(left_bower, right_bower, ledcard, trump));
    ASSERT_FALSE(Card_less(right_bower, left_bower, ledcard, trump));
    ASSERT_TRUE(Card_less(c3, right_bower, ledcard, trump));
    ASSERT_FALSE(Card_less(right_bower, c5, ledcard, trump));
    ASSERT_TRUE(Card_less(c1, left_bower, ledcard, trump));
    ASSERT_FALSE(Card_less(left_bower, c2, ledcard, trump));
    ASSERT_FALSE(Card_less(c2, c5, ledcard, trump));
    ASSERT_TRUE(Card_less(c5, c2, ledcard, trump));
}

TEST_MAIN()
